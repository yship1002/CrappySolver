#include "src/BBNode.h"
BBNode::BBNode(std::vector<mc::Interval> first_stage_IX, std::vector<mc::Interval> second_stage_IX, BranchingStrategy strategy) {
    this->first_stage_IX = first_stage_IX;
    this->second_stage_IX = second_stage_IX;
    this->branchheuristic = BBHeuristic(first_stage_IX, second_stage_IX, strategy);
}
