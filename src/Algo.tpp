#ifndef Algo_TPP
#define Algo_TPP
template<typename T>
Algo<T>::Algo(STModel* model) {
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

outsideAlgo::outsideAlgo(STModel* model,double provided_UBD) : Algo<BBNode>(model) {
    this->bestUBD = provided_UBD;
    this->activeNodes.push_back(BBNode(model->first_stage_IX,model->second_stage_IX,model->branching_strategy));


}
double outsideAlgo::cheatstrongbranching(BBNode* node,double tolerance){
    double new_LBD=0.0;
    for (auto& scenario_name : this->model->scenario_names){
        this->model->scenario_name=scenario_name;
        this->model->first_stage_IX=node->first_stage_IX;
        this->model->second_stage_IX=node->second_stage_IX;
        insideAlgo temp_inside_algo(this->model,scenario_name);
        new_LBD+=temp_inside_algo.calculateUBD(&(temp_inside_algo.activeNodes[0]),tolerance);
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

        double left_LBD=this->cheatstrongbranching(&child1,tolerance); // this is cheating version
        double right_LBD=this->cheatstrongbranching(&child2,tolerance); 
        // double left_LBD=this->calculateLBD(&child1,tolerance); // this is real world version
        // double right_LBD=this->calculateLBD(&child2,tolerance);

        if (left_LBD == INFINITY){
            // left child is infeasible, right child no improve split one more time
            if (right_LBD==node->LBD){
                // child1.first_stage_IX[iterator] = mc::Interval(branch_point, (branch_point+node->first_stage_IX[iterator].u())/2.0);
                // child2.first_stage_IX[iterator] = mc::Interval((branch_point+node->first_stage_IX[iterator].u())/2.0, node->first_stage_IX[iterator].u());
                // left_LBD=this->calculateLBD(&child1, tolerance); 
                // right_LBD=this->calculateLBD(&child2, tolerance);
                node->first_stage_IX[iterator] = mc::Interval(branch_point,node->first_stage_IX[iterator].u());
                continue; // rebranch on the same variable again further split
            }else{
                // left child is infeasible, right child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator, this->bestUBD-original_LBD, right_LBD-original_LBD,range);
                }else{
                    node->branchheuristic.updateWeights(iterator, 0, right_LBD-original_LBD,range);
                }
            }
            // reduce range
            node->first_stage_IX[iterator] = mc::Interval(branch_point,node->first_stage_IX[iterator].u());
        }else if (right_LBD == INFINITY){
            // right child is infeasible, left child no improve
            if (left_LBD==node->LBD){
                // child1.first_stage_IX[iterator] = mc::Interval(node->first_stage_IX[iterator].l(), (node->first_stage_IX[iterator].l() + branch_point)/2.0);
                // child2.first_stage_IX[iterator] = mc::Interval((node->first_stage_IX[iterator].l() + branch_point)/2.0, branch_point);
                // left_LBD=this->calculateLBD(&child1, tolerance);
                // right_LBD=this->calculateLBD(&child2, tolerance);
                node->first_stage_IX[iterator] = mc::Interval(node->first_stage_IX[iterator].l(), branch_point);
                continue; // rebranch on the same variable again further split
            }else{
                // right child is infeasible, left child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator, left_LBD-original_LBD, this->bestUBD-original_LBD,range);
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
};
int outsideAlgo::branchNodeAtIdx(int idx,double tolerance) {
    double original_LBD= this->activeNodes[idx].LBD;
    BBNode child1 = this->activeNodes[idx]; // Copy current node
    BBNode::node_idx++; // Increment node index for child nodes
    child1.node_id = BBNode::node_idx; // Assign unique ID to child1
    BBNode child2 = this->activeNodes[idx]; // Copy current node
    BBNode::node_idx++; // Increment node index for child nodes
    child2.node_id = BBNode::node_idx; // Assign unique ID to child2
   
    int branch_idx = this->activeNodes[idx].branchheuristic.getBranchingVarIndex(this->activeNodes[idx].first_stage_IX);
    double branch_point = this->activeNodes[idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[idx].first_stage_IX,this->activeNodes[idx].second_stage_IX);
    double range=branch_point-this->activeNodes[idx].first_stage_IX[branch_idx].l();
    child1.first_stage_IX[branch_idx] = mc::Interval(this->activeNodes[idx].first_stage_IX[branch_idx].l(), branch_point);
    child2.first_stage_IX[branch_idx] = mc::Interval(branch_point, this->activeNodes[idx].first_stage_IX[branch_idx].u());

    this->calculateLBD(&child1, tolerance);
    this->calculateLBD(&child2, tolerance);

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
double outsideAlgo::calculateUBD(BBNode* node,double tolerance) {
    node->UBD = this->bestUBD;
    return node->UBD;
}
double outsideAlgo::calculateLBD(BBNode* node,double tolerance) {
    // this is the inner layer
    double totalLBD = 0.0;
    int before_lbd_calculation_count=insideAlgo::lbd_calculation_count;
    for (auto scenario_name : this->model->scenario_names) {
        this->model->scenario_name = scenario_name;
        this->model->first_stage_IX = node->first_stage_IX;
        this->model->second_stage_IX = node->second_stage_IX;
        insideAlgo inneralgo(this->model,scenario_name);
        double scenario_LBD=inneralgo.solve(tolerance);
        if (scenario_LBD == INFINITY) {
            // if any scenario is infeasible, then the node is infeasible
            totalLBD = INFINITY;
            break;
        }else{
            totalLBD += scenario_LBD;
        }


    }
    this->LBD_calculation_records[node->node_id]=insideAlgo::lbd_calculation_count-before_lbd_calculation_count;
    std::vector<std::pair<double, double>> IX_record;
    for (size_t i = 0; i < node->first_stage_IX.size(); ++i) {
        IX_record.push_back({node->first_stage_IX[i].l(), node->first_stage_IX[i].u()});
    }
    this->first_stage_IX_record[node->node_id]=IX_record;
    std::cout<<"LBD calculation count for this node: "<<insideAlgo::lbd_calculation_count-before_lbd_calculation_count<<std::endl;
    node->LBD = totalLBD;
    return totalLBD;
}

double outsideAlgo::solve(double tolerance) {
    auto start = std::chrono::high_resolution_clock::now();
    int initial_lbd_calculation_count=insideAlgo::lbd_calculation_count;
    this->worstLBD=this->calculateLBD(&(this->activeNodes[0]), tolerance); // calculate LBD for root node
    std::cout<<"Initialization LBD calculation count: "<<insideAlgo::lbd_calculation_count - initial_lbd_calculation_count<<std::endl;
    initial_lbd_calculation_count=insideAlgo::lbd_calculation_count;
    if (this->activeNodes[0].branchheuristic.strategy==BranchingStrategy::pseudo){
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Started Outside Strong Branching"<<std::endl;
        std::cout<<"========================================"<<std::endl;
        this->strongbranching(&(this->activeNodes[0]), tolerance);
        std::cout<<"========================================"<<std::endl;
        std::cout<<"Finished Outside Strong Branching"<<std::endl;
        std::cout<<"Strong branching LBD calculations: "<<insideAlgo::lbd_calculation_count - initial_lbd_calculation_count<<std::endl;
        std::cout<<"========================================"<<std::endl;
    }

    double gap = (this->bestUBD - this->worstLBD)/std::abs(this->bestUBD); // abs gap calculation
    int iterations = 0;
    while (gap > tolerance) {
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
        gap = (this->bestUBD - this->worstLBD)/std::abs(this->bestUBD); // relative gap
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        std::cout<<"----------------------------------------"<<std::endl;
        std::cout<<"Iteration "<<iterations<<std::endl;
        std::cout<<"----------------------------------------"<<std::endl;
        std::cout<<"Current UBD: "<<this->bestUBD<<", LBD: "<<this->worstLBD<<", Gap: "<<100*gap<<"%"<<" Total Wall Time: " << elapsed.count() << " seconds" << std::endl;
        std::cout<<"Total LBD calculations: "<<insideAlgo::lbd_calculation_count<<std::endl;
        std::cout<<"Fathom at start calculations: "<<insideAlgo::fathom_at_start_count<<std::endl;

        iterations++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout<<"========================================"<<std::endl;
    std::cout<<"Algorithm terminated after "<<iterations<<" iterations."<<std::endl;
    std::cout<<"Total Wall Time: " << elapsed.count() << " seconds" << std::endl;
    std::cout<<"Best Solution: " << this->bestUBD << std::endl;

    return this->bestUBD;
}

insideAlgo::insideAlgo(STModel* model,ScenarioNames scenario_name) : Algo<xBBNode>(model) {
    this->scenario_name=scenario_name;
    this->activeNodes.push_back(xBBNode(model->first_stage_IX,model->second_stage_IX,
        model->branching_strategy,this->scenario_name));

}
void insideAlgo::strongbranching(xBBNode* node,double tolerance){
    int record_lbd_calculations_before=insideAlgo::lbd_calculation_count;
    double original_LBD=node->LBD;
    double original_UBD=node->UBD;
    int iterator=0;
    // first stage strong branching
    while (iterator < node->first_stage_IX.size()) { 
        xBBNode child1 = *node;
        xBBNode child2 = *node;
        double branch_point = (node->first_stage_IX[iterator].l() + node->first_stage_IX[iterator].u()) / 2.0;
        double range=branch_point - node->first_stage_IX[iterator].l();
        child1.first_stage_IX[iterator] = mc::Interval(child1.first_stage_IX[iterator].l(), branch_point);
        child2.first_stage_IX[iterator] = mc::Interval(branch_point, child2.first_stage_IX[iterator].u());
        
        double left_LBD=this->calculateLBD(&child1, tolerance); 
        double right_LBD=this->calculateLBD(&child2, tolerance);

        if (left_LBD == INFINITY){
            // left child is infeasible, right child no improve split one more time
            if (right_LBD==node->LBD){
                // child1.first_stage_IX[iterator] = mc::Interval(branch_point, (branch_point+node->first_stage_IX[iterator].u())/2.0);
                // child2.first_stage_IX[iterator] = mc::Interval((branch_point+node->first_stage_IX[iterator].u())/2.0, node->first_stage_IX[iterator].u());
                // left_LBD=this->calculateLBD(&child1, tolerance); 
                // right_LBD=this->calculateLBD(&child2, tolerance);
                node->first_stage_IX[iterator] = mc::Interval(branch_point,node->first_stage_IX[iterator].u());
                continue; // rebranch on the same variable again further split
            }else{
                // left child is infeasible, right child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator, this->bestUBD-original_LBD, right_LBD-original_LBD,range);
                }else{
                    node->branchheuristic.updateWeights(iterator, 0, right_LBD-original_LBD,range);
                }

            }
            // reduce range
            node->first_stage_IX[iterator] = mc::Interval(branch_point,node->first_stage_IX[iterator].u());
        }else if (right_LBD == INFINITY){
            // right child is infeasible, left child no improve
            if (left_LBD==node->LBD){
                // child1.first_stage_IX[iterator] = mc::Interval(node->first_stage_IX[iterator].l(), (node->first_stage_IX[iterator].l() + branch_point)/2.0);
                // child2.first_stage_IX[iterator] = mc::Interval((node->first_stage_IX[iterator].l() + branch_point)/2.0, branch_point);
                // left_LBD=this->calculateLBD(&child1, tolerance);
                // right_LBD=this->calculateLBD(&child2, tolerance);
                node->first_stage_IX[iterator] = mc::Interval(node->first_stage_IX[iterator].l(), branch_point);
                continue; // rebranch on the same variable again further split
            }else{
                // right child is infeasible, left child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator, left_LBD-original_LBD, this->bestUBD-original_LBD,range); // set to bestUBD of this subproblem to avoid infitinity pseducost update
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
        xBBNode child1 = *node;
        xBBNode child2 = *node;
        double branch_point = (node->second_stage_IX[iterator].l() + node->second_stage_IX[iterator].u()) / 2.0;
        double range=branch_point - node->second_stage_IX[iterator].l();
        child1.second_stage_IX[iterator] = mc::Interval(child1.second_stage_IX[iterator].l(), branch_point);
        child2.second_stage_IX[iterator] = mc::Interval(branch_point, child2.second_stage_IX[iterator].u());
        
        double left_LBD=this->calculateLBD(&child1, tolerance); 
        double right_LBD=this->calculateLBD(&child2, tolerance);

        if (left_LBD == INFINITY){
            // left child is infeasible, right child no improve split one more time
            if (right_LBD==node->LBD){
                // child1.second_stage_IX[iterator] = mc::Interval(branch_point, (branch_point+node->second_stage_IX[iterator].u())/2.0);
                // child2.second_stage_IX[iterator] = mc::Interval((branch_point+node->second_stage_IX[iterator].u())/2.0, node->second_stage_IX[iterator].u());
                // left_LBD=this->calculateLBD(&child1, tolerance); 
                // right_LBD=this->calculateLBD(&child2, tolerance);
                node->second_stage_IX[iterator] = mc::Interval(branch_point,node->second_stage_IX[iterator].u());
                continue; // rebranch on the same variable again further split

            }else{
                // left child is infeasible, right child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator+node->first_stage_IX.size(), this->bestUBD-original_LBD, right_LBD-original_LBD,range);
                }else{
                    node->branchheuristic.updateWeights(iterator+node->first_stage_IX.size(), 0, right_LBD-original_LBD,range);
                }
            }
            // reduce range
            node->second_stage_IX[iterator] = mc::Interval(branch_point,node->second_stage_IX[iterator].u());
        }else if (right_LBD == INFINITY){
            // right child is infeasible, left child no improve
            if (left_LBD==node->LBD){
                // child1.second_stage_IX[iterator] = mc::Interval(node->second_stage_IX[iterator].l(), (node->second_stage_IX[iterator].l() + branch_point)/2.0);
                // child2.second_stage_IX[iterator] = mc::Interval((node->second_stage_IX[iterator].l() + branch_point)/2.0, branch_point);
                // left_LBD=this->calculateLBD(&child1, tolerance);
                // right_LBD=this->calculateLBD(&child2, tolerance);
                node->second_stage_IX[iterator] = mc::Interval(node->second_stage_IX[iterator].l(), branch_point);
                continue; // rebranch on the same variable again further split
            }else{
                // right child is infeasible, left child improve
                if (this->bestUBDforInfinity){
                    node->branchheuristic.updateWeights(iterator+node->first_stage_IX.size(), left_LBD-original_LBD, this->bestUBD-original_LBD,range);
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
    };
};
int insideAlgo::branchNodeAtIdx(int idx,double tolerance) {
    double original_LBD= this->activeNodes[idx].LBD;
    xBBNode child1 = this->activeNodes[idx]; // Copy current node
    xBBNode child2 = this->activeNodes[idx]; // Copy current nod    e

    int branch_idx = this->activeNodes[idx].branchheuristic.getBranchingVarIndex(this->activeNodes[idx].first_stage_IX,this->activeNodes[idx].second_stage_IX);
    
    if(branch_idx<this->activeNodes[idx].first_stage_IX.size()){

        // first stage branching
        double branch_point = this->activeNodes[idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[idx].first_stage_IX,this->activeNodes[idx].second_stage_IX);
        double range=branch_point-this->activeNodes[idx].first_stage_IX[branch_idx].l();
        child1.first_stage_IX[branch_idx] = mc::Interval(this->activeNodes[idx].first_stage_IX[branch_idx].l(), branch_point);
        child2.first_stage_IX[branch_idx] = mc::Interval(branch_point, this->activeNodes[idx].first_stage_IX[branch_idx].u());
    
        this->calculateLBD(&child1, tolerance);
        this->calculateLBD(&child2, tolerance);

        if (child1.LBD == INFINITY){
            // left child is infeasible, right child infeasible
            if (child2.LBD == INFINITY){
                // no need to update heuristic if both child are infeasible
            }else{
                // left child is infeasible, right child improve
                if (this->bestUBDforInfinity){
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

    }else if(branch_idx>=this->activeNodes[idx].first_stage_IX.size()){
        
        // second stage branching

        double branch_point = this->activeNodes[idx].branchheuristic.getBranchingPoint(branch_idx,this->activeNodes[idx].first_stage_IX,this->activeNodes[idx].second_stage_IX);
        double range=branch_point-this->activeNodes[idx].second_stage_IX[branch_idx-this->activeNodes[idx].first_stage_IX.size()].l();
        child1.second_stage_IX[branch_idx-this->activeNodes[idx].first_stage_IX.size()] = mc::Interval(this->activeNodes[idx].second_stage_IX[branch_idx-this->activeNodes[idx].first_stage_IX.size()].l(), branch_point);
        child2.second_stage_IX[branch_idx-this->activeNodes[idx].first_stage_IX.size()] = mc::Interval(branch_point, this->activeNodes[idx].second_stage_IX[branch_idx-this->activeNodes[idx].first_stage_IX.size()].u());

        this->calculateLBD(&child1, tolerance);
        this->calculateLBD(&child2, tolerance);

        if (child1.LBD == INFINITY){
            // left child is infeasible, right child infeasible
            if (child2.LBD == INFINITY){
                // no need to update heuristic if both child are infeasible
            }else{
                // left child is infeasible, right child improve
                if (this->bestUBDforInfinity){
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
    
    }
    this->activeNodes.erase(this->activeNodes.begin() + idx);
    this->activeNodes.push_back(child1);
    this->activeNodes.push_back(child2);
    return branch_idx;
}
double insideAlgo::calculateLBD(xBBNode* node,double tolerance) {
    insideAlgo::lbd_calculation_count++;
    this->model->scenario_name = node->scenario_name;
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

        this->model->generateLP(&env,&cplexmodel,&c,&obj,&x);
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
double insideAlgo::calculateUBD(xBBNode* node,double tolerance) {

    this->model->scenario_name = node->scenario_name;
    this->model->first_stage_IX = node->first_stage_IX;
    this->model->second_stage_IX = node->second_stage_IX;

    GRBEnv env = GRBEnv(true); // empty environemtn to turn off annoying Gurobi output
    env.set(GRB_IntParam_OutputFlag, 0);
    env.set(GRB_IntParam_LogToConsole, 0);
    env.start();
    try {
        GRBModel grbmodel = GRBModel(env);
        this->model->generateMINLP(&grbmodel);

        grbmodel.set(GRB_DoubleParam_MIPGap, 1e-10);  // temporarily set to tight gap for testing

        grbmodel.optimize();
        //grbmodel.write("model.sol");
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
        }

        if (status == GRB_INFEASIBLE) {
            std::cerr<<"Gurobi model infeasible (status=" + std::to_string(status) + ").\n";
        } else if (status == GRB_UNBOUNDED) {
            std::cerr<<"Gurobi model unbounded (status=" + std::to_string(status) + ").\n";
        }else {
            std::cerr<<"Gurobi optimization ended with status " + std::to_string(status) + ".\n";
        }
    } catch (GRBException& e) {
        std::cerr << "Gurobi exception: code=" << e.getErrorCode() << " message=" << e.getMessage() << "\n";
    }

    node->UBD = INFINITY;
    return INFINITY;
}
double insideAlgo::solve(double tolerance) {
    this->bestUBD = this->calculateUBD(&(this->activeNodes[0]), tolerance);
    if (this->bestUBD == INFINITY){
        insideAlgo::fathom_at_start_count++;
        return INFINITY; // if the root node is infeasible, return infinity directly
    }
    this->worstLBD = this->calculateLBD(&(this->activeNodes[0]), tolerance);

    if (this->activeNodes[0].branchheuristic.strategy==BranchingStrategy::pseudo){
        // std::cout<<"========================================"<<std::endl;
        // std::cout<<"Started Inside Strong Branching"<<std::endl;
        // std::cout<<"========================================"<<std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        this->strongbranching(&(this->activeNodes[0]), tolerance);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        // std::cout<<"========================================"<<std::endl;
        // std::cout<<"Finished Inside Strong Branching"<<std::endl;
        // std::cout<<"Strong branching Time: " << elapsed.count() << " seconds" << std::endl;
        // std::cout<<"========================================"<<std::endl;
    }
    

    double gap = (this->bestUBD - this->worstLBD)/std::abs(this->bestUBD);

    int iterations = 0;
    while (gap > tolerance) {
        if (iterations > 5000){
            std::cout<<"Reached maximum iterations limit. Terminating..."<<std::endl;
            break;
        }
        if (this->activeNodes.empty()) {
            break;
        }
        
        int idx = this->getWorstNodeIdx();
        int branch_var_idx= this->branchNodeAtIdx( idx,tolerance);
        std::cout<<"Branching variable index: "<<branch_var_idx<<std::endl;

        this->fathomNodes(this->bestUBD);
        this->worstLBD = this->getWorstLBD();

        gap = (this->bestUBD - this->worstLBD) / std::abs(this->bestUBD);
        
        std::cout<<"Inside Iteration "<<iterations<<": Current UBD: "<<this->bestUBD<<", LBD: "<<this->worstLBD<<", Gap: "<<100*gap<<"%"<<std::endl;
        iterations++;
    }
    return this->bestUBD;
}
#endif