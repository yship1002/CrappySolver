#ifndef ALGO_H
#define ALGO_H
#include <src/BBHeuristic.h>
#include <src/BBNode.h>
#include <example/STModel.h>
#include "ilcplex/ilocplex.h"
#include "gurobi_c++.h"
class Algo {
    public:
        Algo(STModel model,BranchingStrategy strategy);
        Algo()=default; // default constructor
        Algo(const Algo& other)=default;
        STModel model;
        BBNode root;
        std::vector<BBNode> activeNodes;
        int getWorstNodeIdx();
        void branchNodeAtIdx(int idx);
        double getBestUBD();
        double getWorstLBD();   
        void fathomNodes(double UBD);
        double best_solution;
        double solve(double tolerance);
        double calculateLBD(BBNode node);
        double calculateUBD(BBNode node);
};
#endif // ALGO_H