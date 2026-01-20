#include "BBHeuristic.h"
BBHeuristic::BBHeuristic(std::vector<mc::Interval> initial_first_stage_IX,
                    std::vector<mc::Interval> initial_second_stage_IX,
                    BranchingStrategy strategy) {
    this->initial_first_stage_IX = initial_first_stage_IX;
    this->initial_second_stage_IX = initial_second_stage_IX;
    this->strategy = strategy;
    }
int BBHeuristic::getBranchingVarIndex(std::vector<mc::Interval> first_stage_IX,
                                 std::vector<mc::Interval> second_stage_IX){
    double largest_ratio=0;
    int max_idx = 0;
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
    return max_idx;
};
int BBHeuristic::getBranchingVarIndex(std::vector<mc::Interval> first_stage_IX){
    double largest_ratio=0;
    int max_idx = 0;
    for (size_t i = 0; i < first_stage_IX.size(); ++i) {

        double ratio = (first_stage_IX[i].u() - first_stage_IX[i].l()) / (this->initial_first_stage_IX[i].u() - this->initial_first_stage_IX[i].l());
        if (ratio > largest_ratio) {
            largest_ratio = ratio;
            max_idx = static_cast<int>(i);
        }

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
double BBHeuristic::getBranchingPoint(int idx,std::vector<mc::Interval> first_stage_IX){

    return (first_stage_IX[idx].l() + first_stage_IX[idx].u()) / 2.0;
};

void BBHeuristic::updateWeights(int idx_branched, double left_improve,double right_improv){

};

double BBHeuristic::getPseudoCost(int idx_branched,int which_stage,mc::Interval stage_IX){
    return 0.0;
};