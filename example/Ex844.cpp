#include "example/Ex844.h"

Ex844Model::Ex844Model(BranchingStrategy branching_strategy):STModel() {

    this->branching_strategy = branching_strategy;
    this->scenario_names = { ScenarioNames::SCENARIO1, ScenarioNames::SCENARIO2,ScenarioNames::SCENARIO3
    //  ScenarioNames::SCENARIO4, ScenarioNames::SCENARIO5,ScenarioNames::SCENARIO6,
    //  ScenarioNames::SCENARIO7,ScenarioNames::SCENARIO8,ScenarioNames::SCENARIO9,ScenarioNames::SCENARIO10,
    //  ScenarioNames::SCENARIO11, ScenarioNames::SCENARIO12,ScenarioNames::SCENARIO13,
    //  ScenarioNames::SCENARIO14, ScenarioNames::SCENARIO15,ScenarioNames::SCENARIO16,
    //  ScenarioNames::SCENARIO17,ScenarioNames::SCENARIO18,ScenarioNames::SCENARIO19,ScenarioNames::SCENARIO20
    };
    this->scenario_name = ScenarioNames::SCENARIO1; //default
    this->probability = 0.333333333; // equal probability for each scenario
    this->perturb = {
        {ScenarioNames::SCENARIO1, 0.05488135039273248}, 
        {ScenarioNames::SCENARIO2, 0.17151893663724196}, 
        {ScenarioNames::SCENARIO3, 0.2602763376071644}
        // {ScenarioNames::SCENARIO4, 0.05488135039273248}, 
        // {ScenarioNames::SCENARIO5, 0.17151893663724196}, 
        // {ScenarioNames::SCENARIO6, 0.2602763376071644},
        // {ScenarioNames::SCENARIO7, 0.05488135039273248}, 
        // {ScenarioNames::SCENARIO8, 0.17151893663724196}, 
        // {ScenarioNames::SCENARIO9, 0.2602763376071644},
        // {ScenarioNames::SCENARIO10, 0.05488135039273248},
        // {ScenarioNames::SCENARIO11, 0.05488135039273248}, 
        // {ScenarioNames::SCENARIO12, 0.17151893663724196}, 
        // {ScenarioNames::SCENARIO13, 0.2602763376071644},
        // {ScenarioNames::SCENARIO14, 0.05488135039273248}, 
        // {ScenarioNames::SCENARIO15, 0.17151893663724196}, 
        // {ScenarioNames::SCENARIO16, 0.2602763376071644},
        // {ScenarioNames::SCENARIO17, 0.05488135039273248}, 
        // {ScenarioNames::SCENARIO18, 0.17151893663724196}, 
        // {ScenarioNames::SCENARIO19, 0.2602763376071644},
        // {ScenarioNames::SCENARIO20, 0.05488135039273248}


    };
    // this->first_stage_IX = {
    //     mc::Interval(-1.1370129865018144, -1.1370129865018144),       
    //     mc::Interval(1.5650443750201455, 1.5650443750201455),    
    //     mc::Interval(-0.5986905053355759, -0.5986905053355759),
    //     mc::Interval(1.3454091920547648, 1.3454091920547648),
    //     mc::Interval(-0.23129676903369026, -0.23129676903369026),
    //     mc::Interval(1.2019450763451505, 1.2019450763451505),
    //     mc::Interval(0.052637388800998, 0.052637388800998),
    //     mc::Interval(0.5559409367398721, 0.5559409367398721),
    //     mc::Interval(0.6052476858593598, 0.6052476858593598),
    //     mc::Interval(1.1, 1.1),
    //     mc::Interval(0.8068686401687863, 0.8068686401687863),
    //     mc::Interval(0.663161467338442, 0.663161467338442)
    // };
    // this->second_stage_IX = {
    //     mc::Interval(5.137681424644748,5.137681424644748),       
    //     mc::Interval(-4.95353950678979,-4.95353950678979),    
    //     mc::Interval(2.6641201585529943,2.6641201585529943),      
    //     mc::Interval(-2,-2), 
    //     mc::Interval(1.885799773382196,1.885799773382196),

    // };

    this->first_stage_IX = {
        mc::Interval(-2, 0),       
        mc::Interval(0.5, 2.5),    
        mc::Interval(-1.5, 0.5),
        mc::Interval(0.2, 2.2),
        mc::Interval(-1.2, 0.8),
        mc::Interval(0.1, 2.1),
        mc::Interval(-1.1, 0.9),
        mc::Interval(0, 1),
        mc::Interval(0, 1),
        mc::Interval(1.1, 1.3),
        mc::Interval(0, 1),
        mc::Interval(0, 1)
    };
        
    this->second_stage_IX = {
        mc::Interval(4, 6),       
        mc::Interval(-6,-4),    
        mc::Interval(2,4),      
        mc::Interval(-3,-1), 
        mc::Interval(1,3),

    };
 
};
void Ex844Model::buildDAG() {
    for (auto& scenario_name : this->scenario_names) {
        int n_first_stage_vars = this->first_stage_IX.size();

        // Loop over each scenario to build subproblem

        const int nvars = n_first_stage_vars + this->second_stage_IX.size();

        this->X[scenario_name].resize(nvars);


        for (int i = 0; i < nvars; ++i) this->X[scenario_name][i].set(&this->DAG[scenario_name]);

        // scenario perturbation
        double p = this->perturb[this->scenario_name];
        //std::cout << "Building LP for " << scenario_name << " with perturbation " << p << std::endl;
        // Constraints translated from the Pyomo example (indices assume:
        // X[0]=m.x6, X[1]=m.x7, X[2]=m.x8, X[3]=m.x9,X[4]=m.x10, X[5]=m.x11,
        // X[6]=m.x12, X[7]=m.x13, X[8]=m.x14, X[9]=m.x15, X[10]=m.x16,X[11]=m.x17
        // X[12]=m.x1[s], X[13]=m.x2[s], X[14]=m.x3[s], X[15]=m.x4[s], X[16]=m.x5[s])
        // Constraints (mapped from the Pyomo model)
        mc::FFVar c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11;
        mc::FFVar nc1,nc2,nc3,nc4,nc5,nc6,nc7,nc8,nc9,nc10,nc11;

        double scale=1;
        c1=this->X[scenario_name][8]-pow(0.628318,this->X[scenario_name][9])*(this->X[scenario_name][1] - this->X[scenario_name][7]);
        c1=scale*c1;
        nc1=-c1;


        c2=this->X[scenario_name][8] -pow(0.7853975,this->X[scenario_name][9])* (this->X[scenario_name][3] - this->X[scenario_name][7]);
        c2=scale*c2;
        nc2=-c2;


        c3=this->X[scenario_name][8]-pow(0.942477,this->X[scenario_name][9])*( this->X[scenario_name][5] - this->X[scenario_name][7]);
        c3=scale*c3;
        nc3=-c3;


        c4=- this->X[scenario_name][11]-pow(0.4712385,this->X[scenario_name][9]) * (this->X[scenario_name][0] - 0.4712385*this->X[scenario_name][10]);
        c4=scale*c4;
        nc4=-c4;


        c5=- this->X[scenario_name][11]-pow(0.628318,this->X[scenario_name][9]) * (this->X[scenario_name][2] - 0.628318*this->X[scenario_name][10]);
        c5=scale*c5;
        nc5=-c5;

    
        c6=- this->X[scenario_name][11]-pow(0.7853975,this->X[scenario_name][9]) * (this->X[scenario_name][4] - 0.7853975*this->X[scenario_name][10]);
        c6=scale*c6;
        nc6=-c6;

    
        c7=- this->X[scenario_name][11]-pow(0.942477,this->X[scenario_name][9]) * (this->X[scenario_name][6] - 0.942477*this->X[scenario_name][10]);
        c7=scale*c7;
        nc7=-c7;


        c8=this->X[scenario_name][8]-pow(0.1570795,this->X[scenario_name][9]) * (this->X[scenario_name][12] - this->X[scenario_name][7]+p);
        c8=scale*c8;
        nc8=-c8;

        c9=this->X[scenario_name][8]-pow(0.314159,this->X[scenario_name][9]) * (this->X[scenario_name][14] - this->X[scenario_name][7]+p);
        c9=scale*c9;
        nc9=-c9;


        c10=this->X[scenario_name][8]-pow(0.4712385,this->X[scenario_name][9]) * (this->X[scenario_name][16] - this->X[scenario_name][7]+p);
        c10=scale*c10;
        nc10=-c10;

        c11=- this->X[scenario_name][11]-pow(0.1570795,this->X[scenario_name][9]) * (this->X[scenario_name][13] - 0.1570795*this->X[scenario_name][10]);
        c11=scale*c11;
        nc11=-c11;



        mc::FFVar objective =1000*this->probability*(pow((-5 + this->X[scenario_name][12]),2) + pow((5 + this->X[scenario_name][13]),2) + pow((-3 + this->X[scenario_name][14]),2) + pow((2 + this->X[scenario_name][15]),2) + pow((-2 + this->X[scenario_name][16]),2)
                            + pow((1 + this->X[scenario_name][0]),2) + pow((-1.5 + this->X[scenario_name][1]),2) + pow((0.5 + this->X[scenario_name][2]),2) + pow((-1.2 + this->X[scenario_name][3]),2) + pow((0.2 + this->X[scenario_name][4]),2)
                            + pow((-1.1 + this->X[scenario_name][5]),2) + pow((0.1 + this->X[scenario_name][6]),2));
        this->F[scenario_name]={objective,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11,nc1,nc2,nc3,nc4,nc5,nc6,nc7,nc8,nc9,nc10,nc11};
    }
}
void Ex844Model::buildFullModelDAG(){
    // for full model solve we will stay in scenario 1
    int n_first_stage_vars = this->first_stage_IX.size();
    int nvars = this->first_stage_IX.size()+this->second_stage_IX.size();
    int n_second_stage_vars = this->second_stage_IX.size()/this->scenario_names.size(); // number of second stage variables per scenario
    this->X[ScenarioNames::SCENARIO1].resize(this->first_stage_IX.size() +this->second_stage_IX.size());
    

    for (int i = 0; i < n_first_stage_vars; ++i) this->X[ScenarioNames::SCENARIO1][i].set(&this->DAG[ScenarioNames::SCENARIO1]);
    for (int s_idx=0; s_idx<this->scenario_names.size(); ++s_idx){
        int second_stage_start_idx = n_first_stage_vars + s_idx * n_second_stage_vars;
        for (int i = 0; i < n_second_stage_vars; ++i){
            this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+i].set(&this->DAG[ScenarioNames::SCENARIO1]);
        }
    }
    mc::FFVar objective=0;
    for (int s_idx=0; s_idx<this->scenario_names.size(); ++s_idx){
        int second_stage_start_idx = n_first_stage_vars + s_idx * n_second_stage_vars;

        // scenario perturbation
        double p = this->perturb[this->scenario_names[s_idx]];
        // Constraints translated from the Pyomo example (indices assume:
        // X[0]=m.x6, X[1]=m.x7, X[2]=m.x8, X[3]=m.x9,X[4]=m.x10, X[5]=m.x11,
        // X[6]=m.x12, X[7]=m.x13, X[8]=m.x14, X[9]=m.x15, X[10]=m.x16,X[11]=m.x17
        // X[12]=m.x1[s], X[13]=m.x2[s], X[14]=m.x3[s], X[15]=m.x4[s], X[16]=m.x5[s])
        // Constraints (mapped from the Pyomo model)
        mc::FFVar c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11;
        mc::FFVar nc1,nc2,nc3,nc4,nc5,nc6,nc7,nc8,nc9,nc10,nc11;


        double scale=1;
        c1=this->X[ScenarioNames::SCENARIO1][8]-pow(0.628318,this->X[ScenarioNames::SCENARIO1][9])*(this->X[ScenarioNames::SCENARIO1][1] - this->X[ScenarioNames::SCENARIO1][7]);
        c1=scale*c1;
        nc1=-c1;


        c2=this->X[ScenarioNames::SCENARIO1][8] -pow(0.7853975,this->X[ScenarioNames::SCENARIO1][9])* (this->X[ScenarioNames::SCENARIO1][3] - this->X[ScenarioNames::SCENARIO1][7]);
        c2=scale*c2;
        nc2=-c2;


        c3=this->X[ScenarioNames::SCENARIO1][8]-pow(0.942477,this->X[ScenarioNames::SCENARIO1][9])*( this->X[ScenarioNames::SCENARIO1][5] - this->X[ScenarioNames::SCENARIO1][7]);
        c3=scale*c3;
        nc3=-c3;


        c4=- this->X[ScenarioNames::SCENARIO1][11]-pow(0.4712385,this->X[ScenarioNames::SCENARIO1][9]) * (this->X[ScenarioNames::SCENARIO1][0] - 0.4712385*this->X[ScenarioNames::SCENARIO1][10]);
        c4=scale*c4;
        nc4=-c4;


        c5=- this->X[ScenarioNames::SCENARIO1][11]-pow(0.628318,this->X[ScenarioNames::SCENARIO1][9]) * (this->X[ScenarioNames::SCENARIO1][2] - 0.628318*this->X[ScenarioNames::SCENARIO1][10]);
        c5=scale*c5;
        nc5=-c5;

    
        c6=- this->X[ScenarioNames::SCENARIO1][11]-pow(0.7853975,this->X[ScenarioNames::SCENARIO1][9]) * (this->X[ScenarioNames::SCENARIO1][4] - 0.7853975*this->X[ScenarioNames::SCENARIO1][10]);
        c6=scale*c6;
        nc6=-c6;

    
        c7=- this->X[ScenarioNames::SCENARIO1][11]-pow(0.942477,this->X[ScenarioNames::SCENARIO1][9]) * (this->X[ScenarioNames::SCENARIO1][6] - 0.942477*this->X[ScenarioNames::SCENARIO1][10]);
        c7=scale*c7;
        nc7=-c7;


        c8=this->X[ScenarioNames::SCENARIO1][8]-pow(0.1570795,this->X[ScenarioNames::SCENARIO1][9]) * (this->X[ScenarioNames::SCENARIO1][second_stage_start_idx] - this->X[ScenarioNames::SCENARIO1][7]+p);
        c8=scale*c8;
        nc8=-c8;

        c9=this->X[ScenarioNames::SCENARIO1][8]-pow(0.314159,this->X[ScenarioNames::SCENARIO1][9]) * (this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+2] - this->X[ScenarioNames::SCENARIO1][7]+p);
        c9=scale*c9;
        nc9=-c9;


        c10=this->X[ScenarioNames::SCENARIO1][8]-pow(0.4712385,this->X[ScenarioNames::SCENARIO1][9]) * (this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+4] - this->X[ScenarioNames::SCENARIO1][7]+p);
        c10=scale*c10;
        nc10=-c10;

        c11=- this->X[ScenarioNames::SCENARIO1][11]-pow(0.1570795,this->X[ScenarioNames::SCENARIO1][9]) * (this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+1] - 0.1570795*this->X[ScenarioNames::SCENARIO1][10]);
        c11=scale*c11;
        nc11=-c11;




        objective +=1000*this->probability*(pow((-5 + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx]),2) + pow((5 + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+1]),2) + pow((-3 + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+2]),2) + pow((2 + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+3]),2) + pow((-2 + this->X[ScenarioNames::SCENARIO1][second_stage_start_idx+4]),2)
                            + pow((1 + this->X[ScenarioNames::SCENARIO1][0]),2) + pow((-1.5 + this->X[ScenarioNames::SCENARIO1][1]),2) + pow((0.5 + this->X[ScenarioNames::SCENARIO1][2]),2) + pow((-1.2 + this->X[ScenarioNames::SCENARIO1][3]),2) + pow((0.2 + this->X[ScenarioNames::SCENARIO1][4]),2)
                            + pow((-1.1 + this->X[ScenarioNames::SCENARIO1][5]),2) + pow((0.1 + this->X[ScenarioNames::SCENARIO1][6]),2));
        std::vector<mc::FFVar> scenario_constraints = {nc1,nc2,nc3,nc4,nc5,nc6,nc7,nc8,nc9,nc10,nc11,c1,c2,c3,c4,c5,c6,c7,c8,c9,c10,c11};
        this->F[ScenarioNames::SCENARIO1].insert(this->F[ScenarioNames::SCENARIO1].end(), scenario_constraints.begin(), scenario_constraints.end());
    }
    this->F[ScenarioNames::SCENARIO1].insert(this->F[ScenarioNames::SCENARIO1].begin(), objective);
}
Ipopt::SmartPtr<STModel> Ex844Model::clone(solveFullmodel flag){
    Ipopt::SmartPtr<Ex844Model> p = new Ex844Model();

    p->scenario_name=this->scenario_name;
    p->first_stage_IX=this->first_stage_IX;
    p->second_stage_IX=this->second_stage_IX;
    p->perturb=this->perturb;
    p->scenario_names=this->scenario_names;
    p->probability=this->probability;
    p->clearDAG(); // clear the DAG of the cloned model
    if (flag == solveFullmodel::no){
        p->buildDAG(); // build the model for the cloned model
    }else{
        p->buildFullModelDAG(); // build the full model for the cloned model
    }

    return p;
}
