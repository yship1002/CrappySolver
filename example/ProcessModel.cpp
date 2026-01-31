#include "example/ProcessModel.h"
ProcessModel::ProcessModel(BranchingStrategy branching_strategy):STModel() {

    this->branching_strategy = branching_strategy;
    this->scenario_names = { ScenarioNames::SCENARIO1, ScenarioNames::SCENARIO2,
     ScenarioNames::SCENARIO3,ScenarioNames::SCENARIO4, ScenarioNames::SCENARIO5,ScenarioNames::SCENARIO6,
     ScenarioNames::SCENARIO7,ScenarioNames::SCENARIO8,ScenarioNames::SCENARIO9,ScenarioNames::SCENARIO10};
    this->scenario_name = ScenarioNames::SCENARIO1; //default
    this->perturb = {
        {ScenarioNames::SCENARIO1, 1.0976270078546495},// orignal
        {ScenarioNames::SCENARIO2, 9.430378732744838},
        {ScenarioNames::SCENARIO3, 6.6027633760716435},
        {ScenarioNames::SCENARIO4,1.3514894164800063},
        {ScenarioNames::SCENARIO5,4.236547993428394},
        {ScenarioNames::SCENARIO6,2.155994520336202},
        {ScenarioNames::SCENARIO7,5.0580836121681994},
        {ScenarioNames::SCENARIO8,2.0849789288240969},
        {ScenarioNames::SCENARIO9,5.6016775572644488},
        {ScenarioNames::SCENARIO10,4.3503766112257304}

    };
    this->first_stage_IX = {
        mc::Interval(10, 2000),       
        mc::Interval(0,16000),    
        mc::Interval(0,120),      
        mc::Interval(0,2000)  
    };
    this->second_stage_IX = {
        mc::Interval(0, 5000),       
        mc::Interval(85,93),    
        mc::Interval(90,95),      
        mc::Interval(3,12), 
        mc::Interval(1.2,4),
        mc::Interval(145,162)
    };
    // this->convertToCentralizedModel();
};
void ProcessModel::convertToCentralizedModel(){
    std::vector<mc::Interval> new_second_stage_IX;
    for (auto & scenario_name : this->scenario_names){
        new_second_stage_IX.insert(new_second_stage_IX.end(), this->second_stage_IX.begin(), this->second_stage_IX.end());
    };
    this->second_stage_IX = new_second_stage_IX;
}
void ProcessModel::generateLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) {


    int n_first_stage_vars = this->first_stage_IX.size();

    // Loop over each scenario to build subproblem

    const int nvars = n_first_stage_vars + this->second_stage_IX.size();
    mc::FFGraph DAG;
    mc::FFVar X[nvars];


    for (int i = 0; i < nvars; ++i) X[i].set(&DAG);

    // scenario perturbation
    double p = this->perturb[this->scenario_name];
    //std::cout << "Building LP for " << scenario_name << " with perturbation " << p << std::endl;
    // Constraints translated from the Pyomo example (indices assume:
    // X[0]=m.x1, X[1]=m.x2, X[2]=m.x3, X[3]=m.x5,X[4]=m.x4[s], X[5]=m.x6[s],
    // X[6]=m.x7[s], X[7]=m.x8[s], X[8]=m.x9[s], X[9]=m.x10[s]
    // Constraints (mapped from the Pyomo model)
    mc::FFVar c1,c2,c3,c4,c5,c6,c7,c8;
    mc::FFVar nc1,nc2,nc3,nc4,nc5,nc6,nc7,nc8;

    // e1: -x1 * (-0.00667*x8^2 + 0.13167*x8 + 1.12) + x4 == perturb
    c1 = (-X[0] * (-0.00667 * pow(X[7],2) + 0.13167 * X[7] + 1.12) + X[4]) - p;
    nc1 = -c1;

    // e2_1: -x1 + 1.22*x4 - x5 <= perturb  --> (expr - p) <= 0
    c2 = (-X[0] + 1.22 * X[4] - X[3]) - p;

    // e2_2: -x1 + 1.22*x4 - x5 >= -perturb  --> -(expr + p) <= 0
    c3 = X[0] - 1.22 * X[4] + X[3] - p;

    // e3: -0.001 * x4 * x9 * x6 / (98 - x6) + x3 == perturb
    c4 = (-0.001 * X[4] * X[8] * X[5])-(98 - X[5])*(p-X[2]);     // this is the problem
    nc4 = -c4;

    // e4: 0.038*x8^2 - 1.098*x8 - 0.325*x6 + x7 == 57.425
    c5 = (0.038 * pow(X[7],2) - 1.098 * X[7] - 0.325 * X[5] + X[6]) - 57.425;
    nc5 = -c5;

    // e5: -(x2 + x5)/x1 + x8 == 0
    c6 =  X[7]*X[0]-(X[1] + X[3]);
    nc6 = -c6;

    // e6: x9 + 0.222*x10 == 35.82
    c7 = (X[8] + 0.222 * X[9]) - 35.82;
    nc7 = -c7;

    // e7: -3*x7 + x10 == -133  -> (-3*x7 + x10) + 133 == 0
    c8 = (-3 * X[6] + X[9]) + 133;
    nc8 = -c8;


    mc::FFVar objective =0.1*( 5.04 * X[0] + 0.035 * X[1] + 10.0 * X[2] + 3.36 * X[3]- 0.063 * X[4] * X[6]);


    // Evaluate constraints and objective
    mc::PolImg<mc::Interval> Env;
    mc::PolVar<mc::Interval> PX[nvars];

    for (int i = 0; i < n_first_stage_vars; ++i) PX[i].set(&Env, X[i], this->first_stage_IX[i]);
    for (int i = n_first_stage_vars; i < nvars; ++i) PX[i].set(&Env, X[i], this->second_stage_IX[i - n_first_stage_vars]);
    
    mc::PolVar<mc::Interval> PF[15];
    mc::FFVar F[15] = {c1,c2,c3,c4,c5,c6,c7,c8,nc1,nc4,nc5,nc6,nc7,nc8,objective};
    DAG.eval(15, F, PF, nvars, X, PX);
    

    Env.generate_cuts(15, PF);

    // Extract LP data from Env Don't touch below this line
    auto c = Env.Cuts();
    int after_nvars = Env.Vars().size();
    std::vector<mc::Interval> var_bound(after_nvars);
    for (auto v : Env.Vars()) { // Note: Env.Vars() ordering is not v1,v2, ... rather based on z1,z2 so we need to get indices
        int v_idx=v.second->id().second;
        var_bound[v_idx]=mc::Interval(v.second->range().l(),v.second->range().u());
    }
    // Add variables to cplex in order of their IDs to match indexing
    for (int i = 0; i < after_nvars; ++i) {
        cplex_x->add(IloNumVar((*cplex_env), var_bound[i].l(), var_bound[i].u()));
    }
    

    // Loop over cuts to build Ax<=b
    int row_idx=0;
    for (const auto& pc : c) {
        const double* coeffs = pc->coef();    // get pointer to coefficients
        int n = pc->nvar();  // number of variables in this constraint
        auto v = pc->var();              // get variable names that appear in this constraint
        IloExpr expr(*cplex_env);
        for (int i = 0; i < n; ++i){
            int col_idx = std::stoi(v[i].name().substr(1));
            if (col_idx >= 0 && col_idx < cplex_x->getSize()){
                expr += coeffs[i] * (*cplex_x)[col_idx];
            }else{
                throw std::runtime_error("Error in generating constraints from cuts.");
            }
        }
        if (pc->type() == 1) { // <=
            cplex_constraints->add(expr <= pc->rhs());
        }else if (pc->type() == 2) { // >=
            cplex_constraints->add(expr >= pc->rhs());
        }else { // ==
            cplex_constraints->add(expr == pc->rhs());
        }
        expr.end();
    }
    IloExpr objExpr(*cplex_env);
    objExpr+=(*cplex_x)[after_nvars-1];
    *(cplex_obj) = IloMinimize(*cplex_env, objExpr);
    objExpr.end();
    
    for (size_t i = 0; i < sizeof(PF)/sizeof(PF[0])-1; ++i) {
        int pf_idx = PF[i].id().second;
        if (pf_idx >= 0 && pf_idx < cplex_x->getSize()) {
            IloExpr expr(*cplex_env);
            expr+=(*cplex_x)[pf_idx];
            cplex_constraints->add(expr <= 0);
            expr.end();
        }else{
            throw std::runtime_error("Error in generating constraints from cuts.");
        }
    }

    cplexmodel->add(*cplex_x);
    cplexmodel->add(*cplex_constraints);
    cplexmodel->add(*cplex_obj);
};

void ProcessModel::generateMINLP(GRBModel* grbmodel){
    // To be implemented
    int n_first_stage_vars = this->first_stage_IX.size();
    int n_second_stage_vars = this->second_stage_IX.size();

    // Loop over each scenario to build subproblem

    const int nvars = n_first_stage_vars + n_second_stage_vars;
    mc::FFGraph DAG;
    std::vector<mc::FFVar> X(nvars);


    for (int i = 0; i < nvars; ++i) X[i].set(&DAG);

    // scenario perturbation
    double p = this->perturb[this->scenario_name];


    //std::cout << "Building LP for " << scenario_name << " with perturbation " << p << std::endl;
    // Constraints translated from the Pyomo example (indices assume:
    // X[0]=m.x1, X[1]=m.x2, X[2]=m.x3, X[3]=m.x5,X[4]=m.x4[s], X[5]=m.x6[s],
    // X[6]=m.x7[s], X[7]=m.x8[s], X[8]=m.x9[s], X[9]=m.x10[s]
    // Constraints (mapped from the Pyomo model)
    mc::FFVar c1,c2,c3,c4,c5,c6,c7,c8;
    mc::FFVar nc1,nc4,nc5,nc6,nc7,nc8;

    // e1: -x1 * (-0.00667*x8^2 + 0.13167*x8 + 1.12) + x4 == perturb
    c1 = (-X[0] * (-0.00667 * pow(X[7],2) + 0.13167 * X[7] + 1.12) + X[4]) - p;
    nc1 = -c1;

    // e2_1: -x1 + 1.22*x4 - x5 <= perturb  --> (expr - p) <= 0
    c2 = (-X[0] + 1.22 * X[4] - X[3]) - p;

    // e2_2: -x1 + 1.22*x4 - x5 >= -perturb  --> -(expr + p) <= 0
    c3 = X[0] - 1.22 * X[4] + X[3] - p;

    // e3: -0.001 * x4 * x9 * x6 / (98 - x6) + x3 == perturb
    c4 = (-0.001 * X[4] * X[8] * X[5])/(98 - X[5])+X[2]-p;     // this is the problem
    nc4 = -c4;

    // e4: 0.038*x8^2 - 1.098*x8 - 0.325*x6 + x7 == 57.425
    c5 = (0.038 * pow(X[7],2) - 1.098 * X[7] - 0.325 * X[5] + X[6]) - 57.425;
    nc5 = -c5;

    // e5: -(x2 + x5)/x1 + x8 == 0
    c6 = (-(X[1] + X[3]) / X[0] + X[7]);
    nc6 = -c6;

    //e6: x9 + 0.222*x10 == 35.82
    c7 = (X[8] + 0.222 * X[9]) - 35.82;
    nc7 = -c7;

    // e7: -3*x7 + x10 == -133  -> (-3*x7 + x10) + 133 == 0
    c8 = (-3 * X[6] + X[9]) + 133;
    nc8 = -c8;


    mc::FFVar objective =0.1*( 5.04 * X[0] + 0.035 * X[1] + 10.0 * X[2] + 3.36 * X[3]- 0.063 * X[4] * X[6]);
    std::vector<mc::FFVar> F = {c1,c2,c3,c4,c5,c6,c7,c8,nc1,nc4,nc5,nc6,nc7,nc8,objective};
    


    // Don't touch below this line

    grbmodel->set(GRB_DoubleParam_MIPGap, 0.00001);

    for (int i = 0; i < n_first_stage_vars; ++i) {
        grbmodel->addVar(this->first_stage_IX[i].l(), this->first_stage_IX[i].u(), 0.0, GRB_CONTINUOUS, ("x" + std::to_string(i)));
    }
    for (int i = 0; i < n_second_stage_vars; ++i) {
        grbmodel->addVar(this->second_stage_IX[i].l(), this->second_stage_IX[i].u(), 0.0, GRB_CONTINUOUS, ("x" + std::to_string(i+n_first_stage_vars)));
    }

    grbmodel->update();

    for (int i = 0; i < F.size(); ++i) {
        mc::FFSubgraph subgraph = DAG.subgraph(std::vector<mc::FFVar> {F[i]});
        for (auto op : subgraph.l_op) {
            if (op->varin.size()==0) continue;
            if (op->varout[0]->id().first == mc::FFVar::CINT || op->varout[0]->id().first == mc::FFVar::CREAL || op->varout[0]->id().first == mc::FFVar::VAR) continue;
            // now we have an aux variable as output
            if (op->varout[0]->id().second == F[i].id().second) {
                if (i == F.size()-1) { // objective
                    grbmodel->addVar(-GRB_INFINITY, GRB_INFINITY, 1.0, GRB_CONTINUOUS, "aux_"+std::to_string(op->varout[0]->id().second));
                } else {
                    grbmodel->addVar(-GRB_INFINITY, 0, 0.0, GRB_CONTINUOUS, "aux_"+std::to_string(op->varout[0]->id().second)); // this is final output
                }
                grbmodel->update();
            }else{
                grbmodel->addVar(-GRB_INFINITY, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "aux_"+std::to_string(op->varout[0]->id().second));
                grbmodel->update();
            }
            if (op->varin.size()==1){ // one input -> one output aux var
                // check if power then need speical handle

                std::vector<int >opcode1;
                opcode1.push_back(this->map_ffop_to_grb(op->type));

                std::vector<double> data1;
                data1.push_back(-1.0);

                std::vector<int> parent1;
                parent1.push_back(-1); 

                switch (op->varin[0]->id().first){
                    case mc::FFVar::VAR:
                        data1.push_back(grbmodel->getVarByName("x"+std::to_string(op->varin[0]->id().second)).index());
                        opcode1.push_back(GRB_OPCODE_VARIABLE);
                        parent1.push_back(0);

                    break;
                    case mc::FFVar::AUX:
                        data1.push_back(grbmodel->getVarByName("aux_"+std::to_string(op->varin[0]->id().second)).index());
                        opcode1.push_back(GRB_OPCODE_VARIABLE);
                        parent1.push_back(0);
                    break;
                    case mc::FFVar::CINT:
                        data1.push_back(op->varin[0]->num().val());
                        opcode1.push_back(GRB_OPCODE_CONSTANT);
                        parent1.push_back(0);
                    break;
                    case mc::FFVar::CREAL:
                        data1.push_back(op->varin[0]->num().val());
                        opcode1.push_back(GRB_OPCODE_CONSTANT);
                        parent1.push_back(0);
                    break;
                    default:
                        throw std::runtime_error("Unsupported input var type for NL constraint");
                }
                if (op->type==mc::FFOp::SQR){
                    data1.push_back(2.0); // exponent 2 for SQR
                    opcode1.push_back(GRB_OPCODE_CONSTANT);
                    parent1.push_back(0);
                }
                grbmodel->addGenConstrNL(
                    grbmodel->getVarByName("aux_"+std::to_string(op->varout[0]->id().second)),
                    data1.size(),
                    opcode1.data(),
                    data1.data(),
                    parent1.data());
                grbmodel->update();

            }
            else{ // two input -> one output aux var
                std::vector<int >opcode2;
                opcode2.push_back(this->map_ffop_to_grb(op->type));

                std::vector<double> data2;
                data2.push_back(-1.0); 

                std::vector<int> parent2;
                parent2.push_back(-1);


                switch (op->varin[0]->id().first){
                    case mc::FFVar::VAR:
                        data2.push_back(grbmodel->getVarByName("x"+std::to_string(op->varin[0]->id().second)).index());
                        opcode2.push_back(GRB_OPCODE_VARIABLE);
                        parent2.push_back(0);

                    break;
                    case mc::FFVar::AUX:
                        data2.push_back(grbmodel->getVarByName("aux_"+std::to_string(op->varin[0]->id().second)).index());
                        opcode2.push_back(GRB_OPCODE_VARIABLE);
                        parent2.push_back(0);

                    break;
                    case mc::FFVar::CINT:
                        data2.push_back(op->varin[0]->num().val());
                        opcode2.push_back(GRB_OPCODE_CONSTANT);
                        parent2.push_back(0);
                    break;
                    case mc::FFVar::CREAL:
                        data2.push_back(op->varin[0]->num().val());
                        opcode2.push_back(GRB_OPCODE_CONSTANT);
                        parent2.push_back(0);
                    break;
                    default:
                        throw std::runtime_error("Unsupported input var type for NL constraint");
                }
                switch (op->varin[1]->id().first){
                    case mc::FFVar::VAR:
                        data2.push_back(grbmodel->getVarByName("x"+std::to_string(op->varin[1]->id().second)).index());
                        opcode2.push_back(GRB_OPCODE_VARIABLE);
                        parent2.push_back(0);
                    break;
                    case mc::FFVar::AUX:
                        data2.push_back(grbmodel->getVarByName("aux_"+std::to_string(op->varin[1]->id().second)).index());
                        opcode2.push_back(GRB_OPCODE_VARIABLE);
                        parent2.push_back(0);
                    break;
                    case mc::FFVar::CINT:
                        data2.push_back(op->varin[1]->num().val());
                        opcode2.push_back(GRB_OPCODE_CONSTANT);
                        parent2.push_back(0);
                    break;
                    case mc::FFVar::CREAL:
                        data2.push_back(op->varin[1]->num().val());
                        opcode2.push_back(GRB_OPCODE_CONSTANT);
                        parent2.push_back(0);
                    break;
                    default:
                        throw std::runtime_error("Unsupported input var type for NL constraint");
                }
                grbmodel->addGenConstrNL(
                    grbmodel->getVarByName("aux_"+std::to_string(op->varout[0]->id().second)),
                    data2.size(),
                    opcode2.data(),
                    data2.data(),
                    parent2.data());
                grbmodel->update();
            }

        }
    }
}

void ProcessModel::generateFullLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) {


    int n_first_stage_vars = this->first_stage_IX.size();
    int n_second_stage_vars = static_cast<int>(this->second_stage_IX.size())/static_cast<int>(this->scenario_names.size());

    // Loop over each scenario to build subproblem

    int nvars = n_first_stage_vars + this->second_stage_IX.size();
    mc::FFGraph DAG;
    mc::FFVar X[nvars];
    mc::PolImg<mc::Interval> Env;
    mc::PolVar<mc::Interval> PX[nvars];

    for (int i = 0; i < nvars; ++i) X[i].set(&DAG);

    for (int i = 0; i < n_first_stage_vars; ++i) PX[i].set(&Env, X[i], this->first_stage_IX[i]);
    for (const auto& scenario_name : this->scenario_names) {
        int scenario_start_idx= n_first_stage_vars + static_cast<int>(scenario_name) * n_second_stage_vars;
        for (int i =0; i < n_second_stage_vars; ++i){
            PX[i+scenario_start_idx].set(&Env, X[i+scenario_start_idx], this->second_stage_IX[i+scenario_start_idx-n_first_stage_vars]);
        }
    }

    std::vector<mc::FFVar> F;
    // scenario perturbation
    for (const auto& scenario_name : this->scenario_names){
        int scenario_start_idx= n_first_stage_vars + static_cast<int>(scenario_name) * n_second_stage_vars;
        double p = this->perturb[this->scenario_name];
        //std::cout << "Building LP for " << scenario_name << " with perturbation " << p << std::endl;
        // Constraints translated from the Pyomo example (indices assume:
        // X[0]=m.x1, X[1]=m.x2, X[2]=m.x3, X[3]=m.x5,X[4]=m.x4[s], X[5]=m.x6[s],
        // X[6]=m.x7[s], X[7]=m.x8[s], X[8]=m.x9[s], X[9]=m.x10[s]
        // Constraints (mapped from the Pyomo model)


        // e1: -x1 * (-0.00667*x8^2 + 0.13167*x8 + 1.12) + x4 == perturb
        F.push_back( (-X[0] * (-0.00667 * pow(X[scenario_start_idx + 3],2) + 0.13167 * X[scenario_start_idx + 3] + 1.12) + X[scenario_start_idx]) - p );
        F.push_back(-( (-X[0] * (-0.00667 * pow(X[scenario_start_idx + 3],2) + 0.13167 * X[scenario_start_idx + 3] + 1.12) + X[scenario_start_idx]) - p ));
        
        // c1 = (-X[0] * (-0.00667 * pow(X[7],2) + 0.13167 * X[7] + 1.12) + X[4]) - p;
        // nc1 = -c1;

        // e2_1: -x1 + 1.22*x4 - x5 <= perturb  --> (expr - p) <= 0
        F.push_back( (-X[0] + 1.22 * X[scenario_start_idx] - X[3]) - p );
        // c2 = (-X[0] + 1.22 * X[4] - X[3]) - p;

        // e2_2: -x1 + 1.22*x4 - x5 >= -perturb  --> -(expr + p) <= 0
        F.push_back( X[0] - 1.22 * X[scenario_start_idx] + X[3] - p );
        // c3 = X[0] - 1.22 * X[4] + X[3] - p;

        // e3: -0.001 * x4 * x9 * x6 / (98 - x6) + x3 == perturb
        F.push_back( (-0.001 * X[scenario_start_idx] * X[scenario_start_idx + 4] * X[scenario_start_idx + 1])-(98 - X[scenario_start_idx + 1])*(p-X[2]) );
        F.push_back( -((-0.001 * X[scenario_start_idx] * X[scenario_start_idx + 4] * X[scenario_start_idx + 1])-(98 - X[scenario_start_idx + 1])*(p-X[2])) );
        // c4 = (-0.001 * X[4] * X[8] * X[5])-(98 - X[5])*(p-X[2]);     // this is the problem
        // nc4 = -c4;

        // e4: 0.038*x8^2 - 1.098*x8 - 0.325*x6 + x7 == 57.425
        F.push_back( (0.038 * pow(X[scenario_start_idx + 3],2) - 1.098 * X[scenario_start_idx + 3] - 0.325 * X[scenario_start_idx + 1] + X[scenario_start_idx + 2]) - 57.425 );
        F.push_back( -((0.038 * pow(X[scenario_start_idx + 3],2) - 1.098 * X[scenario_start_idx + 3] - 0.325 * X[scenario_start_idx + 1] + X[scenario_start_idx + 2]) - 57.425) );
        // c5 = (0.038 * pow(X[7],2) - 1.098 * X[7] - 0.325 * X[5] + X[6]) - 57.425;
        // nc5 = -c5;

        // e5: -(x2 + x5)/x1 + x8 == 0
        F.push_back( X[scenario_start_idx + 3]*X[0]-(X[1] + X[3]) );
        F.push_back( -(X[scenario_start_idx + 3]*X[0]-(X[1] + X[3])) );
        //
        // c6 =  X[7]*X[0]-(X[1] + X[3]);
        // nc6 = -c6;

        // e6: x9 + 0.222*x10 == 35.82
        F.push_back( (X[scenario_start_idx + 4] + 0.222 * X[scenario_start_idx + 5]) - 35.82 );
        F.push_back( -((X[scenario_start_idx + 4] + 0.222 * X[scenario_start_idx + 5]) - 35.82) );
        // c7 = (X[8] + 0.222 * X[9]) - 35.82;
        // nc7 = -c7;

        // e7: -3*x7 + x10 == -133  -> (-3*x7 + x10) + 133 == 0
        F.push_back( (-3 * X[scenario_start_idx + 2] + X[scenario_start_idx + 5]) + 133 );
        F.push_back( -((-3 * X[scenario_start_idx + 2] + X[scenario_start_idx + 5]) + 133) );
        //
        // c8 = (-3 * X[6] + X[9]) + 133;
        // nc8 = -c8;


    }
    mc::FFVar objective =0;
    for (const auto& scenario_name : this->scenario_names){
        int scenario_start_idx= n_first_stage_vars + static_cast<int>(scenario_name) * n_second_stage_vars;
        objective +=0.1*( 5.04 * X[0] + 0.035 * X[1] + 10.0 * X[2] + 3.36 * X[3]- 0.063 * X[scenario_start_idx] * X[scenario_start_idx+2]);

    }
    F.push_back(objective);

    std::vector<mc::PolVar<mc::Interval>> PF(F.size());

    DAG.eval(F.size(), F.data(), PF.data(), nvars, X, PX);
    

    Env.generate_cuts(F.size(), PF.data());

    // Extract LP data from Env Don't touch below this line
    auto c = Env.Cuts();
    int after_nvars = Env.Vars().size();
    std::vector<mc::Interval> var_bound(after_nvars);
    for (auto v : Env.Vars()) { // Note: Env.Vars() ordering is not v1,v2, ... rather based on z1,z2 so we need to get indices
        int v_idx=v.second->id().second;
        var_bound[v_idx]=mc::Interval(v.second->range().l(),v.second->range().u());
    }
    // Add variables to cplex in order of their IDs to match indexing
    for (int i = 0; i < after_nvars; ++i) {
        cplex_x->add(IloNumVar((*cplex_env), var_bound[i].l(), var_bound[i].u()));
    }
    

    // Loop over cuts to build Ax<=b
    int row_idx=0;
    for (const auto& pc : c) {
        const double* coeffs = pc->coef();    // get pointer to coefficients
        int n = pc->nvar();  // number of variables in this constraint
        auto v = pc->var();              // get variable names that appear in this constraint
        IloExpr expr(*cplex_env);
        for (int i = 0; i < n; ++i){
            int col_idx = std::stoi(v[i].name().substr(1));
            if (col_idx >= 0 && col_idx < cplex_x->getSize()){
                expr += coeffs[i] * (*cplex_x)[col_idx];
            }else{
                throw std::runtime_error("Error in generating constraints from cuts.");
            }
        }
        if (pc->type() == 1) { // <=
            cplex_constraints->add(expr <= pc->rhs());
        }else if (pc->type() == 2) { // >=
            cplex_constraints->add(expr >= pc->rhs());
        }else { // ==
            cplex_constraints->add(expr == pc->rhs());
        }
        expr.end();
    }
    IloExpr objExpr(*cplex_env);
    objExpr+=(*cplex_x)[after_nvars-1];
    *(cplex_obj) = IloMinimize(*cplex_env, objExpr);
    objExpr.end();
    
    for (size_t i = 0; i < static_cast<int>(PF.size())-1; ++i) { //
        int pf_idx = PF[i].id().second;
        if (pf_idx >= 0 && pf_idx < cplex_x->getSize()) {
            IloExpr expr(*cplex_env);
            expr+=(*cplex_x)[pf_idx];
            cplex_constraints->add(expr <= 0);
            expr.end();
        }else{
            throw std::runtime_error("Error in generating constraints from cuts.");
        }
    }

    cplexmodel->add(*cplex_x);
    cplexmodel->add(*cplex_constraints);
    cplexmodel->add(*cplex_obj);
};