#include "example/ProcessModel.h"
ProcessModel::ProcessModel(BranchingStrategy branching_strategy):STModel() {

    this->branching_strategy = branching_strategy;
    this->scenario_names = { ScenarioNames::SCENARIO1, ScenarioNames::SCENARIO2,ScenarioNames::SCENARIO3
    //  ScenarioNames::SCENARIO4, ScenarioNames::SCENARIO5,ScenarioNames::SCENARIO6,
    //  ScenarioNames::SCENARIO7,ScenarioNames::SCENARIO8,ScenarioNames::SCENARIO9,ScenarioNames::SCENARIO10
    };
    this->scenario_name = ScenarioNames::SCENARIO1; //default
    this->perturb = {
        {ScenarioNames::SCENARIO1, 1.0976270078546495},// orignal
        {ScenarioNames::SCENARIO2, 9.430378732744838},
        {ScenarioNames::SCENARIO3, 6.6027633760716435}
        // {ScenarioNames::SCENARIO4,1.3514894164800063},
        // {ScenarioNames::SCENARIO5,4.236547993428394},
        // {ScenarioNames::SCENARIO6,2.155994520336202},
        // {ScenarioNames::SCENARIO7,5.0580836121681994},
        // {ScenarioNames::SCENARIO8,2.0849789288240969},
        // {ScenarioNames::SCENARIO9,5.6016775572644488},
        // {ScenarioNames::SCENARIO10,4.3503766112257304}

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
void ProcessModel::clearDAG(){
    for (const auto& scenario_name : this->scenario_names) {
        this->DAG[scenario_name].clear();
        this->X[scenario_name].clear();
        this->F[scenario_name].clear();
    }
}
void ProcessModel::buildDAG(){
    
    for (const auto& scenario_name : this->scenario_names) {

        int n_first_stage_vars = this->first_stage_IX.size();

        // Loop over each scenario to build subproblem

        const int nvars = n_first_stage_vars + this->second_stage_IX.size();

        this->X[scenario_name].resize(nvars);


        for (int i = 0; i < nvars; ++i) this->X[scenario_name][i].set(&this->DAG[scenario_name]);

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
        c1 = (-X[scenario_name][0] * (-0.00667 * pow(X[scenario_name][7],2) + 0.13167 * X[scenario_name][7] + 1.12) + X[scenario_name][4]) - p;
        nc1 = -c1;

        // e2_1: -x1 + 1.22*x4 - x5 <= perturb  --> (expr - p) <= 0
        c2 = (-X[scenario_name][0] + 1.22 * X[scenario_name][4] - X[scenario_name][3]) - p;

        // e2_2: -x1 + 1.22*x4 - x5 >= -perturb  --> -(expr + p) <= 0
        c3 = X[scenario_name][0] - 1.22 * X[scenario_name][4] + X[scenario_name][3] - p;

        // e3: -0.001 * x4 * x9 * x6 / (98 - x6) + x3 == perturb
        c4 = (-0.001 * X[scenario_name][4] * X[scenario_name][8] * X[scenario_name][5])-(98 - X[scenario_name][5])*(p-X[scenario_name][2]);
        nc4 = -c4;

        // e4: 0.038*x8^2 - 1.098*x8 - 0.325*x6 + x7 == 57.425
        c5 = (0.038 * pow(X[scenario_name][7],2) - 1.098 * X[scenario_name][7] - 0.325 * X[scenario_name][5] + X[scenario_name][6]) - 57.425;
        nc5 = -c5;

        // e5: -(x2 + x5)/x1 + x8 == 0
        c6 =  X[scenario_name][7]*X[scenario_name][0]-(X[scenario_name][1] + X[scenario_name][3]);
        nc6 = -c6;

        // e6: x9 + 0.222*x10 == 35.82
        c7 = (X[scenario_name][8] + 0.222 * X[scenario_name][9]) - 35.82;
        nc7 = -c7;

        // e7: -3*x7 + x10 == -133  -> (-3*x7 + x10) + 133 == 0
        c8 = (-3 * X[scenario_name][6] + X[scenario_name][9]) + 133;
        nc8 = -c8;


        mc::FFVar objective =0.3333333*( 5.04 * X[scenario_name][0] + 0.035 * X[scenario_name][1] + 10.0 * X[scenario_name][2] + 3.36 * X[scenario_name][3]- 0.063 * X[scenario_name][4] * X[scenario_name][6]);
        this->F[scenario_name] = {objective,c1,c2,c3,c4,c5,c6,c7,c8,nc1,nc4,nc5,nc6,nc7,nc8};
    }
}
void ProcessModel::buildFullModelDAG(){
    // for full model solve we will stay in scenario 1
    int n_first_stage_vars = this->first_stage_IX.size();
    int nvars = this->first_stage_IX.size();+this->scenario_names.size() * this->second_stage_IX.size();
    int n_second_stage_vars = this->second_stage_IX.size();
    this->X[ScenarioNames::SCENARIO1].resize(this->first_stage_IX.size() + this->scenario_names.size() * this->second_stage_IX.size());
    
    mc::FFVar objective;
    
    for (int s_idx=0; s_idx<this->scenario_names.size(); ++s_idx){
        int second_stage_start_idx = n_first_stage_vars + s_idx * n_second_stage_vars;
        for (int i = 0; i < n_second_stage_vars; ++i) this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+i].set(&this->DAG[ScenarioNames::SCENARIO1]);

        // scenario perturbation
        double p = this->perturb[this->scenario_names[s_idx]];
        //std::cout << "Building LP for " << scenario_name << " with perturbation " << p << std::endl;
        // Constraints translated from the Pyomo example (indices assume:
        // X[0]=m.x1, X[1]=m.x2, X[2]=m.x3, X[3]=m.x5,X[4]=m.x4[s], X[5]=m.x6[s],
        // X[6]=m.x7[s], X[7]=m.x8[s], X[8]=m.x9[s], X[9]=m.x10[s]
        // Constraints (mapped from the Pyomo model)


        // e1: -x1 * (-0.00667*x8^2 + 0.13167*x8 + 1.12) + x4 == perturb
        this->F[ScenarioNames::SCENARIO1].push_back((-X[ScenarioNames::SCENARIO1][0] * (-0.00667 * pow(X[ScenarioNames::SCENARIO1][second_stage_start_idx+3],2) + 0.13167 * X[ScenarioNames::SCENARIO1][second_stage_start_idx+3] + 1.12) + X[ScenarioNames::SCENARIO1][second_stage_start_idx]) - p);
        this->F[ScenarioNames::SCENARIO1].push_back(-((-X[ScenarioNames::SCENARIO1][0] * (-0.00667 * pow(X[ScenarioNames::SCENARIO1][second_stage_start_idx+3],2) + 0.13167 * X[ScenarioNames::SCENARIO1][second_stage_start_idx+3] + 1.12) + X[ScenarioNames::SCENARIO1][second_stage_start_idx]) - p));

        // e2_1: -x1 + 1.22*x4 - x5 <= perturb  --> (expr - p) <= 0
        this->F[ScenarioNames::SCENARIO1].push_back((-X[ScenarioNames::SCENARIO1][0] + 1.22 * X[ScenarioNames::SCENARIO1][second_stage_start_idx] - X[ScenarioNames::SCENARIO1][3]) - p);

        // e2_2: -x1 + 1.22*x4 - x5 >= -perturb  --> -(expr + p) <= 0
        this->F[ScenarioNames::SCENARIO1].push_back(X[ScenarioNames::SCENARIO1][0] - 1.22 * X[ScenarioNames::SCENARIO1][second_stage_start_idx] + X[ScenarioNames::SCENARIO1][3] - p);

        // e3: -0.001 * x4 * x9 * x6 / (98 - x6) + x3 == perturb
        this->F[ScenarioNames::SCENARIO1].push_back((-0.001 * X[ScenarioNames::SCENARIO1][second_stage_start_idx] * X[ScenarioNames::SCENARIO1][second_stage_start_idx+4] * X[ScenarioNames::SCENARIO1][second_stage_start_idx+1])-(98 - X[ScenarioNames::SCENARIO1][second_stage_start_idx+1])*(p-X[ScenarioNames::SCENARIO1][2]));
        this->F[ScenarioNames::SCENARIO1].push_back(-((-0.001 * X[ScenarioNames::SCENARIO1][second_stage_start_idx] * X[ScenarioNames::SCENARIO1][second_stage_start_idx+4] * X[ScenarioNames::SCENARIO1][second_stage_start_idx+1])-(98 - X[ScenarioNames::SCENARIO1][second_stage_start_idx+1])*(p-X[ScenarioNames::SCENARIO1][2])));

        // e4: 0.038*x8^2 - 1.098*x8 - 0.325*x6 + x7 == 57.425
        this->F[ScenarioNames::SCENARIO1].push_back((0.038 * pow(X[ScenarioNames::SCENARIO1][second_stage_start_idx+3],2) - 1.098 * X[ScenarioNames::SCENARIO1][second_stage_start_idx+3] - 0.325 * X[ScenarioNames::SCENARIO1][second_stage_start_idx+1] + X[ScenarioNames::SCENARIO1][second_stage_start_idx+2]) - 57.425);
        this->F[ScenarioNames::SCENARIO1].push_back(-((0.038 * pow(X[ScenarioNames::SCENARIO1][second_stage_start_idx+3],2) - 1.098 * X[ScenarioNames::SCENARIO1][second_stage_start_idx+3] - 0.325 * X[ScenarioNames::SCENARIO1][second_stage_start_idx+1] + X[ScenarioNames::SCENARIO1][second_stage_start_idx+2]) - 57.425));

        // e5: -(x2 + x5)/x1 + x8 == 0
        this->F[ScenarioNames::SCENARIO1].push_back(X[ScenarioNames::SCENARIO1][second_stage_start_idx+3]*X[ScenarioNames::SCENARIO1][0]-(X[ScenarioNames::SCENARIO1][1] + X[ScenarioNames::SCENARIO1][3]));
        this->F[ScenarioNames::SCENARIO1].push_back(-(X[ScenarioNames::SCENARIO1][second_stage_start_idx+3]*X[ScenarioNames::SCENARIO1][0]-(X[ScenarioNames::SCENARIO1][1] + X[ScenarioNames::SCENARIO1][3])));

        // e6: x9 + 0.222*x10 == 35.82
        this->F[ScenarioNames::SCENARIO1].push_back((X[ScenarioNames::SCENARIO1][second_stage_start_idx+4] + 0.222 * X[ScenarioNames::SCENARIO1][second_stage_start_idx+5]) - 35.82);
        this->F[ScenarioNames::SCENARIO1].push_back(-((X[ScenarioNames::SCENARIO1][second_stage_start_idx+4] + 0.222 * X[ScenarioNames::SCENARIO1][second_stage_start_idx+5]) - 35.82));

        // e7: -3*x7 + x10 == -133  -> (-3*x7 + x10) + 133 == 0
        this->F[ScenarioNames::SCENARIO1].push_back((-3 * X[ScenarioNames::SCENARIO1][second_stage_start_idx+2] + X[ScenarioNames::SCENARIO1][second_stage_start_idx+5]) + 133);
        this->F[ScenarioNames::SCENARIO1].push_back(-((-3 * X[ScenarioNames::SCENARIO1][second_stage_start_idx+2] + X[ScenarioNames::SCENARIO1][second_stage_start_idx+5]) + 133));


        objective +=0.3333333*( 5.04 * X[ScenarioNames::SCENARIO1][0] + 0.035 * X[ScenarioNames::SCENARIO1][1] + 10.0 * X[ScenarioNames::SCENARIO1][2] + 3.36 * X[ScenarioNames::SCENARIO1][3]- 0.063 * X[ScenarioNames::SCENARIO1][second_stage_start_idx] * X[ScenarioNames::SCENARIO1][second_stage_start_idx+2]);
    }

    this->F[ScenarioNames::SCENARIO1].push_back(objective);
}
Ipopt::SmartPtr<STModel> ProcessModel::clone(){
    Ipopt::SmartPtr<ProcessModel> p = new ProcessModel();

    p->scenario_name=this->scenario_name;
    p->first_stage_IX=this->first_stage_IX;
    p->second_stage_IX=this->second_stage_IX;
    p->perturb=this->perturb;
    p->scenario_names=this->scenario_names;
    p->buildDAG(); // rebuild DAG for the cloned model


    return p;
}
void ProcessModel::generateLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) {

    // Loop over each scenario to build subproblem

    const int nvars = this->X[this->scenario_name].size();
    std::rotate(this->F[this->scenario_name].begin(), this->F[this->scenario_name].begin() + 1, this->F[this->scenario_name].end());

    // Evaluate constraints and objective
    mc::PolImg<mc::Interval> Env;
    mc::PolVar<mc::Interval> PX[nvars];

    for (int i = 0; i < this->first_stage_IX.size(); ++i) PX[i].set(&Env, this->X[this->scenario_name][i], this->first_stage_IX[i]);
    for (int i = this->first_stage_IX.size(); i < nvars; ++i) PX[i].set(&Env, this->X[this->scenario_name][i], this->second_stage_IX[i - this->first_stage_IX.size()]);
    
    mc::PolVar<mc::Interval> PF[this->F[this->scenario_name].size()];

    this->DAG[this->scenario_name].eval(this->F[this->scenario_name].size(), this->F[this->scenario_name].data(), PF, nvars, this->X[this->scenario_name].data(), PX);
    

    Env.generate_cuts(this->F[this->scenario_name].size(), PF);

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
    objExpr+=(*cplex_x)[after_nvars-1]; // objective is always the last variable in our construction
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
    std::rotate(this->F[this->scenario_name].rbegin(), this->F[this->scenario_name].rbegin() + 1, this->F[this->scenario_name].rend()); // rotate back to original order
};

void ProcessModel::generateMINLP(GRBModel* grbmodel){
    // Don't touch below this line

    grbmodel->set(GRB_DoubleParam_MIPGap, 0.00001);

    for (int i = 0; i < this->first_stage_IX.size(); ++i) {
        grbmodel->addVar(this->first_stage_IX[i].l(), this->first_stage_IX[i].u(), 0.0, GRB_CONTINUOUS, ("x" + std::to_string(i)));
    }
    for (int i = 0; i < this->second_stage_IX.size(); ++i) {
        grbmodel->addVar(this->second_stage_IX[i].l(), this->second_stage_IX[i].u(), 0.0, GRB_CONTINUOUS, ("x" + std::to_string(i+this->first_stage_IX.size())));
    }

    grbmodel->update();

    for (int i = 0; i < this->F[this->scenario_name].size(); ++i) {
        mc::FFSubgraph subgraph = this->DAG[this->scenario_name].subgraph(std::vector<mc::FFVar> {this->F[this->scenario_name][i]});
        for (auto op : subgraph.l_op) {
            if (op->varin.size()==0) continue;
            if (op->varout[0]->id().first == mc::FFVar::CINT || op->varout[0]->id().first == mc::FFVar::CREAL || op->varout[0]->id().first == mc::FFVar::VAR) continue;
            // now we have an aux variable as output
            if (op->varout[0]->id().second == this->F[this->scenario_name][i].id().second) { //if either object or constraint
                if (i == 0) { // objective
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
    // grbmodel->write("model.lp");
     // Set objective
}

void ProcessModel::generateFullLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) {

    mc::PolImg<mc::Interval> Env;
    mc::PolVar<mc::Interval> PX[this->X[ScenarioNames::SCENARIO1].size()];

    for (int i = 0; i < this->X[ScenarioNames::SCENARIO1].size(); ++i) this->X[ScenarioNames::SCENARIO1][i].set(&this->DAG[ScenarioNames::SCENARIO1]);

    for (int i = 0; i < this->first_stage_IX.size(); ++i) PX[i].set(&Env, this->X[ScenarioNames::SCENARIO1][i], this->first_stage_IX[i]);
    for (const auto& scenario_name : this->scenario_names) {
        int scenario_start_idx= this->first_stage_IX.size() + static_cast<int>(scenario_name) * this->second_stage_IX.size();
        for (int i =0; i < this->second_stage_IX.size(); ++i){
            PX[i+scenario_start_idx].set(&Env, this->X[ScenarioNames::SCENARIO1][i+scenario_start_idx], this->second_stage_IX[i]);
        }
    }


    std::vector<mc::PolVar<mc::Interval>> PF(this->F[ScenarioNames::SCENARIO1].size());

    this->DAG[ScenarioNames::SCENARIO1].eval(this->F[ScenarioNames::SCENARIO1].size(), this->F[ScenarioNames::SCENARIO1].data(), PF.data(), this->X[ScenarioNames::SCENARIO1].size(), this->X[ScenarioNames::SCENARIO1].data(), PX);
    
    Env.generate_cuts(this->F[ScenarioNames::SCENARIO1].size(), PF.data());

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

bool ProcessModel::get_nlp_info(
            Ipopt::Index& n,
            Ipopt::Index& m,
            Ipopt::Index& nnz_jac_g,
            Ipopt::Index& nnz_h_lag,
            Ipopt::TNLP::IndexStyleEnum& index_style
        )
{   


    // number of variables
    n = this->first_stage_IX.size() + this->second_stage_IX.size();

    // number of constraints
    m = this->F[this->scenario_name].size()-1; // w

    // in this example the jacobian is dense and contains 8 nonzeros
    nnz_jac_g = n*m;

    // the Hessian is also dense and has 16 total nonzeros, but we
    // only need the lower left corner (since it is symmetric)
    nnz_h_lag = 0;

    // use the C style indexing (0-based)
    index_style = TNLP::C_STYLE;
    return true;
};
bool ProcessModel::get_bounds_info(
            Ipopt::Index   n,
            Ipopt::Number* x_l,
            Ipopt::Number* x_u,
            Ipopt::Index   m,
            Ipopt::Number* g_l,
            Ipopt::Number* g_u
        )
{
    assert(n == (Ipopt::Index)(this->first_stage_IX.size()+this->second_stage_IX.size()));
    assert(m == (Ipopt::Index)(this->F[this->scenario_name].size()-1));
    // the variables have lower bounds of 1
    for( Ipopt::Index i = 0; i < this->first_stage_IX.size(); i++ )
    {
        x_l[i] = this->first_stage_IX[i].l(); // for first stage variables
        x_u[i] = this->first_stage_IX[i].u();
    }
    for( Ipopt::Index i = 0; i < this->second_stage_IX.size(); i++ )
    {
        x_l[i + this->first_stage_IX.size()] = this->second_stage_IX[i].l(); // for second stage variables
        x_u[i + this->first_stage_IX.size()] = this->second_stage_IX[i].u(); // for second stage variables
    }
    for (Ipopt::Index i = 0; i < m; ++i) {
        g_l[i] = -2e19;
        g_u[i] = 0.0;
    }


    return true;
}

bool ProcessModel::get_starting_point(
            Ipopt::Index   n,
            bool    init_x,
            Ipopt::Number* x,
            bool    init_z,
            Ipopt::Number* z_L,
            Ipopt::Number* z_U,
            Ipopt::Index   m,
            bool    init_lambda,
            Ipopt::Number* lambda
        ) 
{

    // initialize to the given starting point
    for (Ipopt::Index i = 0; i < this->first_stage_IX.size(); ++i) {
        x[i] =0.5*(this->first_stage_IX[i].l() + this->first_stage_IX[i].u()); // for first stage variables
    }
    for (Ipopt::Index i = 0; i < this->second_stage_IX.size(); ++i) {
        x[i + this->first_stage_IX.size()] =0.5*(this->second_stage_IX[i].l() + this->second_stage_IX[i].u()); // for second stage variables
    }

    return true;
};
bool ProcessModel::eval_f(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Number&       obj_value
        )
{


    mc::FFSubgraph   op_f= this->DAG[this->scenario_name].subgraph(std::vector<mc::FFVar> {this->F[this->scenario_name][0]});
    std::vector<double> dwk;
    std::vector<mc::FFVar>  Fvar;

    this->DAG[this->scenario_name].eval(op_f, dwk, 1, &(this->F[this->scenario_name][0]), &obj_value,
             n,this->X[this->scenario_name].data(), x);

    return true;
};
bool ProcessModel::eval_grad_f(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Number*       grad_f
        )
{
    std::vector<fadbad::B<double>> BXval(n);
    fadbad::B<double>   BCval;
    std::vector<fadbad::B<double>> Bwk;
    mc::FFSubgraph   op_f= this->DAG[this->scenario_name].subgraph(std::vector<mc::FFVar> {this->F[this->scenario_name][0]});
    for( Ipopt::Index i=0; i<n; i++ ){
          BXval[i] = x[i];
    }
    this->DAG[this->scenario_name].eval( op_f, Bwk, 1, &(this->F[this->scenario_name][0]), &BCval, n, this->X[this->scenario_name].data(), BXval.data() );
        
    Bwk.clear();
    BCval.diff( 0, 1 );
    // Gather derivatives
    for( Ipopt::Index i=0; i<n; i++ ){
        grad_f[i] = BXval[i].d(0);
    }
    return true;
};
bool ProcessModel::eval_g(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Index         m,
            Ipopt::Number*       g
        )
{
    std::vector<double> dwk;
    mc::FFSubgraph   op_g= this->DAG[this->scenario_name].subgraph(m,this->F[this->scenario_name].data()+1);
    // skipping the first one since it's the objective
    this->DAG[this->scenario_name].eval( op_g, dwk, m, this->F[this->scenario_name].data()+1, g, n, this->X[this->scenario_name].data(), x );

    return true;
}
bool ProcessModel::eval_jac_g(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Index         m,
            Ipopt::Index         nele_jac,
            Ipopt::Index*        iRow,
            Ipopt::Index*        jCol,
            Ipopt::Number*       values
        ) 
{

    // Dense pattern: row-major (constraint-major)
    if (values == nullptr) {
        Ipopt::Index k = 0;
        for (Ipopt::Index row = 0; row < m; ++row) {
            for (Ipopt::Index col = 0; col < n; ++col) {
                iRow[k] = row;
                jCol[k] = col;
                ++k;
            }
        }
        assert(k == nele_jac);
        return true;
    }
    std::vector<fadbad::B<double>> BXval(n);
    std::vector<fadbad::B<double>> BFval(m);
    fadbad::B<double>   BCval;
    std::vector<fadbad::B<double>> Bwk;
    mc::FFSubgraph   op_g= this->DAG[this->scenario_name].subgraph(m,this->F[this->scenario_name].data()+1);

    // Initialize participating variables in fadbad::B<double>
    for( Ipopt::Index i=0; i<n; i++ ){
        BXval[i] = x[i];
    }

    this->DAG[this->scenario_name].eval( op_g, Bwk, m, this->F[this->scenario_name].data()+1, BFval.data(), n, this->X[this->scenario_name].data(), BXval.data() );

    Bwk.clear();
    for( Ipopt::Index j=0; j<m; j++ ){
        BFval[j].diff( j, m );
    }
    // Gather derivatives

    for (Ipopt::Index row=0; row<m; ++row) {
        BFval[row].diff(row, m);
    }
    Ipopt::Index k = 0;
    for (Ipopt::Index row = 0; row < m; ++row) {
        for (Ipopt::Index col = 0; col < n; ++col) {
            values[k++] = BXval[col].d(row);   // <-- key
        }
    }
    return true;

};
void ProcessModel::finalize_solution(
        Ipopt::SolverReturn               status,
        Ipopt::Index                      n,
        const Ipopt::Number*              x,
        const Ipopt::Number*              z_L,
        const Ipopt::Number*              z_U,
        Ipopt::Index                      m,
        const Ipopt::Number*              g,
        const Ipopt::Number*              lambda,
        Ipopt::Number                     obj_value,
        const Ipopt::IpoptData*           ip_data,
        Ipopt::IpoptCalculatedQuantities* ip_cq
    ) 
{
    std::vector<double> Pval;
    this->solution.stat    = status;
    this->solution.p       = Pval;
    this->solution.x.assign( x, x+n );
    this->solution.ux.resize( n );
    for( int i=0; i<n; i++ ) this->solution.ux[i] = z_L[i] - z_U[i];  
    this->solution.f.assign( 1, obj_value );
    this->solution.f.insert( this->solution.f.end() , g, g+m );
    this->solution.uf.assign( 1, -1. );
    this->solution.uf.resize( m+1 );
    for( int j=0; j<m; j++ ) this->solution.uf[1+j] = - lambda[j];
};