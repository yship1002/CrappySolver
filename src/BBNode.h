#ifndef BBNODE_H
#define BBNODE_H
#include <mcpp/include/interval.hpp>
#include <mcpp/include/ffunc.hpp>
#include <mcpp/include/polimage.hpp>
#include "ilcplex/ilocplex.h"
#include <vector>
#include <Crappy_Fuzzy_Problem_Library/STModel.h>
#include <src/BBHeuristic.h>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
class Node{
    public:
        Node(std::vector<mc::Interval> first_stage_IX,std::vector<mc::Interval> second_stage_IX);
        Node()=default; // default constructor
        Node(const Node& other)=default;
        BBHeuristic branchheuristic;
        std::vector<mc::Interval> first_stage_IX;
        std::vector<mc::Interval> second_stage_IX;
        int node_id;
        double LBD;
        double UBD;
};
class BBNode : public Node {
    public:
        BBNode(std::vector<mc::Interval> first_stage_IX,std::vector<mc::Interval> second_stage_IX,BranchingStrategy strategy);
        BBNode()=default; // default constructor
        BBNode(const BBNode& other)=default;
        std::vector<double> scenario_LBDs; // record LBD for each scenario for this node
        static int node_counter;


};
class xBBNode: public Node {
    public:
        xBBNode(std::vector<mc::Interval> first_stage_IX,std::vector<mc::Interval> second_stage_IX, 
            BranchingStrategy strategy,ScenarioNames scenario_name);
        xBBNode()=default; // default constructor
        xBBNode(const xBBNode& other)=default;
        void printBound();
        std::vector<std::pair<double,double>> strong_branching_storage;
        std::vector<double> UBD_solution;
        ScenarioNames scenario_name;

};
#endif // BBNODE_H