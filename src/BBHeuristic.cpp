#include "BBHeuristic.h"
BBHeuristic::BBHeuristic(std::vector<mc::Interval> initial_first_stage_IX,
                    std::vector<mc::Interval> initial_second_stage_IX,
                    BranchingStrategy strategy) {
    this->initial_first_stage_IX = initial_first_stage_IX;
    this->initial_second_stage_IX = initial_second_stage_IX;
    this->strategy = strategy;
    this->weights.resize(initial_first_stage_IX.size() + initial_second_stage_IX.size());
}
BBHeuristic::BBHeuristic(std::vector<mc::Interval> initial_first_stage_IX,
                    BranchingStrategy strategy){
    this->initial_first_stage_IX = initial_first_stage_IX;
    this->strategy = strategy;
    this->weights.resize(initial_first_stage_IX.size());
}
int BBHeuristic::getBranchingVarIndex(std::vector<mc::Interval> first_stage_IX,
                                 std::vector<mc::Interval> second_stage_IX){
    int max_idx = 0;

    std::vector<double> score_list;
    if (this->strategy == BranchingStrategy::pseudo) {
        // Pseudo cost branching logic can be implemented here
        double largest_score=0;

        for (size_t i = 0; i < first_stage_IX.size(); ++i) { // go through first stage to get scores
            double pseudo_cost = (first_stage_IX[i].u() - first_stage_IX[i].l())*this->getPseudoCost(i,SCORE_FUNCTION::SUM);
            score_list.push_back(pseudo_cost);
            if (largest_score < pseudo_cost){
                largest_score = pseudo_cost;
                max_idx = i;
            }
        }

        for (size_t i = 0; i < second_stage_IX.size(); ++i) { // go through second stage to get scores
            double pseudo_cost = (second_stage_IX[i].u() - second_stage_IX[i].l())*this->getPseudoCost(i+first_stage_IX.size(),SCORE_FUNCTION::SUM);
            score_list.push_back(pseudo_cost);
            if (pseudo_cost > largest_score) {
                largest_score = pseudo_cost;
                max_idx = static_cast<int>(first_stage_IX.size() + i);
            }
        }
        std::vector<int> branch_frequency;
        for (auto& weight : this->weights) {
            branch_frequency.push_back(weight.size());
        }
        int frequency_range = *(std::max_element(branch_frequency.begin(), branch_frequency.end()))-*(std::min_element(branch_frequency.begin(), branch_frequency.end()));
        if (frequency_range>5){

            return std::min_element(branch_frequency.begin(), branch_frequency.end()) - branch_frequency.begin();
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
    //std::cout<<"Branching on variable index: "<<max_idx<<std::endl;
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

    if (left_improve<-1e-2 || right_improve<-1e-2){
        throw std::runtime_error("Improvement values should be non-negative");
    }
    if(left_improve<1e-2 && left_improve<=0){ // fix numerical issue if improve is within tol i treat it as no improve
        left_improve=0;
    }
    if(right_improve<1e-2 && right_improve<=0){
        right_improve=0;
    }
    if (left_improve==0 && right_improve==0){
        throw std::runtime_error("Branching range should be positive");
    }

    this->weights[idx_branched].push_back(std::make_pair(left_improve/range,right_improve/range));
  
};

double BBHeuristic::getPseudoCost(int idx_branched,SCORE_FUNCTION score_function){
    double left_sum = 0.0;
    double right_sum = 0.0;

    for (const auto& p : this->weights[idx_branched]) {
        left_sum += p.first;
        right_sum += p.second;
    }
    left_sum/=this->weights[idx_branched].size();
    right_sum/=this->weights[idx_branched].size();


    if (score_function == SCORE_FUNCTION::SUM){
        return this->mu*std::max(left_sum, right_sum)+(1-this->mu)*std::min(left_sum, right_sum);
    }else if (score_function == SCORE_FUNCTION::MULTIPLY){
        return std::max(left_sum, 1E-3)* std::max(right_sum, 1E-3);
    }else{
        throw std::invalid_argument("Unknown SCORE_FUNCTION");
    }
};
