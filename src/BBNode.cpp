#include "src/BBNode.h"
Node::Node(std::vector<mc::Interval> first_stage_IX,std::vector<mc::Interval> second_stage_IX) {
    this->first_stage_IX = first_stage_IX;
    this->second_stage_IX = second_stage_IX;
}
BBNode::BBNode(std::vector<mc::Interval> first_stage_IX,std::vector<mc::Interval> second_stage_IX,
    BranchingStrategy strategy): Node(first_stage_IX,second_stage_IX) {

    this->branchheuristic = BBHeuristic(first_stage_IX, strategy);
}
xBBNode::xBBNode(std::vector<mc::Interval> first_stage_IX,std::vector<mc::Interval> second_stage_IX, 
    BranchingStrategy strategy,ScenarioNames scenario_name) : Node(first_stage_IX,second_stage_IX) {

    this->branchheuristic = BBHeuristic(first_stage_IX, second_stage_IX, BranchingStrategy::relwidth);
    this->scenario_name = scenario_name;
}
