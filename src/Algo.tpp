#ifndef Algo_TPP
#define Algo_TPP
// ----- MPI master/worker protocol for outsideAlgo -----
enum class OutsideCmd : int {
    STOP = 0,
    CALC_LBD = 1
};

static inline void pack_bounds(
    const std::vector<mc::Interval>& first,
    const std::vector<mc::Interval>& second,
    std::vector<double>& buf
){
    buf.clear();
    buf.reserve(2 * (first.size() + second.size()));
    for (const auto& it : first) { buf.push_back(it.l()); buf.push_back(it.u()); }
    for (const auto& it : second){ buf.push_back(it.l()); buf.push_back(it.u()); }
}

static inline void unpack_bounds(
    int n1, int n2,
    const std::vector<double>& buf,
    std::vector<mc::Interval>& first,
    std::vector<mc::Interval>& second
){
    first.resize(n1);
    second.resize(n2);
    int k = 0;
    for (int i=0;i<n1;i++){ first[i] = mc::Interval(buf[k], buf[k+1]); k += 2; }
    for (int i=0;i<n2;i++){ second[i]= mc::Interval(buf[k], buf[k+1]); k += 2; }
}
template<typename T>
Algo<T>::Algo(STModel* model) {
    this->tracker = Tracker();
    this->model = model;
}
template<typename T>
int Algo<T>::getWorstNodeIdx() {
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
template<typename T>
double Algo<T>::getBestUBD() {
    double bestUBD = std::numeric_limits<double>::infinity();
    for (const auto& node : this->activeNodes) {
        if (node.UBD < bestUBD) {
            bestUBD = node.UBD;
        }
    }
    return bestUBD;
}

template<typename T>
double Algo<T>::getWorstLBD() {
    double worstLBD = std::numeric_limits<double>::infinity();
    for (const auto& node : this->activeNodes) {
        if (node.LBD < worstLBD) {
            worstLBD = node.LBD;
        }
    }
    return worstLBD;
}

template<typename T>
void Algo<T>::fathomNodes(double UBD) {
    this->activeNodes.erase(
        std::remove_if(this->activeNodes.begin(), this->activeNodes.end(),
                       [UBD](const T& node) { return node.LBD >= UBD; }),
        this->activeNodes.end());
}

outsideAlgo::outsideAlgo(STModel* model,double provided_UBD,UBDSolver solver) : Algo<BBNode>(model) {
    this->ubd_solver = solver;
    this->bestUBD = provided_UBD;
    this->activeNodes.push_back(BBNode(model->first_stage_IX,model->second_stage_IX,model->branching_strategy));


}
double outsideAlgo::cheatstrongbranching(BBNode* node,double tolerance){
    double new_LBD=0.0;
    for (auto& scenario_name : this->model->scenario_names){
        this->model->scenario_name=scenario_name;
        this->model->first_stage_IX=node->first_stage_IX;
        this->model->second_stage_IX=node->second_stage_IX;
        insideAlgo temp_inside_algo(this->model,scenario_name,INFINITY,solveFullmodel::no,UBDSolver::GUROBI);
        new_LBD+=temp_inside_algo.calculateUBD(&(temp_inside_algo.activeNodes[0]),tolerance,withinStrongBranching::yes);
    }
    return new_LBD;
}
void outsideAlgo::strongbranching(BBNode* node,double tolerance){
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

        double left_LBD=this->cheatstrongbranching(&child1,tolerance); // this is real world version
        double right_LBD=this->cheatstrongbranching(&child2,tolerance);
        //double left_LBD=this->calculateLBD(&child1,tolerance,withinStrongBranching::yes); // this is real world version
        //double right_LBD=this->calculateLBD(&child2,tolerance,withinStrongBranching::yes);

        if (left_LBD == INFINITY){
            // left child is infeasible, right child no improve split one more time
            if (right_LBD==INFINITY){
                // both child are infeasible, this is an infeasible problem
                node->LBD=INFINITY;
                return;
            }
            if (right_LBD==node->LBD){
                // left child is infeasible, right child no improve, further split the range
                node->first_stage_IX[iterator] = mc::Interval(branch_point,node->first_stage_IX[iterator].u());
                continue; // rebranch on the same variable again further split
            }else{
                // left child is infeasible, right child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator, original_UBD-original_LBD, right_LBD-original_LBD,range);
                }else{
                    node->branchheuristic.updateWeights(iterator, 0, right_LBD-original_LBD,range);
                }
            }
            // reduce range
            node->first_stage_IX[iterator] = mc::Interval(branch_point,node->first_stage_IX[iterator].u());
        }else if (right_LBD == INFINITY){
            // right child is infeasible, left child no improve
            if (left_LBD==node->LBD){
                node->first_stage_IX[iterator] = mc::Interval(node->first_stage_IX[iterator].l(), branch_point);
                continue; // rebranch on the same variable again further split
            }else{
                // right child is infeasible, left child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator, left_LBD-original_LBD, original_UBD-original_LBD,range);
                }else{
                    node->branchheuristic.updateWeights(iterator, left_LBD-original_LBD, 0,range);
                }
            }
            // reduce range
            node->first_stage_IX[iterator] = mc::Interval(node->first_stage_IX[iterator].l(),branch_point);
        }else{
            // both child are feasible
            node->branchheuristic.updateWeights(iterator, left_LBD-original_LBD, right_LBD-original_LBD,range);
        }

        iterator++;
    }
}
int outsideAlgo::branchNodeAtIdx(int idx,double tolerance,withinStrongBranching flag) {
    double original_LBD= this->activeNodes[idx].LBD;
    BBNode child1 = this->activeNodes[idx]; // Copy current node
    BBNode::node_counter++; // Increment node index for child nodes
    child1.node_id = BBNode::node_counter; // Assign unique ID to child1
    BBNode child2 = this->activeNodes[idx]; // Copy current node
    BBNode::node_counter++; // Increment node index for child nodes
    child2.node_id = BBNode::node_counter; // Assign unique ID to child2
   
    int branch_idx = this->activeNodes[idx].branchheuristic.getBranchingVarIndex(this->activeNodes[idx].first_stage_IX);
    std::cout<<"Branching on first stage variable index: "<<branch_idx<<std::endl;
    double branch_point = this->activeNodes[idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[idx].first_stage_IX,this->activeNodes[idx].second_stage_IX);
    double range=branch_point-this->activeNodes[idx].first_stage_IX[branch_idx].l();
    child1.first_stage_IX[branch_idx] = mc::Interval(this->activeNodes[idx].first_stage_IX[branch_idx].l(), branch_point);
    child2.first_stage_IX[branch_idx] = mc::Interval(branch_point, this->activeNodes[idx].first_stage_IX[branch_idx].u());

    // processing left child


    this->calculateLBD_MPI(&child1, tolerance, flag);
    std::vector<std::pair<double, double>> initial_first_stage_IX_record; // record the first stage IX for child1
    for (const auto& interval : child1.first_stage_IX) {
        initial_first_stage_IX_record.push_back({interval.l(), interval.u()});
    }
    this->first_stage_IX_record.push_back(initial_first_stage_IX_record);

    // processing right child
    this->calculateLBD_MPI(&child2, tolerance, flag);

    initial_first_stage_IX_record.clear();
    for (const auto& interval : child2.first_stage_IX) {
        initial_first_stage_IX_record.push_back({interval.l(), interval.u()});
    }
    this->first_stage_IX_record.push_back(initial_first_stage_IX_record);
 


    if (child1.LBD == INFINITY){
        // left child is infeasible, right child infeasible
        if (child2.LBD == INFINITY){
            // no need to update heuristic if both child are infeasible
        }else{
            // left child is infeasible, right child improve
            if (this->bestUBDforInfinity){
                child1.branchheuristic.updateWeights(branch_idx,
                            this->bestUBD-original_LBD, (child2.LBD - original_LBD),range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
                child2.branchheuristic.updateWeights(branch_idx,
                            this->bestUBD-original_LBD, (child2.LBD - original_LBD),range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
            }else{
                child1.branchheuristic.updateWeights(branch_idx,
                    0, (child2.LBD - original_LBD),range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
                child2.branchheuristic.updateWeights(branch_idx,
                    0, (child2.LBD - original_LBD),range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
        
            }
        }
    }else if (child2.LBD == INFINITY){
        // right child is infeasible, left child improve
        if (this->bestUBDforInfinity){
            child1.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), this->bestUBD-original_LBD,range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
            child2.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), this->bestUBD-original_LBD,range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
        }else{

            child1.branchheuristic.updateWeights(branch_idx,
                (child1.LBD - original_LBD), 0,range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
            child2.branchheuristic.updateWeights(branch_idx,
                (child1.LBD - original_LBD), 0,range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
        }
    }else{
        // both child are feasible
        child1.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), (child2.LBD - original_LBD),range);
        child2.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), (child2.LBD - original_LBD),range);
    }

    this->activeNodes.erase(this->activeNodes.begin() + idx);
    this->activeNodes.push_back(child1);
    this->activeNodes.push_back(child2);
    return branch_idx;
}
double outsideAlgo::calculateUBD(BBNode* node,double tolerance,withinStrongBranching flag) {
    node->UBD = this->bestUBD;
    return node->UBD;
}
double outsideAlgo::calculateLBD(BBNode* node,double tolerance,withinStrongBranching flag) {
    // this is the inner layer
    double totalLBD = 0.0;
    int rank=0, size=1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int S = (int)this->model->scenario_names.size();
    const double inner_tol = tolerance / (2.0 * S);
    std::vector<double> local_vals(S, 0.0);
    long long local_lbd_count_sum = 0;
    long long local_ubd_count_sum = 0;
    long long local_strong_branching_ubd_calculation_count = 0;
    long long local_strong_branching_lbd_calculation_count = 0;

    for (int si = rank; si < S; si += size) {
        auto scenario_name = this->model->scenario_names[si];

        this->model->scenario_name = scenario_name;
        this->model->first_stage_IX = node->first_stage_IX;
        this->model->second_stage_IX = node->second_stage_IX;
        insideAlgo inneralgo(this->model,scenario_name,INFINITY,solveFullmodel::no,this->ubd_solver);
        inneralgo.bestUBDforInfinity=this->bestUBDforInfinity; // pass the setting for bestUBDforInfinity to inner algo

        double scenario_LBD=inneralgo.solve(inner_tol,flag); // set inner tolerance to be eps/2s
        local_vals[si] = scenario_LBD;
        local_lbd_count_sum += inneralgo.tracker.total_lbd_calculation_count;
        local_strong_branching_lbd_calculation_count += inneralgo.tracker.total_strong_branching_lbd_calculation_count;
        local_ubd_count_sum += inneralgo.tracker.total_ubd_calculation_count;
        local_strong_branching_ubd_calculation_count += inneralgo.tracker.total_strong_branching_ubd_calculation_count;
    }
    std::vector<double> all_vals(S, 0.0);
    MPI_Allreduce(local_vals.data(), all_vals.data(), S, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    long long global_lbd_count_sum = 0;
    long long global_ubd_count_sum = 0;
    long long global_strong_branching_ubd_calculation_count = 0;
    long long global_strong_branching_lbd_calculation_count = 0;
    MPI_Reduce(&local_strong_branching_ubd_calculation_count, &global_strong_branching_ubd_calculation_count,
               1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_lbd_count_sum, &global_lbd_count_sum,
               1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_ubd_count_sum, &global_ubd_count_sum,
               1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_strong_branching_lbd_calculation_count, &global_strong_branching_lbd_calculation_count,
               1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    // only rank 0 mutates node state
    if (rank == 0) {
        this->tracker.total_lbd_calculation_count += global_lbd_count_sum;
        this->tracker.total_ubd_calculation_count += global_ubd_count_sum;
        this->tracker.total_strong_branching_ubd_calculation_count += global_strong_branching_ubd_calculation_count;
        this->tracker.total_strong_branching_lbd_calculation_count += global_strong_branching_lbd_calculation_count;
        // ensure sized for ALL nodes (root, children, strong-branch temp nodes, etc.)
        if ((int)node->scenario_LBDs.size() != S) {
            node->scenario_LBDs.assign(S, -std::numeric_limits<double>::infinity());
        }

        totalLBD = 0.0;
        for (int si = 0; si < S; ++si) {
            double scenario_LBD = all_vals[si];

            // monotone nondecreasing scenario LBD across revisits
            scenario_LBD = std::max(scenario_LBD, node->scenario_LBDs[si]);
            node->scenario_LBDs[si] = scenario_LBD;

            totalLBD += scenario_LBD;
        }
    }

    // IMPORTANT: only rank 0 has the real totalLBD; others should not overwrite node->LBD meaningfully
    if (rank == 0) node->LBD = totalLBD;
    return totalLBD;

}
double outsideAlgo::calculateLBD_MPI(BBNode* node, double tolerance, withinStrongBranching flag)
{
    int rank=0, size=1;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Broadcast command
    int cmd = (int)OutsideCmd::CALC_LBD;
    MPI_Bcast(&cmd, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Broadcast payload: tol, flag, sizes, bounds
    int flag_i = (int)flag;
    int n1 = (int)node->first_stage_IX.size();
    int n2 = (int)node->second_stage_IX.size();

    MPI_Bcast(&tolerance, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&flag_i, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n1, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n2, 1, MPI_INT, 0, MPI_COMM_WORLD);

    std::vector<double> buf;
    pack_bounds(node->first_stage_IX, node->second_stage_IX, buf);
    int buf_n = (int)buf.size();
    MPI_Bcast(&buf_n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(buf.data(), buf_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Now all ranks enter the existing compute (rank 0 uses the real node)
    return this->calculateLBD(node, tolerance, (withinStrongBranching)flag_i);
}
void outsideAlgo::mpi_worker_loop()
{
    int rank=0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    while (true) {
        int cmd = 0;
        MPI_Bcast(&cmd, 1, MPI_INT, 0, MPI_COMM_WORLD);

        if (cmd == (int)OutsideCmd::STOP) {
            break;
        }

        if (cmd != (int)OutsideCmd::CALC_LBD) {
            // unknown command: safest is to abort
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        double tolerance = 0.0;
        int flag_i = 0;
        int n1 = 0, n2 = 0, buf_n = 0;

        MPI_Bcast(&tolerance, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
        MPI_Bcast(&flag_i, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&n1, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&n2, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(&buf_n, 1, MPI_INT, 0, MPI_COMM_WORLD);

        std::vector<double> buf(buf_n);
        MPI_Bcast(buf.data(), buf_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Build a local temporary node with the bounds from rank 0
        BBNode tmp;                    // requires BBNode default ctor OR provide one
        tmp.node_id = 999999;          // doesn't matter for workers
        unpack_bounds(n1, n2, buf, tmp.first_stage_IX, tmp.second_stage_IX);

        // Participate in the Allreduce-based LBD computation
        this->calculateLBD(&tmp, tolerance, (withinStrongBranching)flag_i);
    }
}
double outsideAlgo::solve(double tolerance, withinStrongBranching flag) {
        int rank=0;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank != 0) {
        this->mpi_worker_loop();
        return 0.0; // workers don't own the final objective
    }

    auto start = std::chrono::high_resolution_clock::now();

    std::cout<<"Calculating LBD for root node..."<<std::endl;
    this->worstLBD = this->calculateLBD_MPI(&(this->activeNodes[0]), tolerance, flag);
    std::cout<<"Finished calculating LBD for root node."<<std::endl;



    std::vector<std::pair<double, double>> initial_first_stage_IX_record;  // record first stage variable bound
    for (const auto& interval : this->activeNodes[0].first_stage_IX) {
        initial_first_stage_IX_record.push_back({interval.l(), interval.u()});
    }
    this->first_stage_IX_record.push_back(initial_first_stage_IX_record);
    
    
    if (this->activeNodes[0].branchheuristic.strategy==BranchingStrategy::pseudo){
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Started Outside Strong Branching"<<std::endl;
        std::cout<<"========================================"<<std::endl;
        this->strongbranching(&(this->activeNodes[0]), tolerance);
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Finished Outside Strong Branching"<<std::endl;
        std::cout<<"========================================"<<std::endl;
    }
    double gap = (this->bestUBD - this->worstLBD); // abs gap calculation
    int iterations = 0;

    while (gap >= tolerance) {
        if (this->activeNodes.empty()) {
            break; // No more nodes to process
        }
        //get worst node idx
        int idx=this->getWorstNodeIdx();

        //branch node at idx
        int branch_var_idx= this->branchNodeAtIdx( idx,tolerance,flag);


        //update UBD of nodeList and fathom by inf or value dominance

        this->fathomNodes(this->bestUBD);
        this->worstLBD=this->getWorstLBD();

        // update gap
        gap = (this->bestUBD - this->worstLBD); // absolute gap
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout<<"----------------------------------------"<<std::endl;
        std::cout<<"Iteration "<<iterations<<std::endl;
        std::cout<<"----------------------------------------"<<std::endl;
        std::cout<<"Current UBD: "<<this->bestUBD<<", LBD: "<<this->worstLBD<<", Gap: "<<gap<<" Total Wall Time: " << elapsed.count() << " seconds" << std::endl;
        std::cout<<this->tracker.total_lbd_calculation_count<<" total LBD calculations, "<<this->tracker.total_ubd_calculation_count<<" total UBD calculations."<<std::endl;
        iterations++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout<<"========================================"<<std::endl;
    std::cout<<"Algorithm terminated after "<<iterations<<" iterations."<<std::endl;
    std::cout<<"Total Wall Time: " << elapsed.count() << " seconds" << std::endl;
    std::cout<<"Best Solution: " << this->bestUBD << std::endl;
    int cmd = (int)OutsideCmd::STOP;
    MPI_Bcast(&cmd, 1, MPI_INT, 0, MPI_COMM_WORLD);

    return this->bestUBD;

}

insideAlgo::insideAlgo(STModel* model,ScenarioNames scenario_name,double provided_UBD,solveFullmodel solve_full_model_flag,UBDSolver solver) : Algo<xBBNode>(model) {
    this->scenario_name=scenario_name;
    this->provided_UBD=provided_UBD;
    this->solve_full_model_flag=solve_full_model_flag;
    this->ubd_solver = solver;
    if (this->solve_full_model_flag==solveFullmodel::yes){
        this->model->convertToCentralizedModel();
    }
    this->activeNodes.push_back(xBBNode(this->model->first_stage_IX,this->model->second_stage_IX,
        this->model->branching_strategy,this->scenario_name));

}
void insideAlgo::strongbranching(xBBNode* node,double tolerance){

    double original_LBD=node->LBD;
    double original_UBD=node->UBD;
    int iterator=0;
    // first stage strong branching
    while (iterator < node->first_stage_IX.size()) { 
        if (node->first_stage_IX[iterator].u() - node->first_stage_IX[iterator].l() < 1e-5){
             // if that variable is fixed then skip strong branching on that variable
            node->branchheuristic.updateWeights(iterator, 0, 0,1); // update pseudocost to avoid branching on this variable again
            iterator++;
            continue;
        }
        xBBNode child1 = *node;
        xBBNode child2 = *node;
        double branch_point = (node->first_stage_IX[iterator].l() + node->first_stage_IX[iterator].u()) / 2.0;
        double range=branch_point - node->first_stage_IX[iterator].l();
        child1.first_stage_IX[iterator] = mc::Interval(child1.first_stage_IX[iterator].l(), branch_point);
        child2.first_stage_IX[iterator] = mc::Interval(branch_point, child2.first_stage_IX[iterator].u());
        
        double left_LBD=this->calculateLBD(&child1, tolerance,withinStrongBranching::yes); // pass true to indicate this LBD calculation is within strong branching
        double right_LBD=this->calculateLBD(&child2, tolerance,withinStrongBranching::yes);

        if (left_LBD == INFINITY){
            if (right_LBD == INFINITY){
                node->LBD=INFINITY; // if both child are infeasible, then the node is infeasible
                return;
            }
            if (right_LBD==node->LBD){
                // left child is infeasible, right child no improve, further split the range
                node->first_stage_IX[iterator] = mc::Interval(branch_point,node->first_stage_IX[iterator].u());
                continue; // rebranch on the same variable again further split
            }else{
                // left child is infeasible, right child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator, original_UBD-original_LBD, right_LBD-original_LBD,range);
                }else{
                    node->branchheuristic.updateWeights(iterator, 0, right_LBD-original_LBD,range);
                }

            }
            // reduce range
            node->first_stage_IX[iterator] = mc::Interval(branch_point,node->first_stage_IX[iterator].u());
        }else if (right_LBD == INFINITY){
            if (left_LBD==node->LBD){
                // right child is infeasible, left child no improve, further split the range
                node->first_stage_IX[iterator] = mc::Interval(node->first_stage_IX[iterator].l(), branch_point);
                continue; // rebranch on the same variable again further split
            }else{
                // right child is infeasible, left child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator, left_LBD-original_LBD, original_UBD-original_LBD,range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
                }else{
                    node->branchheuristic.updateWeights(iterator, left_LBD-original_LBD, 0,range);
                }
            }
            // reduce range
            node->first_stage_IX[iterator] = mc::Interval(node->first_stage_IX[iterator].l(),branch_point);
        }else{
            // both child are feasible
            node->branchheuristic.updateWeights(iterator, left_LBD-original_LBD, right_LBD-original_LBD,range);
        }

        iterator++;
    }
    iterator=0;
    // second stage strong branching
    while (iterator < node->second_stage_IX.size()) { 
        if (node->second_stage_IX[iterator].u() - node->second_stage_IX[iterator].l() < 1e-5){
             // if that variable is fixed then skip strong branching on that variable
            node->branchheuristic.updateWeights(iterator+node->first_stage_IX.size(), 0, 0,1); // update pseudocost to avoid branching on this variable again
            iterator++;
            continue;
        }
        xBBNode child3 = *node;
        xBBNode child4 = *node;
        double branch_point = (node->second_stage_IX[iterator].l() + node->second_stage_IX[iterator].u()) / 2.0;
        double range=branch_point - node->second_stage_IX[iterator].l();
        child3.second_stage_IX[iterator] = mc::Interval(child3.second_stage_IX[iterator].l(), branch_point);
        child4.second_stage_IX[iterator] = mc::Interval(branch_point, child4.second_stage_IX[iterator].u());
        
        double left_LBD=this->calculateLBD(&child3, tolerance,withinStrongBranching::yes); // pass true to indicate this LBD calculation is within strong branching
        double right_LBD=this->calculateLBD(&child4, tolerance,withinStrongBranching::yes);

        if (left_LBD == INFINITY){
            if (right_LBD == INFINITY){
                node->LBD=INFINITY; // if both child are infeasible, then the node is infeasible
                return;
            }
            if (right_LBD==node->LBD){
                // left child is infeasible, right child no improve, further split the range
                node->second_stage_IX[iterator] = mc::Interval(branch_point,node->second_stage_IX[iterator].u());
                continue; // rebranch on the same variable again further split

            }else{
                // left child is infeasible, right child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator+node->first_stage_IX.size(), original_UBD-original_LBD, right_LBD-original_LBD,range);
                }else{
                    node->branchheuristic.updateWeights(iterator+node->first_stage_IX.size(), 0, right_LBD-original_LBD,range);
                }
            }
            // reduce range
            node->second_stage_IX[iterator] = mc::Interval(branch_point,node->second_stage_IX[iterator].u());
        }else if (right_LBD == INFINITY){
            if (left_LBD==node->LBD){
                // right child is infeasible, left child no improve
                node->second_stage_IX[iterator] = mc::Interval(node->second_stage_IX[iterator].l(), branch_point);
                continue; // rebranch on the same variable again further split
            }else{
                // right child is infeasible, left child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator+node->first_stage_IX.size(), left_LBD-original_LBD, original_UBD-original_LBD,range);
                }else{
                    node->branchheuristic.updateWeights(iterator+node->first_stage_IX.size(), left_LBD-original_LBD, 0,range);
                }
            }
            // reduce range
            node->second_stage_IX[iterator] = mc::Interval(node->second_stage_IX[iterator].l(),branch_point);
        }else{
            // both child are feasible
            node->branchheuristic.updateWeights(iterator+node->first_stage_IX.size(), left_LBD-original_LBD, right_LBD-original_LBD,range);
        }

        iterator++;
    }
        // if there are 0 0 improve in any first stage weigts
    double min_weight=INFINITY;
    for (auto& weight: this->activeNodes[0].branchheuristic.weights){
        double lower_weight=std::min(weight[0].first,weight[0].second);
        if (lower_weight!=0 && lower_weight<min_weight){
            min_weight=lower_weight;
        }
    }
    // go through the weights again to update 0 0 weight with minimum improve observed among other branches, this is to avoid 0 0 weight which will cause no branching on that variable in the future
    for (auto& weight: this->activeNodes[0].branchheuristic.weights){
        if (weight[0].first==0 && weight[0].second==0){
            weight[0].first=min_weight;
            weight[0].second=min_weight;
        };
    }
    
}
int insideAlgo::branchNodeAtIdx(int idx,double tolerance,withinStrongBranching flag) {
    double original_LBD= this->activeNodes[idx].LBD;
    if (original_LBD==INFINITY){
        throw std::runtime_error("Should not branch on infeasible node");
    }
    xBBNode child1 = this->activeNodes[idx]; // Copy current node
    xBBNode child2 = this->activeNodes[idx]; // Copy current node
    double range;
    int branch_idx = this->activeNodes[idx].branchheuristic.getBranchingVarIndex(this->activeNodes[idx].first_stage_IX,this->activeNodes[idx].second_stage_IX);
    
    if(branch_idx<this->activeNodes[idx].first_stage_IX.size()){

        // first stage branching
        double branch_point = this->activeNodes[idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[idx].first_stage_IX,this->activeNodes[idx].second_stage_IX);
        range=branch_point-this->activeNodes[idx].first_stage_IX[branch_idx].l();
        child1.first_stage_IX[branch_idx] = mc::Interval(this->activeNodes[idx].first_stage_IX[branch_idx].l(), branch_point);
        child2.first_stage_IX[branch_idx] = mc::Interval(branch_point, this->activeNodes[idx].first_stage_IX[branch_idx].u());
      
    }else if(branch_idx>=this->activeNodes[idx].first_stage_IX.size()){
        
        // second stage branching

        double branch_point = this->activeNodes[idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[idx].first_stage_IX,this->activeNodes[idx].second_stage_IX);
        range=branch_point-this->activeNodes[idx].second_stage_IX[branch_idx-this->activeNodes[idx].first_stage_IX.size()].l();
        child1.second_stage_IX[branch_idx-this->activeNodes[idx].first_stage_IX.size()] = mc::Interval(this->activeNodes[idx].second_stage_IX[branch_idx-this->activeNodes[idx].first_stage_IX.size()].l(), branch_point);
        child2.second_stage_IX[branch_idx-this->activeNodes[idx].first_stage_IX.size()] = mc::Interval(branch_point, this->activeNodes[idx].second_stage_IX[branch_idx-this->activeNodes[idx].first_stage_IX.size()].u());
    
    }
    this->calculateLBD(&child1, tolerance,flag);
    this->calculateLBD(&child2, tolerance,flag);

    this->calculateUBD(&child1, tolerance,flag);
    this->calculateUBD(&child2, tolerance,flag);


    if (child1.LBD == INFINITY){
        // left child is infeasible, right child infeasible
        if (child2.LBD == INFINITY){
            // no need to update heuristic if both child are infeasible
            std::cout<<"Both child are infeasible after branching on variable index "<<branch_idx<<std::endl;
            this->activeNodes.erase(this->activeNodes.begin() + idx);
            return branch_idx;
        }else{
            // left child is infeasible, right child improve

            if (this->bestUBDforInfinity){
                if (this->bestUBD == INFINITY){ // if bestUBD is infinity, we cannot update heuristic with bestUBD, no idea why this happend
                    this->activeNodes.erase(this->activeNodes.begin() + idx);
                    std::cout<<"Warning: bestUBD is infinity, cannot update heuristic with bestUBD, exiting"<<std::endl;
                    return branch_idx;

                }
                child1.branchheuristic.updateWeights(branch_idx,
                    this->bestUBD-original_LBD, (child2.LBD - original_LBD),range);
                child2.branchheuristic.updateWeights(branch_idx,
                    this->bestUBD-original_LBD, (child2.LBD - original_LBD),range);
            }else{
                child1.branchheuristic.updateWeights(branch_idx,
                    0, (child2.LBD - original_LBD),range);
                child2.branchheuristic.updateWeights(branch_idx,
                    0, (child2.LBD - original_LBD),range);
            }
        }
        
    }else if (child2.LBD == INFINITY){
        // right child is infeasible, left child improve
        if (this->bestUBDforInfinity){
            child1.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), this->bestUBD-original_LBD,range);
            child2.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), this->bestUBD-original_LBD,range);
        }else{

            child1.branchheuristic.updateWeights(branch_idx,
                (child1.LBD - original_LBD), 0,range); 
            child2.branchheuristic.updateWeights(branch_idx,
                (child1.LBD - original_LBD), 0,range);
        }
    }else{
        // both child are feasible
        child1.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), (child2.LBD - original_LBD),range);
        child2.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), (child2.LBD - original_LBD),range);
    }

    this->activeNodes.erase(this->activeNodes.begin() + idx);
    this->activeNodes.push_back(child1);
    this->activeNodes.push_back(child2);
    return branch_idx;
}
double insideAlgo::calculateLBD(xBBNode* node,double tolerance,withinStrongBranching flag) {
    auto start = std::chrono::high_resolution_clock::now();
    this->tracker.total_lbd_calculation_count++;

    this->model->scenario_name = node->scenario_name;
    this->model->first_stage_IX = node->first_stage_IX;
    this->model->second_stage_IX = node->second_stage_IX;
    this->model->clearDAG(); // remove the previous DAG to avoid interference
    if (this->solve_full_model_flag == solveFullmodel::no){
        this->model->buildDAG();
    }else{
        this->model->buildFullModelDAG();
    }
    try{
        ILOSTLBEGIN
        IloEnv env;
        env.setOut(env.getNullStream());
        env.setWarning(env.getNullStream());
        IloModel cplexmodel(env);
        IloRangeArray c(env);
        IloObjective obj (env);
        IloNumVarArray x(env);

        this->model->generateLP(&env,&cplexmodel,&c,&obj,&x);

        IloCplex cplex(cplexmodel);
        cplex.setParam(IloCplex::Param::ClockType, 2);
        cplex.setParam(IloCplex::Param::Simplex::Tolerances::Optimality, 1e-9);

        //cplex.exportModel("/Users/jyang872/Desktop/CrappySolver/test.lp");
        cplex.setOut(env.getNullStream());
        cplex.solve();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        this->tracker.total_lbd_calculation_time.push_back(elapsed.count());
        if (flag==withinStrongBranching::yes){
            this->tracker.strong_branching_lbd_calculation_count++;
            this->tracker.strong_branching_lbd_calculation_time.push_back(elapsed.count());
        }
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
double insideAlgo::calculateUBD(xBBNode* node,double tolerance,withinStrongBranching flag) {

    this->tracker.total_ubd_calculation_count++;

    auto start = std::chrono::high_resolution_clock::now();
    this->model->scenario_name = node->scenario_name;
    this->model->first_stage_IX = node->first_stage_IX;
    this->model->second_stage_IX = node->second_stage_IX;
    this->model->clearDAG(); // remove the previous DAG to avoid interference
    if (this->solve_full_model_flag == solveFullmodel::no){
        this->model->buildDAG();
    }else{
        this->model->buildFullModelDAG();
    }

    if (this->ubd_solver == UBDSolver::IPOPT){
        Ipopt::SmartPtr<Ipopt::TNLP> mynlp = this->model->clone(this->solve_full_model_flag);
        STModel* sm = dynamic_cast<STModel*>(Ipopt::GetRawPtr(mynlp));

        Ipopt::SmartPtr<Ipopt::IpoptApplication> app = IpoptApplicationFactory();
        app->Options()->SetNumericValue("tol", 1e-9);           // Optimality tolerance
        app->Options()->SetNumericValue("constr_viol_tol", 1e-9);  // Constraint feasibility
        app->Options()->SetNumericValue("compl_inf_tol", 1e-9);    // Complementarity tolerance
        app->Options()->SetIntegerValue("print_level", 0);
        app->Options()->SetStringValue("sb", "yes");
        app->Options()->SetStringValue("hessian_approximation", "limited-memory");
        app->Options()->SetStringValue("mu_strategy", "monotone");

        //app->Options()->SetStringValue("output_file", "/Users/jyang872/Desktop/CrappySolver/ipopt.out");
        Ipopt::ApplicationReturnStatus status;
        status = app->Initialize();
        if( status != Ipopt::Solve_Succeeded )
        {
            std::cout << std::endl << std::endl << "*** Error during initialization!" << std::endl;
            throw std::runtime_error("Error during IPOPT initialization");

        }

        // Ask Ipopt to solve the problem
        status = app->OptimizeTNLP(mynlp);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        this->tracker.total_ubd_calculation_time.push_back(elapsed.count());
        if (flag==withinStrongBranching::yes){
            this->tracker.strong_branching_ubd_calculation_count++;
            this->tracker.strong_branching_ubd_calculation_time.push_back(elapsed.count());
        }
        if( status == Ipopt::Solve_Succeeded )
        {
            node->UBD = sm->solution.f[0];
            return node->UBD;
        }
        else if (status == Ipopt::Infeasible_Problem_Detected)
        {
            node->UBD = INFINITY;
            return node->UBD;
        }
    }else if (this->ubd_solver == UBDSolver::GUROBI){
        GRBEnv env = GRBEnv(true); // empty environemtn to turn off annoying Gurobi output
        env.set(GRB_IntParam_OutputFlag, 0);
        env.set(GRB_IntParam_LogToConsole, 0);
        env.start();
        try {
            GRBModel grbmodel = GRBModel(env);
            this->model->generateMINLP(&grbmodel);
            grbmodel.set(GRB_IntParam_NonConvex, 2);
            grbmodel.set(GRB_DoubleParam_FeasibilityTol, 1e-4); // set feasibility tolerance to be 1e-4 for better numerical performance, can be tuned
            grbmodel.set(GRB_DoubleParam_MIPGap, 1e-10);  // temporarily set to tight gap for testing

            grbmodel.optimize();

            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            this->tracker.total_ubd_calculation_time.push_back(elapsed.count());
            if (flag==withinStrongBranching::yes){
                this->tracker.strong_branching_ubd_calculation_count++;
                this->tracker.strong_branching_ubd_calculation_time.push_back(elapsed.count());
            }

            int status = grbmodel.get(GRB_IntAttr_Status);

            if (status == GRB_OPTIMAL) {
                double objval = grbmodel.get(GRB_DoubleAttr_ObjVal);
                node->UBD = objval;
                // std::cout << "Optimized solution values: "<<objval<<std::endl;
                // for (int i = 0; i <200; ++i) {
                //     std::string auxName = "x" + std::to_string(i);
                        
                //         // 1. Get the variable object
                //     GRBVar auxVar = grbmodel.getVarByName(auxName);
                //     double value = auxVar.get(GRB_DoubleAttr_X);
                //     std::cout << "Variable " << auxName << " = " << value << "\n";
                // }

                return objval;
            }else if(status == GRB_SUBOPTIMAL){
                double objval = grbmodel.get(GRB_DoubleAttr_ObjVal);
                node->UBD = objval;
                std::cout << "Suboptimal solution values: "<<objval<<std::endl;
                return objval;
            }

            if (status == GRB_INFEASIBLE) {
                //std::cerr<<"Gurobi model infeasible (status=" + std::to_string(status) + ").\n";
            } else if (status == GRB_UNBOUNDED) {
                //std::cerr<<"Gurobi model unbounded (status=" + std::to_string(status) + ").\n";
            }else {
                //std::cerr<<"Gurobi optimization ended with status " + std::to_string(status) + ".\n";
            }
        } catch (GRBException& e) {
            std::cerr << "Gurobi exception: code=" << e.getErrorCode() << " message=" << e.getMessage() << std::endl;
        }

        node->UBD = INFINITY;
        return INFINITY;
    }else{
        throw std::runtime_error("Unsupported UBD solver");
    }
}

double insideAlgo::solve(double tolerance,withinStrongBranching flag) {
    auto start = std::chrono::high_resolution_clock::now();
    this->bestUBD = this->calculateUBD(&(this->activeNodes[0]), tolerance,flag);
    this->worstLBD = this->calculateLBD(&(this->activeNodes[0]), tolerance,flag);
    this->tracker.LBD_value_records.push_back(this->worstLBD);

    if (this->bestUBD==INFINITY || this->worstLBD==INFINITY){
        std::cout<<"Scenario "<<static_cast<int>(this->scenario_name)<<" is infeasible at root node."<<std::endl;
        return INFINITY;
    }


    if (this->activeNodes[0].branchheuristic.strategy==BranchingStrategy::pseudo){
        //std::cout<<"========================================"<<std::endl;
        //std::cout<<"Started Inside Strong Branching"<<std::endl;


        this->strongbranching(&(this->activeNodes[0]), tolerance);

        //std::cout<<"Finished Inside Strong Branching"<<std::endl;
        //std::cout<<"========================================"<<std::endl;
    }
    if (this->activeNodes[0].LBD == INFINITY){ // in rare case when strong branching detects infeasibility
        std::cout<<"Scenario "<<static_cast<int>(this->scenario_name)<<" is infeasible after strong branching at root node."<<std::endl;
        return INFINITY;
    }

    double gap = (this->bestUBD - this->worstLBD); // absolute gap calculation for inner layer

    int iterations = 0;

    while (gap >= tolerance) {

        if (this->activeNodes.empty()) {
            break;
        }
        
        int idx = this->getWorstNodeIdx();
        int branch_var_idx= this->branchNodeAtIdx( idx,tolerance,flag);
        this->worstLBD = this->getWorstLBD();
        this->bestUBD = this->getBestUBD();
        //std::cout<<"Branching variable index: "<<branch_var_idx<<std::endl;

        this->fathomNodes(this->bestUBD);
        this->worstLBD = this->getWorstLBD();
        this->bestUBD = this->getBestUBD();

        gap = (this->bestUBD - this->worstLBD); // absolute gap calculation for inner layer
        this->tracker.LBD_value_records.push_back(this->worstLBD);
        //std::cout<<"Inside Iteration "<<iterations<<": Current UBD: "<<this->bestUBD<<", LBD: "<<this->worstLBD<<", AbsGap: "<<gap<<"Tol: "<<tolerance<<std::endl;
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
        //std::cout<<"Total Wall Time: " << duration.count() << " seconds" << ", LBD calculation count: " << this->tracker.total_lbd_calculation_count-this->tracker.strong_branching_lbd_calculation_count << std::endl;
        iterations++;
        
    
    }

    std::cout<<"Scenario "<<static_cast<int>(this->scenario_name)<<" terminated after "<<iterations<<" iterations."<<std::endl;
    return this->worstLBD;

}
#endif