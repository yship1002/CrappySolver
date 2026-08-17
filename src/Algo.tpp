#ifndef Algo_TPP
#define Algo_TPP

template<typename T>
Algo<T>::Algo(STModel* model) {
    this->model = model;
    this->iterations=0;
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
        insideAlgo temp_inside_algo(this->model,scenario_name,INFINITY,false,this->ubd_solver);
        new_LBD+=temp_inside_algo.calculateUBD(&(temp_inside_algo.activeNodes[0]),tolerance);
    }
    return new_LBD;
}
void outsideAlgo::strongbranching(BBNode* node,double tolerance){
    double original_LBD=this->worstLBD;
    double original_UBD=this->bestUBD;
    int iterator=0;
    while (iterator < node->first_stage_IX.size()) { // use while loop to allow restrongbranching when infeasibility detected
        BBNode child1 = *node;
        BBNode child2 = *node;
        double branch_point = (node->first_stage_IX[iterator].l() + node->first_stage_IX[iterator].u()) / 2.0;
        double range=branch_point - node->first_stage_IX[iterator].l();
        child1.first_stage_IX[iterator] = mc::Interval(child1.first_stage_IX[iterator].l(), branch_point);
        child2.first_stage_IX[iterator] = mc::Interval(branch_point, child2.first_stage_IX[iterator].u());

        double left_LBD=this->cheatstrongbranching(&child1,tolerance); // this is cheating version
        double right_LBD=this->cheatstrongbranching(&child2,tolerance); 
        //double left_LBD=this->calculateLBD(&child1,tolerance); // this is real world version
        //double right_LBD=this->calculateLBD(&child2,tolerance);

        if (left_LBD == INFINITY){
            // left child is infeasible, right child no improve split one more time
            if (right_LBD==INFINITY){
                // both child are infeasible, this is an infeasible problem
                node->LBD=INFINITY;
                return;
            }

            node->first_stage_IX[iterator] = mc::Interval(branch_point,node->first_stage_IX[iterator].u());
            continue; // rebranch on the same variable again further split
            
        }else if (right_LBD == INFINITY){

            // reduce range
            node->first_stage_IX[iterator] = mc::Interval(node->first_stage_IX[iterator].l(),branch_point);
            continue;
        }else{
            // both child are feasible
            node->branchheuristic.updateWeights(iterator, left_LBD-original_LBD, right_LBD-original_LBD,range,USE_inside_weights::NO);
        }

        iterator++;
    }
}
int outsideAlgo::branchNodeAtIdx(int idx,double tolerance) {
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
    int initial_lbd_calculation_count=insideAlgo::lbd_calculation_count;
    double initial_lbd_calculation_time=insideAlgo::lbd_calculation_time;


    this->calculateLBD(&child1, tolerance);
    this->LBD_calculation_time_records.push_back(insideAlgo::lbd_calculation_time-initial_lbd_calculation_time); // record LBD calculation time for child1
    this->LBD_calculation_records.push_back(insideAlgo::lbd_calculation_count-initial_lbd_calculation_count); // record LBD calculation count for child1
    std::vector<std::pair<double, double>> initial_first_stage_IX_record; // record the first stage IX for child1
    for (const auto& interval : child1.first_stage_IX) {
        initial_first_stage_IX_record.push_back({interval.l(), interval.u()});
    }
    this->first_stage_IX_record.push_back(initial_first_stage_IX_record);
    this->LBD_values_records.push_back(child1.LBD); // record LBD value for child1

    // processing right child
    initial_lbd_calculation_count=insideAlgo::lbd_calculation_count;
    initial_lbd_calculation_time=insideAlgo::lbd_calculation_time;


    //this->printFirstStageIX(&child2); // print first stage IX for child2 before calculating LBD


    this->calculateLBD(&child2, tolerance);
    this->LBD_calculation_time_records.push_back(insideAlgo::lbd_calculation_time-initial_lbd_calculation_time); // record LBD calculation time for child2
    this->LBD_calculation_records.push_back(insideAlgo::lbd_calculation_count-initial_lbd_calculation_count);
    initial_first_stage_IX_record.clear();
    for (const auto& interval : child2.first_stage_IX) {
        initial_first_stage_IX_record.push_back({interval.l(), interval.u()});
    }
    this->first_stage_IX_record.push_back(initial_first_stage_IX_record);
    this->LBD_values_records.push_back(child2.LBD);


    if (child1.LBD == INFINITY){
        // left child is infeasible, right child infeasible
        if (child2.LBD == INFINITY){
            // no need to update heuristic if both child are infeasible
        }else{
            // left child is infeasible, right child improve
            if (this->bestUBDforInfinity){
                child1.branchheuristic.updateWeights(branch_idx,
                            this->bestUBD-original_LBD, (child2.LBD - original_LBD),range,USE_inside_weights::NO); // set to bestUBD of this subproblem to avoid infitinity pseducost update
                child2.branchheuristic.updateWeights(branch_idx,
                            this->bestUBD-original_LBD, (child2.LBD - original_LBD),range,USE_inside_weights::NO); // set to bestUBD of this subproblem to avoid infitinity pseducost update
            }else{
                child1.branchheuristic.updateWeights(branch_idx,
                    0, (child2.LBD - original_LBD),range,USE_inside_weights::NO); // set to bestUBD of this subproblem to avoid infitinity pseducost update
                child2.branchheuristic.updateWeights(branch_idx,
                    0, (child2.LBD - original_LBD),range,USE_inside_weights::NO); // set to bestUBD of this subproblem to avoid infitinity pseducost update
        
            }
        }
    }else if (child2.LBD == INFINITY){
        // right child is infeasible, left child improve
        if (this->bestUBDforInfinity){
            child1.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), this->bestUBD-original_LBD,range,USE_inside_weights::NO); // set to bestUBD of this subproblem to avoid infitinity pseducost update
            child2.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), this->bestUBD-original_LBD,range,USE_inside_weights::NO); // set to bestUBD of this subproblem to avoid infitinity pseducost update
        }else{

            child1.branchheuristic.updateWeights(branch_idx,
                (child1.LBD - original_LBD), 0,range,USE_inside_weights::NO); // set to bestUBD of this subproblem to avoid infitinity pseducost update
            child2.branchheuristic.updateWeights(branch_idx,
                (child1.LBD - original_LBD), 0,range,USE_inside_weights::NO); // set to bestUBD of this subproblem to avoid infitinity pseducost update
        }
    }else{
        // both child are feasible
        child1.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), (child2.LBD - original_LBD),range,USE_inside_weights::NO);
        child2.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), (child2.LBD - original_LBD),range,USE_inside_weights::NO);
    }

    this->activeNodes.erase(this->activeNodes.begin() + idx);
    this->activeNodes.push_back(child1);
    this->activeNodes.push_back(child2);
    return branch_idx;
}
double outsideAlgo::calculateUBD(BBNode* node,double tolerance) {
    node->UBD = this->bestUBD;
    return node->UBD;
}
double outsideAlgo::calculateLBD(BBNode* node,double tolerance,bool verbose) {
    // this is the inner layer
    double totalLBD = 0.0;

    for (auto scenario_name : this->model->scenario_names) {

        this->model->scenario_name = scenario_name;
        this->model->first_stage_IX = node->first_stage_IX;
        this->model->second_stage_IX = node->second_stage_IX;
        insideAlgo inneralgo(this->model,scenario_name,INFINITY,false,this->ubd_solver);
        inneralgo.bestUBDforInfinity=this->bestUBDforInfinity; // pass the setting for bestUBDforInfinity to inner algo
        //double scenario_LBD = inneralgo.calculateUBD(&(inneralgo.activeNodes[0]),tolerance/(2*this->model->scenario_names.size())); // set inner tolerance to be eps/2s
        double scenario_LBD=inneralgo.solve(tolerance/(2*this->model->scenario_names.size())); // set inner tolerance to be eps/2s 
        if (node->node_id==1) { // root node calculation
            node->scenario_LBDs.push_back(scenario_LBD);
        } else { // regular node
            if (scenario_LBD<node->scenario_LBDs[static_cast<int>(scenario_name)]){ // scenario LBD should be improved otherwise there is a numercial issue
                scenario_LBD=node->scenario_LBDs[static_cast<int>(scenario_name)];
            }else{
                node->scenario_LBDs[static_cast<int>(scenario_name)] = scenario_LBD;
            }
        }
        
        std::cout<<"Scenario "<<static_cast<int>(scenario_name)<<" LBD: "<<scenario_LBD<<std::endl;
        if (scenario_LBD == INFINITY) {
            // if any scenario is infeasible, then the node is infeasible
            totalLBD = INFINITY;
            break;
        }else{
            totalLBD += scenario_LBD;
        }
    }


    node->LBD = totalLBD;
    return totalLBD;
}
void outsideAlgo::printFirstStageIX(BBNode* node){
    std::cout<<"First stage IX for node "<<node->node_id<<": ";
    for (const auto& interval : node->first_stage_IX) {
        std::cout<<"["<<interval.l()<<","<<interval.u()<<"] "<<std::endl;
    }
    std::cout<<std::endl;
}
double outsideAlgo::solve(double tolerance) {

    auto start = std::chrono::high_resolution_clock::now();
    int initial_lbd_calculation_count=insideAlgo::lbd_calculation_count;
    double initial_lbd_calculation_time=insideAlgo::lbd_calculation_time;
    std::cout<<"Calculating LBD for root node..."<<std::endl;
    this->worstLBD=this->calculateLBD(&(this->activeNodes[0]), tolerance);
    std::cout<<"Finished calculating LBD for root node."<<std::endl;
    this->LBD_calculation_records.push_back(insideAlgo::lbd_calculation_count-initial_lbd_calculation_count); // record number of LBD calculation for root node
    std::vector<std::pair<double, double>> initial_first_stage_IX_record;  // record first stage variable bound
    for (const auto& interval : this->activeNodes[0].first_stage_IX) {
        initial_first_stage_IX_record.push_back({interval.l(), interval.u()});
    }
    this->first_stage_IX_record.push_back(initial_first_stage_IX_record);
    this->LBD_values_records.push_back(this->activeNodes[0].LBD); // record LBD value for root node
    this->LBD_calculation_time_records.push_back(insideAlgo::lbd_calculation_time-initial_lbd_calculation_time); // record LBD calculation time for root node
    
    
    int before_strong_branching_lbd_calculation_count=insideAlgo::lbd_calculation_count;
    double before_strong_branching_lbd_calculation_time=insideAlgo::lbd_calculation_time;

    if (this->activeNodes[0].branchheuristic.strategy==BranchingStrategy::pseudo){
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Started Outside Strong Branching"<<std::endl;
        std::cout<<"========================================"<<std::endl;
        this->strongbranching(&(this->activeNodes[0]), tolerance);
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Finished Outside Strong Branching"<<std::endl;
        std::cout<<"========================================"<<std::endl;
    }
    insideAlgo::lbd_calculation_time=before_strong_branching_lbd_calculation_time; // add the LBD calculation time before strong branching to the total LBD calculation time
    insideAlgo::lbd_calculation_count=before_strong_branching_lbd_calculation_count;
    double gap = (this->bestUBD - this->worstLBD); // abs gap calculation
    this->iterations = 0;

    while (gap >= tolerance) {
        if (this->activeNodes.empty()) {
            break; // No more nodes to process
        }
        //get worst node idx
        int idx=this->getWorstNodeIdx();

        //branch node at idx
        int branch_var_idx= this->branchNodeAtIdx( idx,tolerance);


        //update UBD of nodeList and fathom by inf or value dominance
        this->fathomNodes(this->bestUBD);
        this->worstLBD=this->getWorstLBD();

        // update gap
        gap = (this->bestUBD - this->worstLBD); // absolute gap
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout<<"----------------------------------------"<<std::endl;
        std::cout<<"Iteration "<<this->iterations<<std::endl;
        std::cout<<"----------------------------------------"<<std::endl;
        std::cout<<"Current UBD: "<<this->bestUBD<<", LBD: "<<this->worstLBD<<", Gap: "<<gap<<" Total Wall Time: " << elapsed.count() << " seconds" << std::endl;
        std::cout<<"Total LBD time: "<<insideAlgo::lbd_calculation_time<<std::endl;
        std::cout<<"Total LBD calculations: "<<insideAlgo::lbd_calculation_count<<std::endl;
        this->iterations++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout<<"========================================"<<std::endl;
    std::cout<<"Algorithm terminated after "<<this->iterations<<" iterations."<<std::endl;
    std::cout<<"Total Wall Time: " << elapsed.count() << " seconds" << std::endl;
    std::cout<<"Best Solution: " << this->bestUBD << std::endl;

    return this->bestUBD;
}

insideAlgo::insideAlgo(STModel* model,ScenarioNames scenario_name,double provided_UBD,bool solvefullModel,UBDSolver solver) : Algo<xBBNode>(model) {
    this->scenario_name=scenario_name;
    this->provided_UBD=provided_UBD;
    this->solvefullModel=solvefullModel;
    this->ubd_solver = solver;
    if (this->solvefullModel){
        this->model->convertToCentralizedModel();
    }
    this->activeNodes.push_back(xBBNode(this->model->first_stage_IX,this->model->second_stage_IX,
        this->model->branching_strategy,this->scenario_name));
    this->activeNodes[0].node_id=0;


}
void insideAlgo::strongbranching(xBBNode* node,double tolerance){
    xBBNode node_copy=*node;
    bool node_is_valid=this->validitycheck(&node_copy);
    node->strong_branching_storage.clear();
    node->strong_branching_storage.resize(node->first_stage_IX.size()+node->second_stage_IX.size());
    int first_stage_size=node->first_stage_IX.size();
    int second_stage_size=node->second_stage_IX.size();
    double original_LBD=node->LBD;
    double original_UBD=node->UBD;
    int iterator=0;
    std::vector<std::pair<double,double>> temp_weights;
    // continue SB until no variable has infinity weight
    while (iterator < first_stage_size+second_stage_size) {

        if (iterator<first_stage_size) { // first stage 
            double range_current=(node->first_stage_IX[iterator].u() - node->first_stage_IX[iterator].l());
            double range_initial=(node->branchheuristic.initial_first_stage_IX[iterator].u()-node->branchheuristic.initial_first_stage_IX[iterator].l());
            if (range_initial<1e-5 || range_current/range_initial < 1e-5){
                // if the initial range is too small, then skip strong branching on that variable
                temp_weights.push_back(std::pair(0,0));
                iterator++;
                continue;
            }


            xBBNode child1 = *node;
            xBBNode child2 = *node;
            double branch_point = (node->first_stage_IX[iterator].l() + node->first_stage_IX[iterator].u()) / 2.0;
            double range=branch_point - node->first_stage_IX[iterator].l();
            child1.first_stage_IX[iterator] = mc::Interval(child1.first_stage_IX[iterator].l(), branch_point);
            child2.first_stage_IX[iterator] = mc::Interval(branch_point, child2.first_stage_IX[iterator].u());
            
            double left_LBD=this->calculateLBD(&child1, tolerance);
            double right_LBD=this->calculateLBD(&child2, tolerance);

            if (left_LBD == INFINITY){
                if (right_LBD == INFINITY){
                    node->LBD=INFINITY; // if both child are infeasible, then the node is infeasible
                    std::cout<<"Variable index "<<iterator<<" strong branching detected infeasible node, skipping branching."<<std::endl;
                    return;
                }
                // reduce range
                node->first_stage_IX[iterator] = mc::Interval(branch_point,node->first_stage_IX[iterator].u());
                continue;
            }else if (right_LBD == INFINITY){
                // reduce range
                node->first_stage_IX[iterator] = mc::Interval(node->first_stage_IX[iterator].l(),branch_point);
                continue;
            }else{
                // both child are feasible
                if (left_LBD < original_LBD ){
                    left_LBD=original_LBD;
                }
                if (right_LBD < original_LBD){
                    right_LBD=original_LBD;
                }
                temp_weights.push_back(std::pair(left_LBD-original_LBD, right_LBD-original_LBD));
            }

        }else{
            double range_current=(node->second_stage_IX[iterator-first_stage_size].u() - node->second_stage_IX[iterator-first_stage_size].l());
            double range_initial=(node->branchheuristic.initial_second_stage_IX[iterator-first_stage_size].u()-node->branchheuristic.initial_second_stage_IX[iterator-first_stage_size].l());
            if (range_initial<1e-5 || range_current/range_initial < 1e-5){
                // if the initial range is too small, then skip strong branching on that variable
                temp_weights.push_back(std::pair(0,0));
                iterator++;
                continue;
            }


            xBBNode child3 = *node;
            xBBNode child4 = *node;
            double branch_point = (node->second_stage_IX[iterator-first_stage_size].l() + node->second_stage_IX[iterator-first_stage_size].u()) / 2.0;
            double range=branch_point - node->second_stage_IX[iterator-first_stage_size].l();
            child3.second_stage_IX[iterator-first_stage_size] = mc::Interval(child3.second_stage_IX[iterator-first_stage_size].l(), branch_point);
            child4.second_stage_IX[iterator-first_stage_size] = mc::Interval(branch_point, child4.second_stage_IX[iterator-first_stage_size].u());
            
            double left_LBD=this->calculateLBD(&child3, tolerance); 
            double right_LBD=this->calculateLBD(&child4, tolerance);

            if (left_LBD == INFINITY){
                if (right_LBD == INFINITY){
                    node->LBD=INFINITY; // if both child are infeasible, then the node is infeasible
                    std::cout<<"Variable index "<<iterator<<" strong branching detected infeasible node, skipping branching."<<std::endl;
                    return;
                }
                // reduce range
                node->second_stage_IX[iterator-first_stage_size] = mc::Interval(branch_point,node->second_stage_IX[iterator-first_stage_size].u());
                continue;
            }else if (right_LBD == INFINITY){

                // reduce range
                node->second_stage_IX[iterator-first_stage_size] = mc::Interval(node->second_stage_IX[iterator-first_stage_size].l(),branch_point);
                continue;
            }else{
                // both child are feasible
                if (left_LBD < original_LBD ){
                    left_LBD=original_LBD;
                }
                if (right_LBD < original_LBD){
                    right_LBD=original_LBD;
                }
                temp_weights.push_back(std::pair(left_LBD-original_LBD, right_LBD-original_LBD));       
            }


        }
        iterator++;
    }

    
    // there should be no infinity in any varibale weights update weights with lastest result
    for (int i=0;i<temp_weights.size();i++){
        //std::cout<<"Variable index "<<i<<"Left: "<<temp_weights[i].first+original_LBD<<", Right "<<temp_weights[i].second+original_LBD<<std::endl;
        if (i<first_stage_size){
            node->branchheuristic.updateWeights(i,temp_weights[i].first,temp_weights[i].second,
                node->first_stage_IX[i].u()-node->first_stage_IX[i].l(),USE_inside_weights::YES);
            node->strong_branching_storage[i].first = temp_weights[i].first+original_LBD;
            node->strong_branching_storage[i].second = temp_weights[i].second+original_LBD;
        }else{
            node->branchheuristic.updateWeights(i,temp_weights[i].first,temp_weights[i].second,
                node->second_stage_IX[i-first_stage_size].u()-node->second_stage_IX[i-first_stage_size].l(),USE_inside_weights::YES);
            node->strong_branching_storage[i].first = temp_weights[i].first+original_LBD;
            node->strong_branching_storage[i].second = temp_weights[i].second+original_LBD;
        }
    }
}
int insideAlgo::branchNodeAtIdx(int new_idx,double tolerance) {
    double original_LBD= this->activeNodes[new_idx].LBD;
    if (original_LBD==INFINITY){
        std::cout<<"Infeasible node detected, skipping strong branching."<<std::endl;
        return 0;
    }

    double range;
    //this->weirdstrongbranching(&(this->activeNodes[new_idx]), tolerance);
    this->strongbranching(&(this->activeNodes[new_idx]), tolerance);
    if (this->activeNodes[new_idx].LBD==INFINITY){
        std::cout<<"Infeasible node detected after strong branching, skipping branching."<<std::endl;
        return 0;
    }
    int next_idx=this->activeNodes.back().node_id+1; 
    xBBNode child1 = this->activeNodes[new_idx]; // Copy current node
    child1.node_id = next_idx; // Assign unique ID to child1
    next_idx++;
    xBBNode child2 = this->activeNodes[new_idx]; // Copy current node
    child2.node_id = next_idx; // Assign unique ID to child2
    int branch_idx=INFINITY;

    branch_idx = this->activeNodes[new_idx].branchheuristic.getBranchingVarIndex(this->activeNodes[new_idx].first_stage_IX,this->activeNodes[new_idx].second_stage_IX);
    
    if(branch_idx<this->activeNodes[new_idx].first_stage_IX.size()){

        // first stage branching
        double branch_point = this->activeNodes[new_idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[new_idx].first_stage_IX,this->activeNodes[new_idx].second_stage_IX);
        range=branch_point-this->activeNodes[new_idx].first_stage_IX[branch_idx].l();
        child1.first_stage_IX[branch_idx] = mc::Interval(this->activeNodes[new_idx].first_stage_IX[branch_idx].l(), branch_point);
        child2.first_stage_IX[branch_idx] = mc::Interval(branch_point, this->activeNodes[new_idx].first_stage_IX[branch_idx].u());
      
    }else if(branch_idx>=this->activeNodes[new_idx].first_stage_IX.size()){
        
        // second stage branching

        double branch_point = this->activeNodes[new_idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[new_idx].first_stage_IX,this->activeNodes[new_idx].second_stage_IX);
        range=branch_point-this->activeNodes[new_idx].second_stage_IX[branch_idx-this->activeNodes[new_idx].first_stage_IX.size()].l();
        child1.second_stage_IX[branch_idx-this->activeNodes[new_idx].first_stage_IX.size()] = mc::Interval(this->activeNodes[new_idx].second_stage_IX[branch_idx-this->activeNodes[new_idx].first_stage_IX.size()].l(), branch_point);
        child2.second_stage_IX[branch_idx-this->activeNodes[new_idx].first_stage_IX.size()] = mc::Interval(branch_point, this->activeNodes[new_idx].second_stage_IX[branch_idx-this->activeNodes[new_idx].first_stage_IX.size()].u());
    
    }
    double before_LBD_time=insideAlgo::lbd_calculation_time;


    this->calculateLBD(&child1, tolerance);


    this->LBD_calculation_time_records.push_back(insideAlgo::lbd_calculation_time-before_LBD_time); // record LBD calculation time for child1
    double before_LBD_time2=insideAlgo::lbd_calculation_time;

    this->calculateLBD(&child2, tolerance);
    this->LBD_calculation_time_records.push_back(insideAlgo::lbd_calculation_time-before_LBD_time2); // record LBD calculation time for child2
    if (child1.UBD==INFINITY){
        child1.LBD=INFINITY; // if child UBD is infinity, then set child UBD to best UBD to avoid numerical issue
    }
    if (child2.UBD==INFINITY){
        child2.LBD=INFINITY; // if child UBD is infinity, then set child UBD to best UBD to avoid numerical issue
    }

    if (child1.LBD<original_LBD){
        child1.LBD=original_LBD; // if child LBD is less than parent LBD, then set child LBD to parent LBD to avoid numerical issue

    }
    if (child2.LBD<original_LBD){
        child2.LBD=original_LBD; // if child LBD is less than parent LBD, then set child LBD to parent LBD to avoid numerical issue
    }

    if (child1.LBD != INFINITY){
        //this->calculateUBD(&child1, tolerance); // just use global gurobi if ipopt just commetn in
    }else{
        child1.UBD=INFINITY;
    }
    if (child2.LBD != INFINITY){
        //this->calculateUBD(&child2, tolerance); // just use global gurobi
    }else{
        child2.UBD=INFINITY;
    }

    if (child1.LBD == INFINITY){
        // left child is infeasible, right child infeasible
        if (child2.LBD == INFINITY){
            // no need to update heuristic if both child are infeasible
            this->activeNodes.erase(this->activeNodes.begin() + new_idx);
            return branch_idx;
        }else{
            // left child is infeasible, right child improve

            if (this->bestUBDforInfinity && this->bestUBD!=INFINITY){ // if bestUBDforInfinity is true and bestUBD is not infinity, then we can update heuristic with bestUBD, otherwise we cannot update heuristic with bestUBD because it is infinity which will cause numerical issue

                child1.branchheuristic.updateWeights(branch_idx,
                    this->bestUBD-original_LBD, (child2.LBD - original_LBD),range,USE_inside_weights::YES); // set to bestUBD of this subproblem to avoid infitinity pseducost update
                child2.branchheuristic.updateWeights(branch_idx,
                    this->bestUBD-original_LBD, (child2.LBD - original_LBD),range,USE_inside_weights::YES);
            }else{
                child1.branchheuristic.updateWeights(branch_idx,
                    0, (child2.LBD - original_LBD),range,USE_inside_weights::YES);
                child2.branchheuristic.updateWeights(branch_idx,
                    0, (child2.LBD - original_LBD),range,USE_inside_weights::YES);
            }
        }
        
    }else if (child2.LBD == INFINITY){
        // right child is infeasible, left child improve
        if (this->bestUBDforInfinity && this->bestUBD!=INFINITY){
            child1.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), this->bestUBD-original_LBD,range,  USE_inside_weights::YES); // set to bestUBD of this subproblem to avoid infitinity pseducost update
            child2.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), this->bestUBD-original_LBD,range,USE_inside_weights::YES);
        }else{

            child1.branchheuristic.updateWeights(branch_idx,
                (child1.LBD - original_LBD), 0,range,USE_inside_weights::YES); 
            child2.branchheuristic.updateWeights(branch_idx,
                (child1.LBD - original_LBD), 0,range,USE_inside_weights::YES);
        }
    }else{
        // both child are feasible
        child1.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), (child2.LBD - original_LBD),range,USE_inside_weights::YES);
        child2.branchheuristic.updateWeights(branch_idx,
            (child1.LBD - original_LBD), (child2.LBD - original_LBD),range,USE_inside_weights::YES);
    }


    this->LBD_values_records.push_back(child1.LBD); // record LBD value for child1
    this->LBD_values_records.push_back(child2.LBD); // record LBD value
    this->activeNodes.erase(this->activeNodes.begin() + new_idx);
    this->activeNodes.push_back(child1);
    this->activeNodes.push_back(child2);
    return branch_idx;
}
double insideAlgo::calculateLBD(xBBNode* node,double tolerance,bool verbose) {
    insideAlgo::lbd_calculation_count++;
    this->model->scenario_name = node->scenario_name;
    this->model->first_stage_IX = node->first_stage_IX;
    this->model->second_stage_IX = node->second_stage_IX;
    this->model->clearDAG(); // remove the previous DAG to avoid interference
    if (!this->solvefullModel){
        this->model->buildDAG();
    }else{
        this->model->buildFullModelDAG();
    }
    try{
        ILOSTLBEGIN
        IloEnv env;
        if (!verbose){
            env.setOut(env.getNullStream());
            env.setWarning(env.getNullStream());
        }
        IloModel cplexmodel(env);
        IloRangeArray c(env);
        IloObjective obj (env);
        IloNumVarArray x(env);
        this->model->generateLP(&env,&cplexmodel,&c,&obj,&x);
        IloCplex cplex(cplexmodel);
        cplex.setParam(IloCplex::Param::ClockType, 2);
        cplex.setParam(IloCplex::Param::Simplex::Tolerances::Optimality, 1e-4);
        cplex.setParam(IloCplex::Param::Simplex::Tolerances::Feasibility, 1e-4);
        cplex.setParam(IloCplex::Param::Read::Scale, 1);
        //cplex.setParam(IloCplex::Param::RootAlgorithm, IloCplex::Barrier);
        cplex.setParam(IloCplex::AggInd, false);
        cplex.setParam(IloCplex::Param::SolutionType, 2);

        //cplex.exportModel("/Users/jyang872/Desktop/CrappySolver/test.lp"); // please delete
        auto start = std::chrono::high_resolution_clock::now();
        cplex.solve();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        insideAlgo::lbd_calculation_time += elapsed.count();
        if (cplex.getStatus() == IloAlgorithm::Optimal) {
            node->LBD= cplex.getObjValue();
            IloNumArray vals(env);
            cplex.getValues(vals, x);

            std::vector<double> solution(vals.getSize());
            for (IloInt i = 0; i < node->second_stage_IX.size()+node->first_stage_IX.size(); ++i) {
                //std::cout<<"Variable "<<i<<": "<<vals[i]<<std::endl; // please delete
                solution[i] = vals[i];
            }
            vals.end(); 
            node->branchheuristic.LBD_opt_pt=solution; // store the optimal solution for LBD calculation
            
        }else if (cplex.getStatus() == IloAlgorithm::Infeasible) {
            node->LBD=INFINITY; // assign big number for infeasibility
                        // ── Conflict Refiner ──────────────────────────────────────────────
            // cplex.setOut(std::cout);
            // IloConstraintArray conflicts(env);
            // IloNumArray priorities(env);
            
            // for (IloInt i = 0; i < c.getSize(); ++i) { conflicts.add(c[i]); priorities.add(1.0); }

            // if (cplex.refineConflict(conflicts, priorities)) {
            //     std::cerr << "===== CONFLICT REPORT =====\n";
 
            //     for (IloInt i = 0; i < c.getSize(); ++i) {
            //         auto st = cplex.getConflict(c[i]);
            //         if (st == IloCplex::ConflictMember || st == IloCplex::ConflictPossibleMember)
            //             std::cerr << "  CON [" << i+1 << "] " << (c[i].getName() ? c[i].getName() : "?")
            //                     << " lb=" << c[i].getLB() << " ub=" << c[i].getUB() << "\n";
            //     }
            //     std::cerr << "===========================\n";
            // } else {
            //     std::cerr << "[ConflictRefiner] Could not identify conflict (likely numerical).\n";
            // }
            // ─────────────────────────────────────────────────────────────────
        } else if (cplex.getStatus() == IloAlgorithm::InfeasibleOrUnbounded) {
            node->LBD = INFINITY;
        }
        env.end();
    } catch (IloException& e) {
        std::cerr << "CPLEX exception: " << e << "\n";
    }

    return node->LBD;


    // GUROBI LBD calculation
    // insideAlgo::lbd_calculation_count++;
    // this->model->scenario_name = node->scenario_name;
    // this->model->first_stage_IX = node->first_stage_IX;
    // this->model->second_stage_IX = node->second_stage_IX;
    // this->model->clearDAG(); // remove the previous DAG to avoid interference
    // if (!this->solvefullModel) {
    //     this->model->buildDAG();
    // } else {
    //     this->model->buildFullModelDAG();
    // }
    // try {
    //     GRBEnv env(true);

    //     if (!verbose) {
    //         env.set(GRB_IntParam_OutputFlag, 0);
    //     }
    //     env.set(GRB_IntParam_OutputFlag, 0);
    //     env.set(GRB_IntParam_LogToConsole, 0); // please delete
    //     env.start();

    //     GRBModel grb_model(env);
    //     std::vector<GRBVar> x;
    //     this->model->generateLP(&env, &grb_model, &x);

    //     // Parameter equivalents to the CPLEX settings above
    //     grb_model.set(GRB_IntParam_Method, -1);           // let Gurobi pick root algorithm (analogous to leaving RootAlgorithm default/commented)
    //     grb_model.set(GRB_DoubleParam_OptimalityTol, 1e-4);
    //     grb_model.set(GRB_DoubleParam_FeasibilityTol, 1e-4);
    //     grb_model.set(GRB_IntParam_ScaleFlag, 3);          // ~ IloCplex::Param::Read::Scale
    //     grb_model.set(GRB_IntParam_Aggregate, 0);          // ~ IloCplex::AggInd = false
    //     grb_model.set(GRB_IntParam_NumericFocus, 3);           // ~ IloCplex::AggInd = false (no presolve)
 

    //     grb_model.write("/Users/jyang872/Desktop/CrappySolver/test.lp"); // please delete

    //     auto start = std::chrono::high_resolution_clock::now();
    //     grb_model.optimize();
    //     auto end = std::chrono::high_resolution_clock::now();
    //     std::chrono::duration<double> elapsed = end - start;
    //     insideAlgo::lbd_calculation_time += elapsed.count();

    //     int status = grb_model.get(GRB_IntAttr_Status);
    //     if (status == GRB_OPTIMAL) {
    //         node->LBD = grb_model.get(GRB_DoubleAttr_ObjVal);

    //         std::vector<double> solution(x.size());
    //         for (size_t i = 0; i < node->second_stage_IX.size() + node->first_stage_IX.size(); ++i) {
    //             //std::cout << "Variable " << i << ": " << x[i].get(GRB_DoubleAttr_X) << std::endl; // please delete
    //             solution[i] = x[i].get(GRB_DoubleAttr_X);
    //         }
    //         node->branchheuristic.LBD_opt_pt = solution; // store the optimal solution for LBD calculation

    //     } else if (status == GRB_INFEASIBLE) {
    //         node->LBD = INFINITY; // assign big number for infeasibility
    //         // ── Conflict Refiner (IIS) ──────────────────────────────────────────
    //         // grb_model.computeIIS();
    //         // std::cerr << "===== CONFLICT REPORT =====\n";
    //         // for (auto& constr : grb_model.getConstrs()) {
    //         //     if (constr.get(GRB_IntAttr_IISConstr)) {
    //         //         std::cerr << "  CON " << constr.get(GRB_StringAttr_ConstrName) << "\n";
    //         //     }
    //         // }
    //         // std::cerr << "===========================\n";
    //         // ─────────────────────────────────────────────────────────────────
    //     } else if (status == GRB_INF_OR_UNBD) {
    //         node->LBD = INFINITY;
    //     }

    // } catch (GRBException& e) {
    //     std::cerr << "Gurobi exception: " << e.getErrorCode() << ": " << e.getMessage() << "\n";
    // }

    // return node->LBD;


}
double insideAlgo::calculateUBD(xBBNode* node,double tolerance) {

    if (this->solvefullModel){
        // if solvefullModel is true, we solve the full MINLP to get the UBD, otherwise we just use the provided UBD for this node
        // used for nodecomposition approach only
        node->UBD = this->provided_UBD;
        return this->provided_UBD;
    }

    this->model->scenario_name = node->scenario_name;
    this->model->first_stage_IX = node->first_stage_IX;
    this->model->second_stage_IX = node->second_stage_IX;
    this->model->clearDAG(); // remove the previous DAG to avoid interference
    if (!this->solvefullModel){
        this->model->buildDAG();
    }else{
        this->model->buildFullModelDAG();
    }

    if (this->ubd_solver == UBDSolver::IPOPT){
        Ipopt::SmartPtr<Ipopt::TNLP> mynlp = this->model->clone();
        STModel* sm = dynamic_cast<STModel*>(Ipopt::GetRawPtr(mynlp));

        Ipopt::SmartPtr<Ipopt::IpoptApplication> app = IpoptApplicationFactory();
        app->Options()->SetNumericValue("tol", 1e-4);           // Optimality tolerance
        app->Options()->SetNumericValue("constr_viol_tol", 1e-4);  // Constraint feasibility
        app->Options()->SetNumericValue("compl_inf_tol", 1e-4);    // Complementarity tolerance
        app->Options()->SetIntegerValue("print_level", 0);
        app->Options()->SetIntegerValue("max_iter", 10000); 
        app->Options()->SetStringValue("sb", "yes");
        app->Options()->SetStringValue("hessian_approximation", "limited-memory");
        app->Options()->SetStringValue("mu_strategy", "adaptive");


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

        if( status == Ipopt::Solve_Succeeded )
        {
            node->UBD = sm->solution.f[0];

            // <--------------- print solution
            int i=0;
            node->UBD_solution.clear();
            for (auto v: sm->solution.x) {
                node->UBD_solution.push_back(v);
                //std::cout <<"mc::Interval ("<<v<<","<<v<<"), // x["<<i<<"]"<<std::endl;
                i++;
            }


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
        env.set(GRB_IntParam_LogToConsole, 0); // please delete
        env.start();
        try {
            GRBModel grbmodel = GRBModel(env);
            this->model->generateMINLP(&grbmodel);
            grbmodel.set(GRB_IntParam_NonConvex, 2);
            grbmodel.set(GRB_DoubleParam_OptimalityTol, 1e-4);
            grbmodel.set(GRB_DoubleParam_FeasibilityTol, 1e-4); // set feasibility tolerance to be 1e-4 for better numerical performance, can be tuned
            grbmodel.set(GRB_DoubleParam_MIPGap, 1e-10);  // temporarily set to tight gap for testing
            grbmodel.set(GRB_DoubleParam_TimeLimit, 60.0);

            grbmodel.optimize();

            int status = grbmodel.get(GRB_IntAttr_Status);

            if (status == GRB_OPTIMAL || status == GRB_TIME_LIMIT || status == GRB_SUBOPTIMAL) {
                double objval = grbmodel.get(GRB_DoubleAttr_ObjVal);
                node->UBD = objval;
                // std::cout << "Optimized solution values: "<<objval<<std::endl;
                for (int i = 0; i <node->first_stage_IX.size()+node->second_stage_IX.size(); ++i) {
                    std::string auxName = "x" + std::to_string(i);
        
                    GRBVar auxVar = grbmodel.getVarByName(auxName);
                    double value = auxVar.get(GRB_DoubleAttr_X);
                    node->UBD_solution.push_back(value);
                    //std::cout <<"mc::Interval ("<<value<<","<<value<<"), // x["<<i<<"]"<<std::endl;

                }

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
void insideAlgo::printFirstStageIX(xBBNode* node){
    //leave empty for inside algo since we don't have first stage IX record for inside algo, we can add this in the future if needed
    for (const auto& interval : node->first_stage_IX) {
        std::cout<<"mc::Interval ("<<interval.l()<<","<<interval.u()<<"), "<<std::endl;
    }
    std::cout<<std::endl;
}
void insideAlgo::printSecondStageIX(xBBNode* node){
    int i = 0;
    for (const auto& interval : node->second_stage_IX) {
        std::cout<<"mc::Interval ("<<interval.l()<<","<<interval.u()<<"), // x["<<i<<"]"<<std::endl;
        i++;
    }
    std::cout<<std::endl;
}

void insideAlgo::weirdstrongbranching(xBBNode* node,double tolerance){
    node->strong_branching_storage.clear();
    node->strong_branching_storage.resize(node->first_stage_IX.size()+node->second_stage_IX.size());
    int first_stage_size=node->first_stage_IX.size();
    int second_stage_size=node->second_stage_IX.size();
    double original_LBD=node->LBD;
    double original_UBD=node->UBD;
    int iterator=0;
    std::vector<std::pair<double,double>> temp_weights;
    // continue SB until no variable has infinity weight
    while (iterator < first_stage_size+second_stage_size) {
        if (iterator<first_stage_size) {
            if (node->first_stage_IX[iterator].u() - node->first_stage_IX[iterator].l() < 1e-5){
                // if that variable is fixed then skip strong branching on that variable
                temp_weights.push_back(std::make_pair(0, 0));
                iterator++;
                continue;
            }

            xBBNode child1 = *node;
            double branch_point = (node->first_stage_IX[iterator].l() + node->first_stage_IX[iterator].u()) / 2.0;
            double range=(node->first_stage_IX[iterator].u() - node->first_stage_IX[iterator].l())*0.1;
            child1.first_stage_IX[iterator] = mc::Interval(branch_point-0.5*range, branch_point+0.5*range);
            
            double left_LBD = this->calculateLBD(&child1, tolerance);
            
            if (left_LBD == INFINITY){
                temp_weights.push_back(std::make_pair(this->bestUBD-original_LBD, this->bestUBD-original_LBD));
                iterator++;
                continue; // if child is infeasible, then skip this variable
            }

            temp_weights.push_back(std::make_pair(left_LBD-original_LBD, left_LBD-original_LBD));

            
        }else{
            // second stage variable strong branching
            if (node->second_stage_IX[iterator-first_stage_size].u() - node->second_stage_IX[iterator-first_stage_size].l() < 1e-5){
                // if that variable is fixed then skip strong branching on that variable
                temp_weights.push_back(std::make_pair(0, 0));                
                iterator++;
                continue;
            }
            xBBNode child3 = *node;
            double branch_point = (node->second_stage_IX[iterator-first_stage_size].l() + node->second_stage_IX[iterator-first_stage_size].u()) / 2.0;
            double range=(node->second_stage_IX[iterator-first_stage_size].u()- node->second_stage_IX[iterator-first_stage_size].l())*0.1;
            child3.second_stage_IX[iterator-first_stage_size] = mc::Interval(branch_point-0.5*range, branch_point+0.5*range);
            
            double left_LBD=this->calculateLBD(&child3, tolerance); 


            if (left_LBD == INFINITY){
                temp_weights.push_back(std::make_pair(this->bestUBD-original_LBD, this->bestUBD-original_LBD));
                iterator++;
                continue; // if child is infeasible, then skip this variable
            }

            temp_weights.push_back(std::make_pair(left_LBD-original_LBD, left_LBD-original_LBD));

            
        }

        iterator++;
    }
    for (int i=0;i<temp_weights.size();i++){
        //std::cout<<"Variable index "<<i<<"Left: "<<temp_weights[i].first+original_LBD<<", Right "<<temp_weights[i].second+original_LBD<<std::endl;
        if (i<first_stage_size){
            node->branchheuristic.updateWeights(i,temp_weights[i].first,temp_weights[i].second,
                node->first_stage_IX[i].u()-node->first_stage_IX[i].l(),USE_inside_weights::YES);

        }else{
            node->branchheuristic.updateWeights(i,temp_weights[i].first,temp_weights[i].second,
                node->second_stage_IX[i-first_stage_size].u()-node->second_stage_IX[i-first_stage_size].l(),USE_inside_weights::YES);

        }
    }
}



double insideAlgo::solve(double tolerance) {

    this->bestUBD = this->calculateUBD(&(this->activeNodes[0]), tolerance);
    if (this->bestUBD==INFINITY){
        std::cout<<"Scenario "<<static_cast<int>(this->scenario_name)<<" is infeasible at root node."<<std::endl;
        return INFINITY;
    }
    double before_root_lbd_calculation_time=insideAlgo::lbd_calculation_time;

    this->worstLBD = this->calculateLBD(&(this->activeNodes[0]), tolerance);
    this->LBD_values_records.push_back(this->activeNodes[0].LBD); // record LBD value for root node
    this->LBD_calculation_time_records.push_back(insideAlgo::lbd_calculation_time - before_root_lbd_calculation_time); // record LBD calculation time for root node

    double gap = (this->bestUBD - this->worstLBD); // absolute gap calculation for inner layer
    if (gap < tolerance){
        std::cout<<"Scenario "<<static_cast<int>(this->scenario_name)<<" terminated at root node with gap: "<<gap<<std::endl;
        return this->worstLBD;
    }
    if (this->worstLBD==INFINITY || this->bestUBD==INFINITY){ // if root node is infeasible or the provided UBD is infeasible, then we can terminate immediately
        std::cout<<"Scenario "<<static_cast<int>(this->scenario_name)<<" is infeasible at root node."<<std::endl;
        return INFINITY;
    }

    // strong branching
    int before_strong_branching_lbd_calculation_count=insideAlgo::lbd_calculation_count;
    double before_strong_branching_lbd_calculation_time=insideAlgo::lbd_calculation_time;
    if (this->activeNodes[0].branchheuristic.strategy==BranchingStrategy::pseudo){
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Started Inside Strong Branching"<<std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        this->strongbranching(&(this->activeNodes[0]), tolerance);
        //this->weirdstrongbranching(&(this->activeNodes[0]), tolerance);  //PLEASE DELETE
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout<<"Finished Inside Strong Branching"<<std::endl;
        std::cout<<"========================================"<<std::endl;
    }else{
        std::cout<<"========================================"<<std::endl;}

    if (this->activeNodes[0].LBD == INFINITY){ // in rare case when strong branching detects infeasibility
        std::cout<<"Scenario "<<static_cast<int>(this->scenario_name)<<" is infeasible after strong branching at root node."<<std::endl;
        return INFINITY;
    }

    insideAlgo::lbd_calculation_count=before_strong_branching_lbd_calculation_count; //offset the LBD calculation count to exclude strong branching calculations for fair comparison
    insideAlgo::lbd_calculation_time=before_strong_branching_lbd_calculation_time; // same idea


    // OFFICIAL SOLVING LOOP
    this->iterations = 0;

    while (gap >= tolerance) {

        if (this->activeNodes.empty()) {
            break;
        }
        int idx = this->getWorstNodeIdx();
        int branch_var_idx= this->branchNodeAtIdx( idx,tolerance);
        this->worstLBD = this->getWorstLBD();
        this->bestUBD = this->getBestUBD();
        if (this->worstLBD>this->bestUBD){
            return this->bestUBD;
            //throw std::runtime_error("Warning: Worst LBD is greater than best UBD, this should not happen, there might be a bug in the code");
        }

        this->fathomNodes(this->bestUBD);
        this->worstLBD = this->getWorstLBD();
        this->bestUBD = this->getBestUBD();
        this->LBD_values_records.push_back(this->worstLBD); // record LBD value for worst node
        if (this->worstLBD==INFINITY){
            return INFINITY;
        }



        gap = (this->bestUBD - this->worstLBD); // absolute gap calculation for inner layer 

        //std::cout<<"Inside Iteration "<<this->iterations<<": Current UBD: "<<this->bestUBD<<", LBD: "<<this->worstLBD<<", AbsGap: "<<gap<<"Tol: "<<tolerance<<std::endl;
        //std::cout<<"Total LBD calculations: "<<insideAlgo::lbd_calculation_count<<std::endl;
        this->iterations++;
    }

    std::cout<<"Scenario "<<static_cast<int>(this->scenario_name)<<" terminated after "<<iterations<<" iterations."<<std::endl;
    return this->worstLBD;

}
bool insideAlgo::OBBT(xBBNode* node,double tolerance){

    int var_idx=0;
    while (var_idx < node->first_stage_IX.size()+node->second_stage_IX.size()){


        if (var_idx<node->first_stage_IX.size()){
            double range_current=node->first_stage_IX[var_idx].u()-node->first_stage_IX[var_idx].l();
            double range_original=node->branchheuristic.initial_first_stage_IX[var_idx].u()-node->branchheuristic.initial_first_stage_IX[var_idx].l();
            if (range_original<1e-6 || range_current/range_original < 1e-4){
                // if that variable is fixed then skip OBBT on that variable
                var_idx++;
                continue;
            }
        }else{
            double range_current=node->second_stage_IX[var_idx-node->first_stage_IX.size()].u()-node->second_stage_IX[var_idx-node->first_stage_IX.size()].l();
            double range_original=node->branchheuristic.initial_second_stage_IX[var_idx-node->first_stage_IX.size()].u()-node->branchheuristic.initial_second_stage_IX[var_idx-node->first_stage_IX.size()].l();
            if (range_original<1e-6 || range_current/range_original < 1e-4){
                // if that variable is fixed then skip OBBT on that variable
                var_idx++;
                continue;
            }
        }

        if (this->getOBBTbounds_upper(node, var_idx)&&this->getOBBTbounds_lower(node, var_idx)){
            var_idx++;
        }
        else{
            node->LBD = INFINITY; // if the lower bound is greater than the upper bound, then the node is infeasible
            return false; // if the node is infeasible, then we can stop OBBT
        }

    }


    return true;

}
// bool insideAlgo::getOBBTbounds_lower(xBBNode* node, int var_idx){
//     xBBNode node_copy = *node; // make a copy of the node to avoid modifying the original node in case of infeasibility
//     bool node_is_valid = this->validitycheck(node);
//     this->model->scenario_name = node->scenario_name;
//     this->model->first_stage_IX = node->first_stage_IX;
//     this->model->second_stage_IX = node->second_stage_IX;
//     this->model->clearDAG(); // remove the previous DAG to avoid interference
//     if (!this->solvefullModel){
//         this->model->buildDAG();
//     }else{
//         this->model->buildFullModelDAG();
//     }

//     ILOSTLBEGIN
//     IloEnv env;
//     env.setOut(env.getNullStream());
//     env.setWarning(env.getNullStream());
//     IloModel cplexmodel(env);
//     IloRangeArray c(env);
//     IloObjective obj (env);
//     IloNumVarArray x(env);

//     this->model->generateLP(&env,&cplexmodel,&c,&obj,&x);
//     IloCplex cplex(cplexmodel);
//     cplex.setParam(IloCplex::Param::ClockType, 2);
//     cplex.setParam(IloCplex::Param::Simplex::Tolerances::Optimality, 1e-6);
//     cplex.setParam(IloCplex::Param::Simplex::Tolerances::Feasibility, 1e-4);
//     cplex.setParam(IloCplex::Param::Read::Scale, 1);
//     cplex.setParam(IloCplex::AggInd, false);
//     //cplex.setParam(IloCplex::Param::RootAlgorithm, IloCplex::Barrier);
//     cplex.setParam(IloCplex::Param::SolutionType, 2); 

//     IloExpr obj_cons(env);
//     obj_cons+=x[x.getSize()-1]; // objective is always the last variable in our construction
//     cplexmodel.add(obj_cons <= node->UBD*1.01); // add objective constraint to the model
//     obj_cons.end();
    
//     IloExpr objExpr_lower(env);
//     objExpr_lower += (x)[var_idx];    // objective is always the last variable in our construction
//     obj.setExpr(objExpr_lower);
//     objExpr_lower.end();
//     obj.setSense(IloObjective::Minimize);

//     cplex.setOut(env.getNullStream());
//     cplex.exportModel("/Users/jyang872/Desktop/CrappySolver/test.lp"); // please delete

//     cplex.solve();
//     double tolerance=1e-2;
//     if (cplex.getStatus() == IloAlgorithm::Optimal) {
//         double lower_candidate = cplex.getObjValue()-tolerance; // subtract tolerance to avoid numerical issue
//         if (var_idx < node->first_stage_IX.size()) {
//             if (lower_candidate <= node->first_stage_IX[var_idx].u()){
//                 node->first_stage_IX[var_idx].l() = std::max(node->first_stage_IX[var_idx].l(), lower_candidate-tolerance);
//             } else { // this means either bug or degenerate bound
//                 if (std::abs(lower_candidate - node->first_stage_IX[var_idx].u()) < tolerance){ // correct for numerical issue
//                     node->first_stage_IX[var_idx].l() = node->first_stage_IX[var_idx].u();
//                 } else {
//                     throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
//                 }
//             }
//             if (node_is_valid && !this->validitycheck(node)){
//                 throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
//             }
//         }else{
//             if (lower_candidate <= node->second_stage_IX[var_idx - node->first_stage_IX.size()].u()){
//                 node->second_stage_IX[var_idx - node->first_stage_IX.size()].l() = std::max(node->second_stage_IX[var_idx - node->first_stage_IX.size()].l(), lower_candidate-tolerance);
//             } else { // this means either bug or degenerate bound
//                 if (std::abs(lower_candidate - node->second_stage_IX[var_idx - node->first_stage_IX.size()].u()) < tolerance){ // correct for numerical issue
//                     node->second_stage_IX[var_idx - node->first_stage_IX.size()].l() = node->second_stage_IX[var_idx - node->first_stage_IX.size()].u();
//                 } else {
//                     throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
//                 }
//             }
//             if (node_is_valid && !this->validitycheck(node)){
//                 throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
//             }
//         }
//     } else {
//         node->LBD = INFINITY; // if the lower bound is greater than the upper bound, then the node is infeasible
//         env.end();
//         return false;
//     }
//     env.end();
//     return true;
// }
// bool insideAlgo::getOBBTbounds_upper(xBBNode* node, int var_idx){
//     xBBNode node_copy = *node; // make a copy of the node to avoid modifying the original node in case of infeasibility
//     bool node_is_valid = this->validitycheck(node);
//     this->model->scenario_name = node->scenario_name;
//     this->model->first_stage_IX = node->first_stage_IX;
//     this->model->second_stage_IX = node->second_stage_IX;
//     this->model->clearDAG(); // remove the previous DAG to avoid interference
//     if (!this->solvefullModel){
//         this->model->buildDAG();
//     }else{
//         this->model->buildFullModelDAG();
//     }

//     ILOSTLBEGIN
//     IloEnv env;
//     env.setOut(env.getNullStream());
//     env.setWarning(env.getNullStream());
//     IloModel cplexmodel(env);
//     IloRangeArray c(env);
//     IloObjective obj (env);
//     IloNumVarArray x(env);

//     this->model->generateLP(&env,&cplexmodel,&c,&obj,&x);
//     IloCplex cplex(cplexmodel);
//     cplex.setParam(IloCplex::Param::ClockType, 2);
//     cplex.setParam(IloCplex::Param::Simplex::Tolerances::Optimality, 1e-6);
//     cplex.setParam(IloCplex::Param::Simplex::Tolerances::Feasibility, 1e-4);
//     cplex.setParam(IloCplex::Param::Read::Scale, 1);
//     cplex.setParam(IloCplex::AggInd, false);
//     //cplex.setParam(IloCplex::Param::RootAlgorithm, IloCplex::Barrier);
//     cplex.setParam(IloCplex::Param::SolutionType, 2); 
//     IloExpr obj_cons(env);
//     obj_cons+=x[x.getSize()-1]; // objective is always the last variable in our construction
//     cplexmodel.add(obj_cons <= node->UBD*1.01); // add objective constraint to the model
//     obj_cons.end();

//     IloExpr objExpr_upper(env);
//     objExpr_upper += (x)[var_idx];    // objective is always the last variable in our construction
//     obj.setExpr(objExpr_upper);
//     objExpr_upper.end();
//     obj.setSense(IloObjective::Maximize);
//     cplex.setOut(env.getNullStream());
//     cplex.exportModel("/Users/jyang872/Desktop/CrappySolver/test.lp"); // please delete

//     cplex.solve();
//     double tolerance=1e-2;
//     if (cplex.getStatus() == IloAlgorithm::Optimal) {
//         double upper_candidate = cplex.getObjValue()+tolerance;
//         if (var_idx < node->first_stage_IX.size()) {
//             if (upper_candidate >= node->first_stage_IX[var_idx].l()){
//                 node->first_stage_IX[var_idx].u() = std::min(node->first_stage_IX[var_idx].u(), upper_candidate+tolerance);
//             } else { // this means either bug or degenerate bound
//                 if (std::abs(upper_candidate - node->first_stage_IX[var_idx].l()) < tolerance){ // correct for numerical issue
//                     node->first_stage_IX[var_idx].u() = node->first_stage_IX[var_idx].l();
//                 } else {
//                     throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
//                 }
//             }
//             if (node_is_valid && !this->validitycheck(node)){
//                 throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
//             }
//         }else{
//             if (upper_candidate >= node->second_stage_IX[var_idx - node->first_stage_IX.size()].l()){
//                 node->second_stage_IX[var_idx - node->first_stage_IX.size()].u() = std::min(node->second_stage_IX[var_idx - node->first_stage_IX.size()].u(), upper_candidate+tolerance);
//             } else { // this means either bug or degenerate bound
//                 if (std::abs(upper_candidate - node->second_stage_IX[var_idx - node->first_stage_IX.size()].l()) < tolerance){ // correct for numerical issue
//                     node->second_stage_IX[var_idx - node->first_stage_IX.size()].u() = node->second_stage_IX[var_idx - node->first_stage_IX.size()].l();
//                 } else {
//                     throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
//                 }
//             }
//             if (node_is_valid && !this->validitycheck(node)){
//                 throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
//             }
//         }
//     } else {
//         node->LBD = INFINITY; // if the lower bound is greater than the upper bound, then the node is infeasible
//         env.end();
//         return false;
//     }
//     env.end();
//     return true;
// }

bool insideAlgo::getOBBTbounds_upper(xBBNode* node, int var_idx){
    xBBNode node_copy = *node; // make a copy of the node to avoid modifying the original node in case of infeasibility
    bool node_is_valid = this->validitycheck(node);
    this->model->scenario_name = node->scenario_name;
    this->model->first_stage_IX = node->first_stage_IX;
    this->model->second_stage_IX = node->second_stage_IX;
    this->model->clearDAG(); // remove the previous DAG to avoid interference
    if (!this->solvefullModel){
        this->model->buildDAG();
    }else{
        this->model->buildFullModelDAG();
    }

    try {
        GRBEnv env = GRBEnv(true);
        env.set(GRB_IntParam_OutputFlag, 1); // suppress solver output
        env.start();
        GRBModel grbmodel(env);

        std::vector<GRBVar> x;
        this->model->generateLP(&env, &grbmodel, &x); // builds vars/constraints and sets a MINIMIZE objective on x.back()

        // --- solver parameters ---
        grbmodel.set(GRB_DoubleParam_OptimalityTol, 1e-6);   // Simplex::Tolerances::Optimality
        grbmodel.set(GRB_DoubleParam_FeasibilityTol, 1e-4);  // Simplex::Tolerances::Feasibility
        grbmodel.set(GRB_IntParam_ScaleFlag, 3);              // Read::Scale (approximate)
        grbmodel.set(GRB_IntParam_Aggregate, 0);              // AggInd = false
        grbmodel.set(GRB_IntParam_NumericFocus, 3);           // ~ IloCplex::AggInd = false (no presolve)


        // objective cutoff constraint: obj <= UBD*1.01
        // (generateLP already put the "objective variable" at x.back())
        GRBLinExpr obj_cons = x.back();
        grbmodel.addConstr(obj_cons <= node->UBD * 1.01, "obj_cutoff");

        // OBBT objective: maximize x[var_idx] (overrides the MINIMIZE objective generateLP set)
        GRBLinExpr objExpr_upper = x[var_idx];
        grbmodel.setObjective(objExpr_upper, GRB_MAXIMIZE);

        grbmodel.update(); // push the new constraint + objective before solving
        grbmodel.write("/Users/jyang872/Desktop/CrappySolver/test.lp"); // please delete

        grbmodel.optimize();

        double tolerance = 1e-2;
        int status = grbmodel.get(GRB_IntAttr_Status);
        if (status == GRB_OPTIMAL) {
            double upper_candidate = grbmodel.get(GRB_DoubleAttr_ObjVal) + tolerance;
            if (var_idx < (int)node->first_stage_IX.size()) {
                if (upper_candidate >= node->first_stage_IX[var_idx].l()){
                    node->first_stage_IX[var_idx].u() = std::min(node->first_stage_IX[var_idx].u(), upper_candidate+tolerance);
                } else { // this means either bug or degenerate bound
                    if (std::abs(upper_candidate - node->first_stage_IX[var_idx].l()) < tolerance){ // correct for numerical issue
                        node->first_stage_IX[var_idx].u() = node->first_stage_IX[var_idx].l();
                    } else {
                        throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
                    }
                }
                // if (node_is_valid && !this->validitycheck(node)){
                //     throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
                // }
            } else {
                if (upper_candidate >= node->second_stage_IX[var_idx - node->first_stage_IX.size()].l()){
                    node->second_stage_IX[var_idx - node->first_stage_IX.size()].u() = std::min(node->second_stage_IX[var_idx - node->first_stage_IX.size()].u(), upper_candidate+tolerance);
                } else { // this means either bug or degenerate bound
                    if (std::abs(upper_candidate - node->second_stage_IX[var_idx - node->first_stage_IX.size()].l()) < tolerance){ // correct for numerical issue
                        node->second_stage_IX[var_idx - node->first_stage_IX.size()].u() = node->second_stage_IX[var_idx - node->first_stage_IX.size()].l();
                    } else {
                        throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
                    }
                }
                // if (node_is_valid && !this->validitycheck(node)){
                //     throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
                // }
            }
        } else {
            node->LBD = INFINITY; // if the lower bound is greater than the upper bound, then the node is infeasible
            return false;
        }
        return true;

    } catch (GRBException& e) {
        std::cerr << "Gurobi error code = " << e.getErrorCode() << ": " << e.getMessage() << std::endl;
        throw;
    }
}
bool insideAlgo::getOBBTbounds_lower(xBBNode* node, int var_idx){
    xBBNode node_copy = *node; // make a copy of the node to avoid modifying the original node in case of infeasibility
    bool node_is_valid = this->validitycheck(node);
    this->model->scenario_name = node->scenario_name;
    this->model->first_stage_IX = node->first_stage_IX;
    this->model->second_stage_IX = node->second_stage_IX;
    this->model->clearDAG(); // remove the previous DAG to avoid interference
    if (!this->solvefullModel){
        this->model->buildDAG();
    }else{
        this->model->buildFullModelDAG();
    }

    try {
        GRBEnv env = GRBEnv(true);
        env.set(GRB_IntParam_OutputFlag, 1); // suppress solver output
        env.start();
        GRBModel grbmodel(env);

        std::vector<GRBVar> x;
        this->model->generateLP(&env, &grbmodel, &x); // builds vars/constraints and sets a MINIMIZE objective on x.back()

        // --- solver parameters ---
        grbmodel.set(GRB_DoubleParam_OptimalityTol, 1e-6);   // Simplex::Tolerances::Optimality
        grbmodel.set(GRB_DoubleParam_FeasibilityTol, 1e-4);  // Simplex::Tolerances::Feasibility
        grbmodel.set(GRB_IntParam_ScaleFlag, 3);              // Read::Scale (approximate)
        grbmodel.set(GRB_IntParam_Aggregate, 0);              // AggInd = false
        grbmodel.set(GRB_IntParam_NumericFocus, 3);           // ~ IloCplex::AggInd = false (no presolve)

        // objective cutoff constraint: obj <= UBD*1.01
        GRBLinExpr obj_cons = x.back();
        grbmodel.addConstr(obj_cons <= node->UBD * 1.01, "obj_cutoff");

        // OBBT objective: minimize x[var_idx] (overrides the MINIMIZE objective generateLP already set,
        // but on a different variable — x[var_idx] instead of x.back())
        GRBLinExpr objExpr_lower = x[var_idx];
        grbmodel.setObjective(objExpr_lower, GRB_MINIMIZE);

        grbmodel.update(); // push the new constraint + objective before solving
        grbmodel.write("/Users/jyang872/Desktop/CrappySolver/test.lp"); // please delete

        grbmodel.optimize();

        double tolerance = 1e-2;
        int status = grbmodel.get(GRB_IntAttr_Status);
        if (status == GRB_OPTIMAL) {
            double lower_candidate = grbmodel.get(GRB_DoubleAttr_ObjVal) - tolerance; // subtract tolerance to avoid numerical issue
            if (var_idx < (int)node->first_stage_IX.size()) {
                if (lower_candidate <= node->first_stage_IX[var_idx].u()){
                    node->first_stage_IX[var_idx].l() = std::max(node->first_stage_IX[var_idx].l(), lower_candidate-tolerance);
                } else { // this means either bug or degenerate bound
                    if (std::abs(lower_candidate - node->first_stage_IX[var_idx].u()) < tolerance){ // correct for numerical issue
                        node->first_stage_IX[var_idx].l() = node->first_stage_IX[var_idx].u();
                    } else {
                        throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
                    }
                }
                // if (node_is_valid && !this->validitycheck(node)){
                //     throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
                // }
            } else {
                if (lower_candidate <= node->second_stage_IX[var_idx - node->first_stage_IX.size()].u()){
                    node->second_stage_IX[var_idx - node->first_stage_IX.size()].l() = std::max(node->second_stage_IX[var_idx - node->first_stage_IX.size()].l(), lower_candidate-tolerance);
                } else { // this means either bug or degenerate bound
                    if (std::abs(lower_candidate - node->second_stage_IX[var_idx - node->first_stage_IX.size()].u()) < tolerance){ // correct for numerical issue
                        node->second_stage_IX[var_idx - node->first_stage_IX.size()].l() = node->second_stage_IX[var_idx - node->first_stage_IX.size()].u();
                    } else {
                        throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
                    }
                }
                // if (node_is_valid && !this->validitycheck(node)){
                //     throw std::runtime_error("Error: OBBT made the node invalid, this should not happen");
                // }
            }
        } else {
            node->LBD = INFINITY; // if the lower bound is greater than the upper bound, then the node is infeasible
            return false;
        }
        return true;

    } catch (GRBException& e) {
        std::cerr << "Gurobi error code = " << e.getErrorCode() << ": " << e.getMessage() << std::endl;
        throw;
    }
}





bool insideAlgo::validitycheck(xBBNode* node){
    if (node->UBD_solution.size()>node->first_stage_IX.size()+node->second_stage_IX.size()){
        throw std::runtime_error("Node is invalid, UBD_solution size is greater than the number of variables. UBD_solution size: " + std::to_string(node->UBD_solution.size()) + ", number of variables: " + std::to_string(node->first_stage_IX.size() + node->second_stage_IX.size()));

    }
    double tolerance = 1e-4; // set a small tolerance for numerical issues
    for (int i = 0; i < node->first_stage_IX.size(); i++) {
        if (node->UBD_solution[i] >= node->first_stage_IX[i].l()-tolerance && node->UBD_solution[i] <= node->first_stage_IX[i].u()+tolerance) {
            continue;
        }else{
            //std::cout<<"Node is invalid, UBD_solution["<<i<<"] = "<<node->UBD_solution[i]<<" is not within the bounds of first_stage_IX["<<i<<"] = ("<<node->first_stage_IX[i].l()<<","<<node->first_stage_IX[i].u()<<")"<<std::endl;
            return false;
        }
    }
    for (int i = 0; i < node->second_stage_IX.size(); i++) {
        if (node->UBD_solution[i+node->first_stage_IX.size()] >= node->second_stage_IX[i].l()-tolerance && node->UBD_solution[i+node->first_stage_IX.size()] <= node->second_stage_IX[i].u()+tolerance) {
            continue;
        }else{
            //std::cout<<"Node is invalid, UBD_solution["<<i+node->first_stage_IX.size()<<"] = "<<node->UBD_solution[i+node->first_stage_IX.size()]<<" is not within the bounds of second_stage_IX["<<i<<"] = ("<<node->second_stage_IX[i].l()<<","<<node->second_stage_IX[i].u()<<")"<<std::endl;
            return false;
        }
    }
    // if we reach here, then the node is valid
    return true;

}
void insideAlgo::printLBDsolution(xBBNode* node){
    for (int i = 0; i < node->first_stage_IX.size()+node->second_stage_IX.size(); i++) {
        std::cout<<"Variable "<<i<<": "<<node->branchheuristic.LBD_opt_pt[i]<<std::endl;
    }
}
#endif