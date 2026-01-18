#include "example/STModel.h"
STModel::STModel(BranchingStrategy branching_strategy){
    this->branching_strategy = branching_strategy;
}

void STModel::generateLP(IloEnv* cplex_env,IloModel* cplexmodel,
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
    c4 = (-0.001 * X[4] * X[8] * X[5])/(98 - X[5])+X[2]-p;     // this is the problem
    nc4 = -c4;

    // e4: 0.038*x8^2 - 1.098*x8 - 0.325*x6 + x7 == 57.425
    c5 = (0.038 * pow(X[7],2) - 1.098 * X[7] - 0.325 * X[5] + X[6]) - 57.425;
    nc5 = -c5;

    // e5: -(x2 + x5)/x1 + x8 == 0
    c6 = (-(X[1] + X[3]) / X[0] + X[7]);
    nc6 = -c6;

    // e6: x9 + 0.222*x10 == 35.82
    c7 = (X[8] + 0.222 * X[9]) - 35.82;
    nc7 = -c7;

    // e7: -3*x7 + x10 == -133  -> (-3*x7 + x10) + 133 == 0
    c8 = (-3 * X[6] + X[9]) + 133;
    nc8 = -c8;


    mc::FFVar objective =0.333333333*( 5.04 * X[0] + 0.035 * X[1] + 10.0 * X[2] + 3.36 * X[3]- 0.063 * X[4] * X[6]);


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
    for (auto var : var_bound) {
        cplex_x->add(IloNumVar((*cplex_env), var.l(), var.u())); //change  
    }
    

    // Loop over cuts to build Ax<=b
    int row_idx=0;
    for (auto pc : c) {
        const double* coeffs = pc->coef();    // get pointer to coefficients
        int n = pc->nvar();  // number of variables in this constraint
        auto v = pc->var();              // get variable names that appear in this constraint
        if (pc->type() == 1) { // <=
            IloExpr expr(*cplex_env);
            for (int i = 0; i < n; ++i){
                int col_idx = std::stoi(v[i].name().substr(1));
                if (coeffs[i] != 0){
                    expr += coeffs[i] * (*cplex_x)[col_idx];
                }
            }
            cplex_constraints->add(expr <= pc->rhs());
        }else if (pc->type() == 2) { // >=
            IloExpr expr(*cplex_env);
            for (int i = 0; i < n; ++i){
                int col_idx = std::stoi(v[i].name().substr(1));
                if (coeffs[i] != 0){
                    expr += coeffs[i] * (*cplex_x)[col_idx];
                }
            }
            cplex_constraints->add(expr >= pc->rhs());
        }else { // ==
            IloExpr expr(*cplex_env);
            for (int i = 0; i < n; ++i){
                int col_idx = std::stoi(v[i].name().substr(1));
                if (coeffs[i] != 0){
                    expr += coeffs[i] * (*cplex_x)[col_idx];
                }
            }
            cplex_constraints->add(expr == pc->rhs());
        }
    }
    IloExpr objExpr(*cplex_env);
    objExpr+=(*cplex_x)[after_nvars-1];
    *(cplex_obj) = IloMinimize(*cplex_env, objExpr);
    objExpr.end();
    for (size_t i = 0; i < sizeof(PF)/sizeof(PF[0])-1; ++i) {
        IloExpr expr(*cplex_env);
        expr+=(*cplex_x)[PF[i].id().second];
        cplex_constraints->add(expr <= 0);
    }


    

    cplexmodel->add(*cplex_x);
    cplexmodel->add(*cplex_constraints);
    cplexmodel->add(*cplex_obj);
};
void STModel::LFRR(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x,int var_index,bool max){
    // Modify the objective to relax the variable at var_index
    if (max){
        cplexmodel->remove(*cplex_obj);
        IloExpr objExpr(*cplex_env);
        objExpr+=(*cplex_x)[var_index];
        *cplex_obj = IloMaximize(*cplex_env, objExpr);
        objExpr.end();
        cplexmodel->add(*cplex_obj);
    }else{
        cplexmodel->remove(*cplex_obj);
        IloExpr objExpr(*cplex_env);
        objExpr+=(*cplex_x)[var_index];
        *cplex_obj = IloMinimize(*cplex_env, objExpr);
        objExpr.end();
        cplexmodel->add(*cplex_obj);
    }
}