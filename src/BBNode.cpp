#include "src/BBNode.h"
BBNode::BBNode(std::vector<mc::Interval> first_stage_IX, std::vector<mc::Interval> second_stage_IX, BranchingStrategy strategy) {
    this->first_stage_IX = first_stage_IX;
    this->second_stage_IX = second_stage_IX;
    this->branchheuristic = BBHeuristic(first_stage_IX, second_stage_IX, strategy);
}
std::vector<BBNode> BBNode::branch() {

    int branch_idx = this->branchheuristic.getBranchingVarIndex(this->first_stage_IX,this->second_stage_IX);
    BBNode child1 = *this; // Copy current node
    BBNode child2 = *this; // Copy current node
    double branch_point = this->branchheuristic.getBranchingPoint(branch_idx,this->first_stage_IX,this->second_stage_IX);
    if (branch_idx < this->first_stage_IX.size()) {
        // First stage variable
        child1.first_stage_IX[branch_idx] = mc::Interval(child1.first_stage_IX[branch_idx].l(), branch_point);
        child2.first_stage_IX[branch_idx] = mc::Interval(branch_point, child2.first_stage_IX[branch_idx].u());
    } else {
        // Second stage variable
        int second_stage_idx = branch_idx - this->first_stage_IX.size();
        child1.second_stage_IX[second_stage_idx] = mc::Interval(child1.second_stage_IX[second_stage_idx].l(), branch_point);
        child2.second_stage_IX[second_stage_idx] = mc::Interval(branch_point, child2.second_stage_IX[second_stage_idx].u());
    }

    std::vector<BBNode> children;
    children.push_back(child1);
    children.push_back(child2);
    return children;
}