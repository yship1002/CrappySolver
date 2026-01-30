#ifndef BBHEURISTIC_H
#define BBHEURISTIC_H
#include <mcpp/include/interval.hpp>
#include <example/STModel.h>
#include <vector>
enum class SCORE_FUNCTION {SUM,MULTIPLY};
class BBHeuristic {
    public:
        BBHeuristic(std::vector<mc::Interval> initial_first_stage_IX,
                    std::vector<mc::Interval> initial_second_stage_IX,
                    BranchingStrategy strategy);
        BBHeuristic(const BBHeuristic& other)=default;
        BBHeuristic()=default; // default constructor
        BranchingStrategy strategy;

        std::vector<mc::Interval> initial_first_stage_IX;
        std::vector<mc::Interval> initial_second_stage_IX;

        std::vector<std::vector<std::pair<double,double>>> weights;

        double mu=1.0/6.0;  // percentage of bigger improvement to consider in pseudo cost update(0-1)
        int getBranchingVarIndex(std::vector<mc::Interval> first_stage_IX,
                                 std::vector<mc::Interval> second_stage_IX);
        int getBranchingVarIndex(std::vector<mc::Interval> first_stage_IX);
        double getBranchingPoint(int idx,std::vector<mc::Interval> first_stage_IX,
                                 std::vector<mc::Interval> second_stage_IX );
        void updateWeights(int idx_branched, double left_improve,double right_improv);
        
        double getPseudoCost(int idx_branched,SCORE_FUNCTION score_function=SCORE_FUNCTION::SUM);


};
#endif // BBHEURISTIC_H