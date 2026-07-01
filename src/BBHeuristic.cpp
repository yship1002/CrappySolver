#include "BBHeuristic.h"
BBHeuristic::BBHeuristic(std::vector<mc::Interval> initial_first_stage_IX,
                    std::vector<mc::Interval> initial_second_stage_IX,
                    BranchingStrategy strategy) {
    this->initial_first_stage_IX = initial_first_stage_IX;
    this->initial_second_stage_IX = initial_second_stage_IX;
    this->strategy = strategy;

}
BBHeuristic::BBHeuristic(std::vector<mc::Interval> initial_first_stage_IX,
                    BranchingStrategy strategy){
    this->initial_first_stage_IX = initial_first_stage_IX;
    this->strategy = strategy;

}
int BBHeuristic::getBranchingVarIndex(std::vector<mc::Interval> first_stage_IX,
                                 std::vector<mc::Interval> second_stage_IX){
    int max_idx = 0;
    // if  (BBHeuristic::branch_counter>100)
    // {   
    //     std::cout<<"Now force branching on first stage variable with largest relative width"<<std::endl;
    //     BBHeuristic::branch_counter=-1;
    //     this->strategy=BranchingStrategy::relwidth;
    // }else{
    //     BBHeuristic::branch_counter++;
    // }
    
    
    std::vector<double> score_list;
    if (this->strategy == BranchingStrategy::pseudo) {
        // Pseudo cost branching logic can be implemented here
        double largest_score=0;

        for (size_t i = 0; i < first_stage_IX.size(); ++i) { // go through first stage to get scores
            double pseudo_cost = (first_stage_IX[i].u() - first_stage_IX[i].l())*this->getPseudoCost(i,SCORE_FUNCTION::SUM);
            //pseudo_cost += 50*(first_stage_IX[i].u() - first_stage_IX[i].l())/(this->initial_first_stage_IX[i].u() - this->initial_first_stage_IX[i].l()); // add relative width to pseudo cost to avoid branching on very small width variable
            score_list.push_back(pseudo_cost);
            if (largest_score < pseudo_cost){
                largest_score = pseudo_cost;
                max_idx = i;
            }
        }

        for (size_t i = 0; i < second_stage_IX.size(); ++i) { // go through second stage to get scores
            double pseudo_cost = (second_stage_IX[i].u() - second_stage_IX[i].l())*this->getPseudoCost(i+first_stage_IX.size(),SCORE_FUNCTION::SUM);
            //pseudo_cost += 50*(second_stage_IX[i].u() - second_stage_IX[i].l())/(this->initial_second_stage_IX[i].u() - this->initial_second_stage_IX[i].l()); // add relative width to pseudo cost to avoid branching on very small width variable
            score_list.push_back(pseudo_cost);
            if (pseudo_cost > largest_score) {
                largest_score = pseudo_cost;
                max_idx = static_cast<int>(first_stage_IX.size() + i);
            }
        }


    }else if (this->strategy == BranchingStrategy::relwidth) {
        // Relative width branching logic can be implemented here

        double largest_ratio=0;
        for (size_t i = 0; i < first_stage_IX.size(); ++i) {
            double ratio = (first_stage_IX[i].u() - first_stage_IX[i].l()) / (this->initial_first_stage_IX[i].u() - this->initial_first_stage_IX[i].l());
            if (ratio > largest_ratio) {
                largest_ratio = ratio;
                max_idx = static_cast<int>(i);
            }
        }
        for (size_t i = 0; i < second_stage_IX.size(); ++i) {
            double ratio = (second_stage_IX[i].u() - second_stage_IX[i].l()) / (this->initial_second_stage_IX[i].u() - this->initial_second_stage_IX[i].l());
            if (ratio > largest_ratio) {
                largest_ratio = ratio;
                max_idx = static_cast<int>(first_stage_IX.size() + i);
            }
        }
    }else{
        throw std::invalid_argument("Unknown Branching Strategy");
    }
    if (BBHeuristic::branch_counter==-1){
        this->strategy=BranchingStrategy::pseudo; // reset to pseudo cost branching after force branching on first stage variable
        BBHeuristic::branch_counter=0; //reset branch counter after force branching on first stage variable
    }
    this->score_list=score_list; // store the score for each variable in the current node
    return max_idx;
};
int BBHeuristic::getBranchingVarIndex(std::vector<mc::Interval> first_stage_IX){
    int max_idx = 0;
    if (this->strategy == BranchingStrategy::pseudo) {
        // Pseudo cost branching logic can be implemented here
        double largest_score=0;
        std::vector<double> score_list;
        for (size_t i = 0; i < first_stage_IX.size(); ++i) {
            double pseudo_cost = (first_stage_IX[i].u() - first_stage_IX[i].l())*this->getPseudoCost(i);
            score_list.push_back(pseudo_cost);
            if (largest_score < pseudo_cost){
                largest_score = pseudo_cost;
                max_idx = i;
            }
        }
    }else if (this->strategy == BranchingStrategy::relwidth) {
        // Relative width branching logic can be implemented here

        double largest_ratio=0;
        for (size_t i = 0; i < first_stage_IX.size(); ++i) {
            double ratio = (first_stage_IX[i].u() - first_stage_IX[i].l()) / (this->initial_first_stage_IX[i].u() - this->initial_first_stage_IX[i].l());
            if (ratio > largest_ratio) {
                largest_ratio = ratio;
                max_idx = static_cast<int>(i);
            }
        }

    }else{
        throw std::invalid_argument("Unknown Branching Strategy");
    }
    return max_idx;
};


double BBHeuristic::getBranchingPoint(int idx,std::vector<mc::Interval> first_stage_IX,std::vector<mc::Interval> second_stage_IX ){
    if (idx < first_stage_IX.size()) {
        return (first_stage_IX[idx].l() + first_stage_IX[idx].u()) / 2.0;
    } else {
        int second_stage_idx = idx - first_stage_IX.size();
        return (second_stage_IX[second_stage_idx].l() + second_stage_IX[second_stage_idx].u()) / 2.0;
    }
};

void BBHeuristic::updateWeights(int idx_branched, double left_improve,double right_improve,double range){
    if (left_improve ==INFINITY || right_improve == INFINITY){
        throw std::runtime_error("Improvement values should not be infinity");
    }

    if (left_improve<0){
        left_improve=0;
    }
    if (right_improve<0){
        right_improve=0;
    }

    BBHeuristic::weights[idx_branched].push_back(std::make_pair(left_improve/range,right_improve/range));


  
};

double BBHeuristic::getPseudoCost(int idx_branched,SCORE_FUNCTION score_function){
    double left_sum = 0.0;
    double right_sum = 0.0;
    int memory_Size=INFINITY; // use all the history to calculate pseudo cost
    int counter=0;
    for (int i=BBHeuristic::weights[idx_branched].size()-1; i>=0 && counter<=memory_Size; i--) {
        left_sum += BBHeuristic::weights[idx_branched][i].first;
        right_sum += BBHeuristic::weights[idx_branched][i].second;
        counter++;
    }
    left_sum/=counter;
    right_sum/=counter;


    if (score_function == SCORE_FUNCTION::SUM){
        return this->mu*std::max(left_sum, right_sum)+(1-this->mu)*std::min(left_sum, right_sum);
    }else if (score_function == SCORE_FUNCTION::MULTIPLY){
        return std::max(left_sum, 1E-3)* std::max(right_sum, 1E-3);
    }else{
        throw std::invalid_argument("Unknown SCORE_FUNCTION");
    }
};
