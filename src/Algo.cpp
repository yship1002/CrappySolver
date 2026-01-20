#include "Algo.h"
Algo::Algo(STModel& model,BranchingStrategy strategy) {
    this->model = model;
    this->best_solution = std::numeric_limits<double>::infinity();
    this->activeNodes.push_back(BBNode(this->model.first_stage_IX,this->model.second_stage_IX,strategy));

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
void Algo::branchNodeAtIdx(int idx,double tolerance) {
    
    int branch_idx = this->activeNodes[idx].branchheuristic.getBranchingVarIndex(this->activeNodes[idx].first_stage_IX);
    BBNode child1 = this->activeNodes[idx]; // Copy current node
    BBNode child2 = this->activeNodes[idx]; // Copy current node
    double branch_point = this->activeNodes[idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[idx].first_stage_IX);

    child1.first_stage_IX[branch_idx] = mc::Interval(child1.first_stage_IX[branch_idx].l(), branch_point);
    child2.first_stage_IX[branch_idx] = mc::Interval(branch_point, child2.first_stage_IX[branch_idx].u());

    
    child1.LBD = this->calculateLBD(&child1, tolerance);
    child2.LBD = this->calculateLBD(&child2, tolerance);
    child1.UBD = this->activeNodes[idx].UBD;
    child2.UBD = this->activeNodes[idx].UBD;
    this->activeNodes.erase(this->activeNodes.begin() + idx);
    this->activeNodes.push_back(child1);
    this->activeNodes.push_back(child2);

}
double Algo::solve(double tolerance) {
    auto start = std::chrono::high_resolution_clock::now();
    double UBD= this->calculateUBD(&(this->activeNodes[0]), tolerance);
    double LBD = this->calculateLBD(&(this->activeNodes[0]), tolerance);
    double gap = (UBD - LBD)/std::abs(UBD); // abs gap calculation
    this->iterations=0;
    while (gap > tolerance) {
        if (this->activeNodes.empty()) {
            break; // No more nodes to process
        }
        //get worst node idx
        int idx=this->getWorstNodeIdx();

        //branch node at idx
        this->branchNodeAtIdx(idx,tolerance);

        //update UBD of nodeList and fathom by inf or value dominance
        UBD= this->getBestUBD();
        this->fathomNodes(UBD);
        LBD=this->getWorstLBD();

        // update gap
        gap = (UBD - LBD)/std::abs(UBD); // relative gap
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout<<"----------------------------------------"<<std::endl;
        std::cout<<"Iteration "<<this->iterations<<std::endl;
        std::cout<<"----------------------------------------"<<std::endl;
        std::cout<<"Current UBD: "<<UBD<<", LBD: "<<LBD<<", Gap: "<<100*gap<<"%"<<" Total Wall Time: " << elapsed.count() << " seconds" << std::endl;
        std::cout<<"Current solver Nodes: "<<this->getTotalSolverNodes()<<std::endl;

        this->iterations++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout<<"========================================"<<std::endl;
    std::cout<<"Algorithm terminated after "<<this->iterations<<" iterations."<<std::endl;
    std::cout<<"Total Wall Time: " << elapsed.count() << " seconds" << std::endl;
    std::cout<<"Total solver Nodes: "<<this->getTotalSolverNodes()<<std::endl;
    std::cout<<"Best Solution: " << UBD << std::endl;

    return UBD;
}
double Algo::calculateLBD(BBNode* node,double tolerance) {
    // this is the inner layer
    double totalLBD = 0.0;
    std::vector<int> temp;
    for (auto scenario_name : this->model.scenario_names) {
        this->model.scenario_name = scenario_name;
        this->model.first_stage_IX = node->first_stage_IX;
        this->model.second_stage_IX = node->second_stage_IX;
        insideAlgo inneralgo(this->model,node->branchheuristic.strategy);
        totalLBD += inneralgo.solve(tolerance*0.1);  // increase tolerance tightness for inner layer
        temp.push_back(inneralgo.iterations);
    }
    this->solver_iterations.push_back(temp);
    node->LBD = totalLBD;
    return totalLBD;

}
double Algo::calculateUBD(BBNode* node,double tolerance) {

    node->UBD = -1126.4218270121305;
    return -1126.4218270121305;
}
insideAlgo::insideAlgo(STModel& model,BranchingStrategy strategy) : Algo(model,strategy) {

}
double insideAlgo::solve(double tolerance) {

    double UBD = this->calculateUBD(&(this->activeNodes[0]), tolerance);
    double LBD = this->calculateLBD(&(this->activeNodes[0]), tolerance);
    double gap = (UBD - LBD)/std::abs(UBD);
    this->iterations = 0;

    while (gap > tolerance) {
        if (this->activeNodes.empty()) {
            break;
        }
        
        int idx = this->getWorstNodeIdx();
        this->branchNodeAtIdx(idx, tolerance);
        
        UBD = this->getBestUBD();

        this->fathomNodes(UBD);
        LBD = this->getWorstLBD();
        

        gap = (UBD - LBD) / std::abs(UBD);
        this->iterations++;
    }

    return UBD;

}
void insideAlgo::branchNodeAtIdx(int idx,double tolerance) {

    int branch_idx = this->activeNodes[idx].branchheuristic.getBranchingVarIndex(this->activeNodes[idx].first_stage_IX, this->activeNodes[idx].second_stage_IX);
    BBNode child1 = this->activeNodes[idx]; // Copy current node
    BBNode child2 = this->activeNodes[idx]; // Copy current node
    double branch_point = this->activeNodes[idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[idx].first_stage_IX, this->activeNodes[idx].second_stage_IX);

    if (branch_idx >= this->activeNodes[idx].first_stage_IX.size()) {
        int second_stage_idx = branch_idx - this->activeNodes[idx].first_stage_IX.size();
        child1.second_stage_IX[second_stage_idx] = mc::Interval(child1.second_stage_IX[second_stage_idx].l(), branch_point);
        child2.second_stage_IX[second_stage_idx] = mc::Interval(branch_point, child2.second_stage_IX[second_stage_idx].u());
    } else {
        // Branching on first stage variable
        child1.first_stage_IX[branch_idx] = mc::Interval(child1.first_stage_IX[branch_idx].l(), branch_point);
        child2.first_stage_IX[branch_idx] = mc::Interval(branch_point, child2.first_stage_IX[branch_idx].u());
    }
    
    this->calculateLBD(&child1, tolerance);
    this->calculateLBD(&child2, tolerance);
    child1.UBD = this->activeNodes[idx].UBD;
    child2.UBD = this->activeNodes[idx].UBD;

    this->activeNodes.erase(this->activeNodes.begin() + idx);
    this->activeNodes.push_back(child1);
    this->activeNodes.push_back(child2);

}


double insideAlgo::calculateLBD(BBNode* node,double tolerance) {


    this->model.first_stage_IX = node->first_stage_IX;
    this->model.second_stage_IX = node->second_stage_IX;
    try{
        ILOSTLBEGIN
        IloEnv env;
        env.setOut(env.getNullStream());
        env.setWarning(env.getNullStream());
        IloModel cplexmodel(env);
        IloRangeArray c(env);
        IloObjective obj (env);
        IloNumVarArray x(env);

        this->model.generateLP(&env,&cplexmodel,&c,&obj,&x);
        IloCplex cplex(cplexmodel);
        cplex.setParam(IloCplex::Param::ClockType, 2);
        //cplex.setParam(IloCplex::Param::Simplex::Tolerances::Optimality, tol);

        //cplex.exportModel(("/Users/jyang872/Desktop/fuzzy-tribble/scenario" + std::to_string(static_cast<int>(this->model.scenario_name)) + ".lp").c_str());
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

    this->model.first_stage_IX = node->first_stage_IX;
    this->model.second_stage_IX = node->second_stage_IX;
    GRBEnv env = GRBEnv("genconstrnl_indexed.log");
    env.set(GRB_IntParam_OutputFlag, 0);

    GRBModel grbmodel = GRBModel(env);
    this->model.generateMINLP(&grbmodel);
    grbmodel.optimize();
    int status = grbmodel.get(GRB_IntAttr_Status);

    if (status == GRB_INF_OR_UNBD) {
        std::cout << "Model is infeasible.\n";
        node->UBD=INFINITY;
        return INFINITY;
    }
    double objval = grbmodel.get(GRB_DoubleAttr_ObjVal);
    node->UBD= objval;
    return objval;
}