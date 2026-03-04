#include "example/ProcessModel.h"
ProcessModel::ProcessModel(BranchingStrategy branching_strategy):STModel() {

    this->branching_strategy = branching_strategy;
    this->scenario_names = { ScenarioNames::SCENARIO1, ScenarioNames::SCENARIO2,ScenarioNames::SCENARIO3,
     ScenarioNames::SCENARIO4, ScenarioNames::SCENARIO5,ScenarioNames::SCENARIO6,
     ScenarioNames::SCENARIO7,ScenarioNames::SCENARIO8,ScenarioNames::SCENARIO9,ScenarioNames::SCENARIO10,
    ScenarioNames::SCENARIO11,ScenarioNames::SCENARIO12,
     ScenarioNames::SCENARIO13,ScenarioNames::SCENARIO14,ScenarioNames::SCENARIO15,
    ScenarioNames::SCENARIO16,ScenarioNames::SCENARIO17,ScenarioNames::SCENARIO18,
    ScenarioNames::SCENARIO19,ScenarioNames::SCENARIO20
    };
    this->scenario_name = ScenarioNames::SCENARIO1; //default
    this->probability = 0.05; // equal probability for each scenario
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
        {ScenarioNames::SCENARIO10,4.3503766112257304},
        {ScenarioNames::SCENARIO11, 1.0976270078546495},
        {ScenarioNames::SCENARIO12, 9.430378732744838},
        {ScenarioNames::SCENARIO13, 6.6027633760716435},
        {ScenarioNames::SCENARIO14,1.3514894164800063},
        {ScenarioNames::SCENARIO15,4.236547993428394},
        {ScenarioNames::SCENARIO16,2.155994520336202},
        {ScenarioNames::SCENARIO17,5.0580836121681994},
        {ScenarioNames::SCENARIO18,2.0849789288240969},
        {ScenarioNames::SCENARIO19,5.6016775572644488},
        {ScenarioNames::SCENARIO20,4.3503766112257304}

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
    
};

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
        c1 = (-this->X[scenario_name][0] * (-0.00667 * pow(this->X[scenario_name][7],2) + 0.13167 * this->X[scenario_name][7] + 1.12) + this->X[scenario_name][4]) - p;
        nc1 = -c1;

        // e2_1: -x1 + 1.22*x4 - x5 <= perturb  --> (expr - p) <= 0
        c2 = (-this->X[scenario_name][0] + 1.22 * this->X[scenario_name][4] - this->X[scenario_name][3]) - p;

        // e2_2: -x1 + 1.22*x4 - x5 >= -perturb  --> -(expr + p) <= 0
        c3 = this->X[scenario_name][0] - 1.22 * this->X[scenario_name][4] + this->X[scenario_name][3] - p;

        // e3: -0.001 * x4 * x9 * x6 / (98 - x6) + x3 == perturb
        c4 = (-0.001 * this->X[scenario_name][4] * this->X[scenario_name][8] * this->X[scenario_name][5])-(98 - this->X[scenario_name][5])*(p-this->X[scenario_name][2]);
        nc4 = -c4;

        // e4: 0.038*x8^2 - 1.098*x8 - 0.325*x6 + x7 == 57.425
        c5 = (0.038 * pow(this->X[scenario_name][7],2) - 1.098 * this->X[scenario_name][7] - 0.325 * this->X[scenario_name][5] + this->X[scenario_name][6]) - 57.425;
        nc5 = -c5;

        // e5: -(x2 + x5)/x1 + x8 == 0
        c6 =  this->X[scenario_name][7]*this->X[scenario_name][0]-(this->X[scenario_name][1] + this->X[scenario_name][3]);
        nc6 = -c6;

        // e6: x9 + 0.222*x10 == 35.82
        c7 = (this->X[scenario_name][8] + 0.222 * this->X[scenario_name][9]) - 35.82;
        nc7 = -c7;

        // e7: -3*x7 + x10 == -133  -> (-3*x7 + x10) + 133 == 0
        c8 = (-3 * this->X[scenario_name][6] + this->X[scenario_name][9]) + 133;
        nc8 = -c8;


        mc::FFVar objective =this->probability*( 5.04 * this->X[scenario_name][0] + 0.035 * this->X[scenario_name][1] + 10.0 * this->X[scenario_name][2] + 3.36 * this->X[scenario_name][3]- 0.063 * this->X[scenario_name][4] * this->X[scenario_name][6]);
        this->F[scenario_name] = {objective,c1,c2,c3,c4,c5,c6,c7,c8,nc1,nc4,nc5,nc6,nc7,nc8};
    }
}

void ProcessModel::buildFullModelDAG(){
    // for full model solve we will stay in scenario 1
    int n_first_stage_vars = this->first_stage_IX.size();
    int nvars = this->first_stage_IX.size()+this->second_stage_IX.size();
    int n_second_stage_vars = this->second_stage_IX.size()/this->scenario_names.size(); // number of second stage variables per scenario
    this->X[ScenarioNames::SCENARIO1].resize(this->first_stage_IX.size() +this->second_stage_IX.size());
    
    mc::FFVar objective=0;
    for (int i = 0; i < n_first_stage_vars; ++i) this->X[ScenarioNames::SCENARIO1][i].set(&this->DAG[ScenarioNames::SCENARIO1]);
    for (int s_idx=0; s_idx<this->scenario_names.size(); ++s_idx){
        int second_stage_start_idx = n_first_stage_vars + s_idx * n_second_stage_vars;
        for (int i = 0; i < n_second_stage_vars; ++i){
            this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+i].set(&this->DAG[ScenarioNames::SCENARIO1]);
        }
    }
    for (int s_idx=0; s_idx<this->scenario_names.size(); ++s_idx){
        int second_stage_start_idx = n_first_stage_vars + s_idx * n_second_stage_vars;

        // scenario perturbation
        double p = this->perturb[this->scenario_names[s_idx]];
        //std::cout << "Building LP for " << scenario_name << " with perturbation " << p << std::endl;
        // Constraints translated from the Pyomo example (indices assume:
        // X[0]=m.x1, X[1]=m.x2, X[2]=m.x3, X[3]=m.x5,X[4]=m.x4[s], X[5]=m.x6[s],
        // X[6]=m.x7[s], X[7]=m.x8[s], X[8]=m.x9[s], X[9]=m.x10[s]
        // Constraints (mapped from the Pyomo model)


        // e1: -x1 * (-0.00667*x8^2 + 0.13167*x8 + 1.12) + x4 == perturb
        this->F[ScenarioNames::SCENARIO1].push_back((-this->X[ScenarioNames::SCENARIO1][0] * (-0.00667 * pow(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+3],2) + 0.13167 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+3] + 1.12) + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx]) - p);
        this->F[ScenarioNames::SCENARIO1].push_back(-((-this->X[ScenarioNames::SCENARIO1][0] * (-0.00667 * pow(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+3],2) + 0.13167 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+3] + 1.12) + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx]) - p));

        // e2_1: -x1 + 1.22*x4 - x5 <= perturb  --> (expr - p) <= 0
        this->F[ScenarioNames::SCENARIO1].push_back((-this->X[ScenarioNames::SCENARIO1][0] + 1.22 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx] - this->X[ScenarioNames::SCENARIO1][3]) - p);

        // e2_2: -x1 + 1.22*x4 - x5 >= -perturb  --> -(expr + p) <= 0
        this->F[ScenarioNames::SCENARIO1].push_back(this->X[ScenarioNames::SCENARIO1][0] - 1.22 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx] + this->X[ScenarioNames::SCENARIO1][3] - p);

        // e3: -0.001 * x4 * x9 * x6 / (98 - x6) + x3 == perturb
        this->F[ScenarioNames::SCENARIO1].push_back((-0.001 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+4] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+1])-(98 - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+1])*(p-this->X[ScenarioNames::SCENARIO1][2]));
        this->F[ScenarioNames::SCENARIO1].push_back(-((-0.001 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+4] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+1])-(98 - this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+1])*(p-this->X[ScenarioNames::SCENARIO1][2])));

        // e4: 0.038*x8^2 - 1.098*x8 - 0.325*x6 + x7 == 57.425
        this->F[ScenarioNames::SCENARIO1].push_back((0.038 * pow(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+3],2) - 1.098 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+3] - 0.325 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+1] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+2]) - 57.425);
        this->F[ScenarioNames::SCENARIO1].push_back(-((0.038 * pow(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+3],2) - 1.098 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+3] - 0.325 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+1] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+2]) - 57.425));

        // e5: -(x2 + x5)/x1 + x8 == 0
        this->F[ScenarioNames::SCENARIO1].push_back(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+3]*this->X[ScenarioNames::SCENARIO1][0]-(this->X[ScenarioNames::SCENARIO1][1] + this->X[ScenarioNames::SCENARIO1][3]));
        this->F[ScenarioNames::SCENARIO1].push_back(-(this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+3]*this->X[ScenarioNames::SCENARIO1][0]-(this->X[ScenarioNames::SCENARIO1][1] + this->X[ScenarioNames::SCENARIO1][3])));

        // e6: x9 + 0.222*x10 == 35.82
        this->F[ScenarioNames::SCENARIO1].push_back((this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+4] + 0.222 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+5]) - 35.82);
        this->F[ScenarioNames::SCENARIO1].push_back(-((this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+4] + 0.222 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+5]) - 35.82));

        // e7: -3*x7 + x10 == -133  -> (-3*x7 + x10) + 133 == 0
        this->F[ScenarioNames::SCENARIO1].push_back((-3 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+2] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+5]) + 133);
        this->F[ScenarioNames::SCENARIO1].push_back(-((-3 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+2] + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+5]) + 133));


        objective +=this->probability*( 5.04 * this->X[ScenarioNames::SCENARIO1][0] + 0.035 * this->X[ScenarioNames::SCENARIO1][1] + 10.0 * this->X[ScenarioNames::SCENARIO1][2] + 3.36 * this->X[ScenarioNames::SCENARIO1][3]- 0.063 * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx] * this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+2]);
    }

    this->F[ScenarioNames::SCENARIO1].insert(this->F[ScenarioNames::SCENARIO1].begin(), objective);
}
Ipopt::SmartPtr<STModel> ProcessModel::clone(solveFullmodel flag){
    Ipopt::SmartPtr<ProcessModel> p = new ProcessModel();

    p->scenario_name=this->scenario_name;
    p->first_stage_IX=this->first_stage_IX;
    p->second_stage_IX=this->second_stage_IX;
    p->perturb=this->perturb;
    p->scenario_names=this->scenario_names;
    p->probability=this->probability;
    p->clearDAG(); // clear the DAG for the cloned model
    if (flag == solveFullmodel::yes){
        p->buildFullModelDAG(); // build full model DAG for the cloned model
    }else{
        p->buildDAG(); // rebuild DAG for the cloned model
    }

    return p;
}