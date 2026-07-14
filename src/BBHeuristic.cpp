#include "BBHeuristic.h"
BBHeuristic::BBHeuristic(std::vector<mc::Interval> initial_first_stage_IX,
                    std::vector<mc::Interval> initial_second_stage_IX,
                    BranchingStrategy strategy) {
    this->initial_first_stage_IX = initial_first_stage_IX;
    this->initial_second_stage_IX = initial_second_stage_IX;
    this->strategy = strategy;
    this->inside_weights.resize(initial_first_stage_IX.size() + initial_second_stage_IX.size());
    this->outside_weights.resize(initial_first_stage_IX.size());

}
BBHeuristic::BBHeuristic(std::vector<mc::Interval> initial_first_stage_IX,
                    BranchingStrategy strategy){
    this->initial_first_stage_IX = initial_first_stage_IX;
    this->strategy = strategy;
    this->outside_weights.resize(initial_first_stage_IX.size());
}
int BBHeuristic::getBranchingVarIndex(std::vector<mc::Interval> first_stage_IX,
                                 std::vector<mc::Interval> second_stage_IX){
    int max_idx = 0;

    std::vector<double> score_list;
    if (this->strategy == BranchingStrategy::pseudo) {
        // Pseudo cost branching logic can be implemented here
        double largest_score=0;
        std::vector<double> pseudo_costs;
        std::vector<double> relwidths;
        for (size_t i = 0; i < first_stage_IX.size(); ++i) { // go through first stage to get scores

            double pseudo_cost = (first_stage_IX[i].u() - first_stage_IX[i].l())*this->getPseudoCost(i,USE_inside_weights::YES);
            double relwidth = (first_stage_IX[i].u() - first_stage_IX[i].l())/(this->initial_first_stage_IX[i].u() - this->initial_first_stage_IX[i].l());
            pseudo_costs.push_back(pseudo_cost);
            relwidths.push_back(relwidth);
            //pseudo_cost += 1000*(first_stage_IX[i].u() - first_stage_IX[i].l())/(this->initial_first_stage_IX[i].u() - this->initial_first_stage_IX[i].l()); // scale by relative width
            //std::cout << "Var index " << i << " Relwidth: "<<relwidth <<std::endl;

            score_list.push_back(pseudo_cost);
            if (largest_score < pseudo_cost){
                largest_score = pseudo_cost;
                max_idx = i;
            }
        }

        for (size_t i = 0; i < second_stage_IX.size(); ++i) { // go through second stage to get scores
            
            double pseudo_cost = (second_stage_IX[i].u() - second_stage_IX[i].l())*this->getPseudoCost(i+first_stage_IX.size(),USE_inside_weights::YES);
            if (i==33){ //please delete
                pseudo_cost = pseudo_cost*100; // scale up the pseudo cost for second stage variables 6-11 to prioritize branching on them
            }
            double relwidth = (second_stage_IX[i].u() - second_stage_IX[i].l())/(this->initial_second_stage_IX[i].u() - this->initial_second_stage_IX[i].l());
            pseudo_costs.push_back(pseudo_cost);
            relwidths.push_back(relwidth);
            //pseudo_cost += 1000*(second_stage_IX[i].u() - second_stage_IX[i].l())/(this->initial_second_stage_IX[i].u() - this->initial_second_stage_IX[i].l()); // scale by relative width
            //std::cout << "Var index " << i+first_stage_IX.size() << " Relwidth: "<<relwidth <<std::endl;

            score_list.push_back(pseudo_cost);
            if (largest_score < pseudo_cost){
                largest_score = pseudo_cost;
                max_idx = static_cast<int>(first_stage_IX.size() + i);
            }
        }
        if (largest_score == 0){
            max_idx=this->argMax(relwidths);
        }
        //max_idx=this->argMax(this->addVectors(this->normalize(pseudo_costs), this->normalize(relwidths)));


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
    this->score_list=score_list; // store the score list for debugging

    return max_idx;
};
int BBHeuristic::getBranchingVarIndex(std::vector<mc::Interval> first_stage_IX){
    int max_idx = 0;
    if (this->strategy == BranchingStrategy::pseudo) {
        // Pseudo cost branching logic can be implemented here
        double largest_score=0;
        std::vector<double> score_list;
        for (size_t i = 0; i < first_stage_IX.size(); ++i) {
            double pseudo_cost = (first_stage_IX[i].u() - first_stage_IX[i].l())*this->getPseudoCost(i,USE_inside_weights::NO);

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
    //return this->LBD_opt_pt[idx]; // return the optimal solution value for the branching variable
    if (idx < first_stage_IX.size()) {

        return (first_stage_IX[idx].l() + first_stage_IX[idx].u()) / 2.0; // if the optimal solution is too close to the lower bound, then branch at the midpoint

    } else {
        int second_stage_idx = idx - first_stage_IX.size();
        return (second_stage_IX[second_stage_idx].l() + second_stage_IX[second_stage_idx].u()) / 2.0; // if the optimal solution is too close to the lower bound, then branch at the midpoint

    }
    // if (idx < first_stage_IX.size()) {
    //     if (this->LBD_opt_pt[idx]-first_stage_IX[idx].l() >= 1e-3) {
    //         if (first_stage_IX[idx].u()-this->LBD_opt_pt[idx] >= 1e-3){
    //             return this->LBD_opt_pt[idx]; // return the optimal solution value for the branching variable
    //         }
            
    //     }else{
    //         return (first_stage_IX[idx].l() + first_stage_IX[idx].u()) / 2.0; // if the optimal solution is too close to the lower bound, then branch at the midpoint
    //     }
    // } else {
    //     int second_stage_idx = idx - first_stage_IX.size();
    //     if (this->LBD_opt_pt[idx]-second_stage_IX[second_stage_idx].l() >= 1e-3) {
    //         if (second_stage_IX[second_stage_idx].u()-this->LBD_opt_pt[idx] >= 1e-3){
    //             return this->LBD_opt_pt[idx]; // return the optimal solution value for the branching variable
    //         }
            
    //     }else{
    //         return (second_stage_IX[second_stage_idx].l() + second_stage_IX[second_stage_idx].u()) / 2.0; // if the optimal solution is too close to the lower bound, then branch at the midpoint
    //     }
    // }
};

void BBHeuristic::updateWeights(int idx_branched, double left_improve,double right_improve,double range,USE_inside_weights use_inside_weights){
    if (left_improve ==INFINITY || right_improve == INFINITY){
        throw std::runtime_error("Improvement values should not be infinity");
    }

    if (left_improve<0){
        left_improve=0;
    }
    if (right_improve<0){
        right_improve=0;
    }
    if (range == 0){
        throw std::runtime_error("Range should not be zero");
    }


    if (use_inside_weights==USE_inside_weights::YES){
        this->inside_weights[idx_branched].push_back(std::make_pair(left_improve/range,right_improve/range));
    }else{
        this->outside_weights[idx_branched].push_back(std::make_pair(left_improve/range,right_improve/range));
    }

};

double BBHeuristic::getPseudoCost(int idx_branched,USE_inside_weights use_inside_weights,SCORE_FUNCTION score_function){
    double left_sum = 0.0;
    double right_sum = 0.0;
    int counter=0;
    int memory_limit=INFINITY; // INFINITY to use all available weights, 0 for all strong branching
    if (use_inside_weights==USE_inside_weights::YES){
        for (int i=this->inside_weights[idx_branched].size()-1;i>=0&&counter<=memory_limit;i--){
            left_sum += this->inside_weights[idx_branched][i].first;
            right_sum += this->inside_weights[idx_branched][i].second;
            counter++;
        }

        left_sum/=counter;
        right_sum/=counter;
    }else{
        for (int i=this->outside_weights[idx_branched].size()-1;i>=0&&counter<=memory_limit;i--){
            left_sum += this->outside_weights[idx_branched][i].first;
            right_sum += this->outside_weights[idx_branched][i].second;
            counter++;
        }

        left_sum/=counter;
        right_sum/=counter;
    }

    if (score_function == SCORE_FUNCTION::SUM){
        return this->mu*std::max(left_sum, right_sum)+(1-this->mu)*std::min(left_sum, right_sum);
    }else if (score_function == SCORE_FUNCTION::MULTIPLY){
        return std::max(left_sum, 1E-3)* std::max(right_sum, 1E-3);
    }else{
        throw std::invalid_argument("Unknown SCORE_FUNCTION");
    }
};
void BBHeuristic::printinsideweights(){
    for (int i=0;i<this->inside_weights.size();i++){
        std::cout<<"Inside weights for variable "<<i<<": ";
        for (const auto& weight: this->inside_weights[i]){
            std::cout<<"("<<weight.first<<","<<weight.second<<") ";
        }
        std::cout<<std::endl;
    }
}
std::vector<double> BBHeuristic::normalize(const std::vector<double>& values) {
    if (values.empty()) return {};

    auto [lo_it, hi_it] = std::minmax_element(values.begin(), values.end());
    double lo = *lo_it, hi = *hi_it;

    std::vector<double> result(values.size());

    if (hi == lo) {
        std::fill(result.begin(), result.end(), 0.5); // avoid div-by-zero
        return result;
    }

    std::transform(values.begin(), values.end(), result.begin(),
        [lo, hi](double x) { return (x - lo) / (hi - lo); });

    return result;
}
// Element-wise addition
std::vector<double> BBHeuristic::addVectors(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must be the same size");
    }

    std::vector<double> result(a.size());
    std::transform(a.begin(), a.end(), b.begin(), result.begin(),
        [](double x, double y) { return x + y; });

    return result;
}

// Find index of max element
size_t BBHeuristic::argMax(const std::vector<double>& values) {
    if (values.empty()) {
        throw std::invalid_argument("Vector is empty");
    }
    auto max_it = std::max_element(values.begin(), values.end());
    return std::distance(values.begin(), max_it);
}