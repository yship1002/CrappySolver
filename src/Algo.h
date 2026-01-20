#ifndef ALGO_H
#define ALGO_H

#include <src/BBHeuristic.h>
#include <src/BBNode.h>
#include <example/STModel.h>
#include "ilcplex/ilocplex.h"
#include "gurobi_c++.h"

class Algo {
    public:
        Algo(STModel& model,BranchingStrategy strategy);
        Algo()=default; // default constructor
        Algo(const Algo& other)=default;
        int iterations;
        STModel model;
        std::vector<std::vector<int>> solver_iterations;
        std::vector<BBNode> activeNodes;
        int getWorstNodeIdx();
        virtual void branchNodeAtIdx(int idx,double tolerance);
        double getBestUBD();
        double getWorstLBD();   
        void fathomNodes(double UBD);
        int getTotalSolverNodes();
        double best_solution;
        virtual double solve(double tolerance);
        virtual double calculateLBD(BBNode* node,double tolerance);
        virtual double calculateUBD(BBNode* node,double tolerance);
};

class insideAlgo:public Algo{
    public:
        insideAlgo(STModel& model,BranchingStrategy strategy);
        double solve(double tolerance) override;
        void branchNodeAtIdx(int idx,double tolerance) override;
        double calculateLBD(BBNode* node,double tolerance) override;
        double calculateUBD(BBNode* node,double tolerance) override;
};
#endif // ALGO_H