#ifndef BBNODE_H
#define BBNODE_H
#include <mcpp/include/interval.hpp>
#include <mcpp/include/ffunc.hpp>
#include <mcpp/include/polimage.hpp>
#include "ilcplex/ilocplex.h"
#include <vector>
#include <example/STModel.h>
#include <src/BBHeuristic.h>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
class BBNode {
    public:
        BBNode(std::vector<mc::Interval> first_stage_IX,std::vector<mc::Interval> second_stage_IX, BranchingStrategy strategy);
        BBNode()=default; // default constructor
        BBNode(const BBNode& other)=default;
        std::vector<mc::Interval> first_stage_IX;
        std::vector<mc::Interval> second_stage_IX;
        BBHeuristic branchheuristic;
        int nodeIdx;
        double LBD;
        double UBD;
        std::vector<BBNode> branch();
};
#endif // BBNODE_H