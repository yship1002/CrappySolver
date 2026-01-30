#ifndef ALGO_H
#define ALGO_H
#include <cmath>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>   // <-- THIS is the important one
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <src/BBHeuristic.h>
#include <src/BBNode.h>
#include <example/STModel.h>
#include "ilcplex/ilocplex.h"
#include "gurobi_c++.h"
#include <chrono>
class Algo {
    public:
        Algo(STModel* model);
        Algo()=default; // default constructor
        Algo(const Algo& other)=default;
        int iterations;
        double worstLBD;
        double bestUBD;
        STModel* model;
        std::vector<std::vector<int>> solver_iterations;
        std::vector<BBNode> activeNodes;

        int getWorstNodeIdx();
        int branchNodeAtIdx(int idx,double tolerance);
        void strongbranching(BBNode* node,double tolerance);
        double getBestUBD();
        double getWorstLBD();   
        void fathomNodes(double UBD);
        int getTotalSolverNodes();
        double best_solution;
        virtual double solve(double tolerance);
        virtual double calculateLBD(BBNode* node,double tolerance);
        virtual double calculateUBD(BBNode* node,double tolerance);
        
        // Cereal serialization support

        template<class Archive>
        void serialize(Archive& ar) {
            ar(CEREAL_NVP(solver_iterations));
        }
};

class insideAlgo:public Algo{
    public:
        insideAlgo(STModel* model);
        double solve(double tolerance) override;
        double calculateLBD(BBNode* node,double tolerance) override;
        double calculateUBD(BBNode* node,double tolerance) override;
};
#endif // ALGO_H