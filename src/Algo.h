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
template<typename T>
class Algo {
    public:
        Algo(STModel* model);
        Algo()=default; // default constructor
        Algo(const Algo& other)=default;
        double worstLBD;
        double bestUBD;
        STModel* model;
        std::vector<T> activeNodes;
        int getWorstNodeIdx();
        double getBestUBD();
        double getWorstLBD();   
        void fathomNodes(double UBD);
        bool bestUBDforInfinity=false;

        virtual int branchNodeAtIdx(int idx,double tolerance)=0;
        virtual double solve(double tolerance)=0;
        virtual double calculateLBD(T* node,double tolerance)=0;
        virtual double calculateUBD(T* node,double tolerance)=0;
        virtual void strongbranching(T* node,double tolerance)=0;
};
class outsideAlgo:public Algo<BBNode>{
    public:
        outsideAlgo(STModel* model,double provided_UBD);
        outsideAlgo()=default; // default constructor
        outsideAlgo(const outsideAlgo& other)=default;
        double cheatstrongbranching(BBNode* node,double tolerance);
        int branchNodeAtIdx(int idx,double tolerance) override;
        double solve(double tolerance) override;
        double calculateLBD(BBNode* node,double tolerance) override;
        double calculateUBD(BBNode* node,double tolerance) override;
        void strongbranching(BBNode* node,double tolerance) override;
};
class insideAlgo:public Algo<xBBNode>{
    public:
        insideAlgo(STModel* model,ScenarioNames scenario_name);
        ScenarioNames scenario_name;
        static int lbd_calculation_count;
        static int fathom_at_start_count;
        double solve(double tolerance) override;
        int branchNodeAtIdx(int idx,double tolerance) override;
        void strongbranching(xBBNode* node,double tolerance) override;
        double calculateLBD(xBBNode* node,double tolerance) override;
        double calculateUBD(xBBNode* node,double tolerance) override;
};
#include "Algo.tpp" // Include the implementation file for template definitions
#endif // ALGO_H