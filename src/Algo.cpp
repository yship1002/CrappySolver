#include "Algo.h"
Algo::Algo(STModel* model,double provided_UBD) {
    this->model = model;
    this->best_solution = std::numeric_limits<double>::infinity();
    this->activeNodes.push_back(BBNode(this->model->first_stage_IX,this->model->second_stage_IX,this->model->branching_strategy));
    this->activeNodes[0].is_second_stage_BBnode = false;
    this->provided_UBD = provided_UBD;
}
int Algo::getTotalSolverNodes() {
    if (this->solver_iterations.size()==this->iterations) {
        throw std::runtime_error("Solver iterations size matches Algo iterations");
    }
    int total_nodes = 0;

    for (const auto& iter : this->solver_iterations) {
        for (const auto& count : iter) {
            total_nodes += count;
        }
    }
    return total_nodes;
}
int Algo::getWorstNodeIdx() {
    double worstLBD = std::numeric_limits<double>::infinity();
    int worstNodeIdx = 0;
    for (size_t i = 0; i < this->activeNodes.size(); ++i) {
        if (this->activeNodes[i].LBD < worstLBD) {
            worstLBD = this->activeNodes[i].LBD;
            worstNodeIdx = i;
        }
    }
    return worstNodeIdx;
}


double Algo::getBestUBD() {
    double bestUBD = std::numeric_limits<double>::infinity();
    for (const auto& node : this->activeNodes) {
        if (node.UBD < bestUBD) {
            bestUBD = node.UBD;
        }
    }
    return bestUBD;
}

double Algo::getWorstLBD() {
    double worstLBD = std::numeric_limits<double>::infinity();
    for (const auto& node : this->activeNodes) {
        if (node.LBD < worstLBD) {
            worstLBD = node.LBD;
        }
    }
    return worstLBD;
}

void Algo::fathomNodes(double UBD) {
    this->activeNodes.erase(
        std::remove_if(this->activeNodes.begin(), this->activeNodes.end(),
                       [UBD](const BBNode& node) { return node.LBD >= UBD; }),
        this->activeNodes.end());
}
double Algo::solve(double tolerance) {

    auto start = std::chrono::high_resolution_clock::now();
    this->bestUBD= this->calculateUBD(&(this->activeNodes[0]), tolerance);
    this->worstLBD = this->calculateLBD(&(this->activeNodes[0]), tolerance);
    if (this->model->branching_strategy==BranchingStrategy::pseudo){
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Started Outside Strong Branching"<<std::endl;
        std::cout<<"========================================"<<std::endl;
        this->strongbranching(&(this->activeNodes[0]), tolerance);
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Finished Outside Strong Branching"<<std::endl;
        std::cout<<"========================================"<<std::endl;
    }

    double gap = (this->bestUBD - this->worstLBD)/std::abs(this->bestUBD); // abs gap calculation
    this->iterations=0;
    while (gap > tolerance) {
        if (this->activeNodes.empty()) {
            break; // No more nodes to process
        }
        //get worst node idx
        int idx=this->getWorstNodeIdx();

        //branch node at idx
        int branch_var_idx= this->branchNodeAtIdx( idx,tolerance);


        //update UBD of nodeList and fathom by inf or value dominance
        this->bestUBD= this->getBestUBD();
        this->fathomNodes(this->bestUBD);
        this->worstLBD=this->getWorstLBD();

        // update gap
        gap = (this->bestUBD - this->worstLBD)/std::abs(this->bestUBD); // relative gap
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout<<"----------------------------------------"<<std::endl;
        std::cout<<"Iteration "<<this->iterations<<std::endl;
        std::cout<<"----------------------------------------"<<std::endl;
        std::cout<<"Current UBD: "<<this->bestUBD<<", LBD: "<<this->worstLBD<<", Gap: "<<100*gap<<"%"<<" Total Wall Time: " << elapsed.count() << " seconds" << std::endl;
        std::cout<<"Current solver Nodes: "<<this->getTotalSolverNodes()<<std::endl;

        this->iterations++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout<<"========================================"<<std::endl;
    std::cout<<"Algorithm terminated after "<<this->iterations<<" iterations."<<std::endl;
    std::cout<<"Total Wall Time: " << elapsed.count() << " seconds" << std::endl;
    std::cout<<"Total solver Nodes: "<<this->getTotalSolverNodes()<<std::endl;
    std::cout<<"Best Solution: " << this->bestUBD << std::endl;

    return this->bestUBD;
}

void Algo::strongbranching(BBNode* node,double tolerance){
    double original_LBD=node->LBD;
    double original_UBD=node->UBD;
    int iterator=0;
    while (iterator < node->first_stage_IX.size()) { // use while loop to allow restrongbranching when infeasibility detected
        BBNode child1 = *node;
        BBNode child2 = *node;
        double branch_point = (node->first_stage_IX[iterator].l() + node->first_stage_IX[iterator].u()) / 2.0;
        double range=branch_point - node->first_stage_IX[iterator].l();
        child1.first_stage_IX[iterator] = mc::Interval(child1.first_stage_IX[iterator].l(), branch_point);
        child2.first_stage_IX[iterator] = mc::Interval(branch_point, child2.first_stage_IX[iterator].u());
        
        double left_LBD=this->calculateLBD(&child1, tolerance); 

        double right_LBD=this->calculateLBD(&child2, tolerance);

        if (left_LBD == INFINITY){
            node->first_stage_IX[iterator] = mc::Interval(branch_point,node->first_stage_IX[iterator].u());
            left_LBD=original_UBD;
        }
        if (right_LBD == INFINITY){
            node->first_stage_IX[iterator] = mc::Interval(node->first_stage_IX[iterator].l(),branch_point);
            right_LBD=original_UBD;
        }

        double left_improve = left_LBD - original_LBD;
        double right_improve = right_LBD -original_LBD;
        left_improve /= range;
        right_improve /= range;

        node->branchheuristic.updateWeights(iterator, left_improve, right_improve);
        iterator++;
    }

    if (node->is_second_stage_BBnode){
        iterator=0;
        while (iterator < node->second_stage_IX.size()) {
            BBNode child3 = *node;
            BBNode child4 = *node;
            double branch_point = (node->second_stage_IX[iterator].l() + node->second_stage_IX[iterator].u()) / 2.0;
            double range=branch_point - node->second_stage_IX[iterator].l();
            child3.second_stage_IX[iterator] = mc::Interval(child3.second_stage_IX[iterator].l(), branch_point);
            child4.second_stage_IX[iterator] = mc::Interval(branch_point, child4.second_stage_IX[iterator].u());

            double left_LBD=this->calculateLBD(&child3, tolerance); 

            double right_LBD=this->calculateLBD(&child4, tolerance); 
            
            
            if (left_LBD == INFINITY){
                node->second_stage_IX[iterator] = mc::Interval(branch_point,node->second_stage_IX[iterator].u());
                left_LBD=original_UBD;
            }
            if (right_LBD == INFINITY){
                node->second_stage_IX[iterator] = mc::Interval(node->second_stage_IX[iterator].l(),branch_point);
                right_LBD=original_UBD;

            }
            double left_improve = left_LBD - original_LBD;
            double right_improve = right_LBD -original_LBD;
            left_improve /= range;
            right_improve /= range;

            node->branchheuristic.updateWeights(iterator+node->first_stage_IX.size(), left_improve, right_improve);
            iterator++;
        }
    }
};
int Algo::branchNodeAtIdx(int idx,double tolerance) {
    double original_LBD= this->activeNodes[idx].LBD;
    BBNode child1 = this->activeNodes[idx]; // Copy current node
    BBNode child2 = this->activeNodes[idx]; // Copy current node
    int size_first_stage=this->activeNodes[idx].first_stage_IX.size();
    int branch_idx;
    double branch_point;
    double range;
    if (this->activeNodes[idx].is_second_stage_BBnode){ // A second stage BBnode processing
        branch_idx = this->activeNodes[idx].branchheuristic.getBranchingVarIndex(this->activeNodes[idx].first_stage_IX, this->activeNodes[idx].second_stage_IX);
        branch_point = this->activeNodes[idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[idx].first_stage_IX, this->activeNodes[idx].second_stage_IX);
        if (branch_idx>= size_first_stage){ // decide to branch on second stage
            range=branch_point-this->activeNodes[idx].second_stage_IX[branch_idx-size_first_stage].l();
            child1.second_stage_IX[branch_idx-size_first_stage] = mc::Interval(child1.second_stage_IX[branch_idx-size_first_stage].l(), branch_point);
            child2.second_stage_IX[branch_idx-size_first_stage] = mc::Interval(branch_point, child2.second_stage_IX[branch_idx-size_first_stage ].u());
        }else{ // decide to branch on first stage
            range=branch_point-this->activeNodes[idx].first_stage_IX[branch_idx].l();
            child1.first_stage_IX[branch_idx] = mc::Interval(child1.first_stage_IX[branch_idx].l(), branch_point);
            child2.first_stage_IX[branch_idx] = mc::Interval(branch_point, child2.first_stage_IX[branch_idx].u());
        }
    }else{ //A first stage BBnode processing
        branch_idx = this->activeNodes[idx].branchheuristic.getBranchingVarIndex(this->activeNodes[idx].first_stage_IX);
        branch_point = this->activeNodes[idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[idx].first_stage_IX, this->activeNodes[idx].second_stage_IX);
        range=branch_point-this->activeNodes[idx].first_stage_IX[branch_idx].l();
        child1.first_stage_IX[branch_idx] = mc::Interval(child1.first_stage_IX[branch_idx].l(), branch_point);
        child2.first_stage_IX[branch_idx] = mc::Interval(branch_point, child2.first_stage_IX[branch_idx].u());
    }

    
    this->calculateLBD(&child1, tolerance);
    this->calculateLBD(&child2, tolerance);

    child1.UBD = this->activeNodes[idx].UBD; // pass parent UBD to children is valid for proof of concept
    child2.UBD = this->activeNodes[idx].UBD; // potentially do beeter if actual calculate

    if (child1.LBD == INFINITY){
        child1.branchheuristic.updateWeights(branch_idx,
            (this->bestUBD - original_LBD)/range, (child2.LBD - original_LBD)/range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
        child2.branchheuristic.updateWeights(branch_idx,
            (this->bestUBD - original_LBD)/range, (child2.LBD - original_LBD)/range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
    
    }else if (child2.LBD == INFINITY){
        child1.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD)/range, (this->bestUBD - original_LBD)/range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
        child2.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD)/range, (this->bestUBD - original_LBD)/range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
    
    }else{
        child1.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD)/range, (child2.LBD - original_LBD)/range);
        child2.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD)/range, (child2.LBD - original_LBD)/range);
    }

    this->activeNodes.erase(this->activeNodes.begin() + idx);
    this->activeNodes.push_back(child1);
    this->activeNodes.push_back(child2);
    return branch_idx;
}
double Algo::calculateLBD(BBNode* node,double tolerance) {
    // this is the inner layer
    double totalLBD = 0.0;
    std::vector<int> temp;
    for (auto scenario_name : this->model->scenario_names) {
        this->model->scenario_name = scenario_name;
        this->model->first_stage_IX = node->first_stage_IX;
        this->model->second_stage_IX = node->second_stage_IX;
        insideAlgo inneralgo(this->model);

        totalLBD += inneralgo.solve(tolerance);  // increase tolerance tightness for inner layer
        temp.push_back(inneralgo.iterations);
    }
    this->solver_iterations.push_back(temp);
    node->LBD = totalLBD;
    return totalLBD;

}
double Algo::calculateUBD(BBNode* node,double tolerance) {
    if (this->provided_UBD==INFINITY){
        throw std::runtime_error("No provided UBD for outer layer UBD calculation");
    }
    node->UBD = this->provided_UBD;
    return this->provided_UBD;
}
insideAlgo::insideAlgo(STModel* model) : Algo(model) {
    this->activeNodes[0].is_second_stage_BBnode = true;
}
double insideAlgo::solve(double tolerance) {
    this->bestUBD = this->calculateUBD(&(this->activeNodes[0]), tolerance);
    this->worstLBD = this->calculateLBD(&(this->activeNodes[0]), tolerance);

    if (this->model->branching_strategy==BranchingStrategy::pseudo){
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Started Inside Strong Branching"<<std::endl;
        std::cout<<"========================================"<<std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        this->strongbranching(&(this->activeNodes[0]), tolerance);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Finished Inside Strong Branching"<<std::endl;
        std::cout<<"Strong branching Time: " << elapsed.count() << " seconds" << std::endl;
        std::cout<<"========================================"<<std::endl;
    }
    

    double gap = (this->bestUBD - this->worstLBD)/std::abs(this->bestUBD);
    this->iterations = 0;
 
    while (gap > tolerance) {
        if (this->activeNodes.empty()) {
            break;
        }
        
        int idx = this->getWorstNodeIdx();
        this->branchNodeAtIdx(idx, tolerance);
        this->bestUBD = this->getBestUBD();

        this->fathomNodes(this->bestUBD);
        this->worstLBD = this->getWorstLBD();

        gap = (this->bestUBD - this->worstLBD) / std::abs(this->bestUBD);
        
        std::cout<<"Inside Iteration "<<this->iterations<<": Current UBD: "<<this->bestUBD<<", LBD: "<<this->worstLBD<<", Gap: "<<100*gap<<"%"<<std::endl;

        this->iterations++;
    }
    return this->bestUBD;
}

double insideAlgo::calculateLBD(BBNode* node,double tolerance) {

    this->model->first_stage_IX = node->first_stage_IX;
    this->model->second_stage_IX = node->second_stage_IX;
    try{
        ILOSTLBEGIN
        IloEnv env;
        env.setOut(env.getNullStream());
        env.setWarning(env.getNullStream());
        IloModel cplexmodel(env);
        IloRangeArray c(env);
        IloObjective obj (env);
        IloNumVarArray x(env);

        this->model->generateFullLP(&env,&cplexmodel,&c,&obj,&x);
        IloCplex cplex(cplexmodel);
        cplex.setParam(IloCplex::Param::ClockType, 2);
        cplex.setParam(IloCplex::Param::Simplex::Tolerances::Optimality, tolerance);

        //cplex.exportModel("/Users/jyang872/Desktop/CrappySolver/test.lp");
        cplex.setOut(env.getNullStream());

        cplex.solve();
        if (cplex.getStatus() == IloAlgorithm::Optimal) {
            node->LBD= cplex.getObjValue();
        }else if (cplex.getStatus() == IloAlgorithm::Infeasible) {
                node->LBD=INFINITY; // assign big number for infeasibility
        }
        env.end();
    } catch (IloException& e) {
        std::cerr << "CPLEX exception: " << e << "\n";
    }

    return node->LBD;

}
double insideAlgo::calculateUBD(BBNode* node,double tolerance) {
    node->UBD=-1134.15;
    return node->UBD;
    // this->model->first_stage_IX = node->first_stage_IX;
    // this->model->second_stage_IX = node->second_stage_IX;
    // //GRBEnv env = GRBEnv("genconstrnl_indexed.log");
    // GRBEnv env = GRBEnv();

    // env.set(GRB_IntParam_OutputFlag, 0);
    // env.set(GRB_IntParam_LogToConsole, 0);

    // try {
    //     GRBModel grbmodel = GRBModel(env);
    //     this->model->generateMINLP(&grbmodel);

    //     grbmodel.set(GRB_DoubleParam_MIPGap, 1e-10);  // temporarily set to tight gap for testing

    //     grbmodel.optimize();
    //     //grbmodel.write("model.sol");
    //     int status = grbmodel.get(GRB_IntAttr_Status);

    //     if (status == GRB_OPTIMAL) {
    //         double objval = grbmodel.get(GRB_DoubleAttr_ObjVal);
    //         node->UBD = objval;
    //         // std::cout << "Optimized solution values: "<<objval<<std::endl;
    //         // for (int i = 0; i <200; ++i) {
    //         //     std::string auxName = "x" + std::to_string(i);
                    
    //         //         // 1. Get the variable object
    //         //     GRBVar auxVar = grbmodel.getVarByName(auxName);
    //         //     double value = auxVar.get(GRB_DoubleAttr_X);
    //         //     std::cout << "Variable " << auxName << " = " << value << "\n";
    //         // }
    //         return objval;
    //     }

    //     if (status == GRB_INFEASIBLE) {
    //         std::cout << "Gurobi model infeasible (status=" << status << ").\n";
    //     } else if (status == GRB_UNBOUNDED) {
    //         std::cout << "Gurobi model unbounded (status=" << status << ").\n";
    //     }else {
    //         std::cout << "Gurobi optimization ended with status " << status << ".\n";
    //     }
    // } catch (GRBException& e) {
    //     std::cerr << "Gurobi exception: code=" << e.getErrorCode() << " message=" << e.getMessage() << "\n";
    // }

    // node->UBD = INFINITY;
    // return INFINITY;
}
