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
enum class UBDSolver
{
    GUROBI,
   IPOPT
};
template<typename T>
class Algo {
    public:
        Algo(STModel* model);
        Algo()=default; // default constructor
        Algo(const Algo& other)=default;
        UBDSolver ubd_solver;
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
        outsideAlgo(STModel* model,double provided_UBD,UBDSolver solver=UBDSolver::IPOPT);
        outsideAlgo()=default; // default constructor
        outsideAlgo(const outsideAlgo& other)=default;
        std::vector<double> LBD_values_records;
        std::vector<int> LBD_calculation_records;
        std::vector<double> LBD_calculation_time_records;
        std::vector<std::vector<std::pair<double, double>>> first_stage_IX_record;
        double cheatstrongbranching(BBNode* node,double tolerance);
        int branchNodeAtIdx(int idx,double tolerance) override;
        double solve(double tolerance) override;
        double calculateLBD(BBNode* node,double tolerance) override;
        double calculateUBD(BBNode* node,double tolerance) override;
        void strongbranching(BBNode* node,double tolerance) override;
        template<class Archive>
        void serialize(Archive& ar) {
            ar(
               cereal::make_nvp("LBD_calculation_records", LBD_calculation_records),
               cereal::make_nvp("first_stage_IX_record", first_stage_IX_record),
               cereal::make_nvp("LBD_values_records", LBD_values_records),
            cereal::make_nvp("LBD_calculation_time_records", LBD_calculation_time_records));
        }
};
class insideAlgo:public Algo<xBBNode>{
    public:
        insideAlgo(STModel* model,ScenarioNames scenario_name,double provided_UBD=INFINITY,bool solvefullModel=false,UBDSolver solver=UBDSolver::IPOPT);
        double provided_UBD;
        bool solvefullModel;
        ScenarioNames scenario_name;
        static int lbd_calculation_count;
        static double lbd_calculation_time;
        std::vector<double> LBD_values_records;
        double solve(double tolerance) override;
        int branchNodeAtIdx(int idx,double tolerance) override;
        void strongbranching(xBBNode* node,double tolerance) override;
        double calculateLBD(xBBNode* node,double tolerance) override;
        double calculateUBD(xBBNode* node,double tolerance) override;
        template<class Archive>
        void serialize(Archive& ar) {
            ar(
               cereal::make_nvp("lbd_calculation_count", lbd_calculation_count),
               cereal::make_nvp("lbd_calculation_time", lbd_calculation_time),
               cereal::make_nvp("LBD_values_records", LBD_values_records));
        }
};
#include "Algo.tpp" // Include the implementation file for template definitions
#endif // ALGO_H