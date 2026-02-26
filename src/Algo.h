#ifndef ALGO_H
#define ALGO_H
#include <string>
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

enum class withinStrongBranching { yes, no };
enum class UBDSolver
{
    GUROBI,
   IPOPT
};
struct Tracker{
    static int total_ubd_calculation_count;
    static std::vector<double> total_ubd_calculation_time;
    static int strong_branching_ubd_calculation_count; // onlyfor CZ
    static std::vector<double> strong_branching_ubd_calculation_time; // only for CZ

    // LBD related bookeeping variables
    static int total_lbd_calculation_count; // include strong branching calculations
    static std::vector<double> total_lbd_calculation_time;
    static int strong_branching_lbd_calculation_count;
    static std::vector<double> strong_branching_lbd_calculation_time;
    static std::vector<double> LBD_value_records; // for every LBD calculation recrod result value (exclude strong branching)
    static std::string file_name; // for output file name
    template<class Archive>
    static void serialize(Archive& ar)
    {        
        ar(
        CEREAL_NVP(total_ubd_calculation_count),
           CEREAL_NVP(total_ubd_calculation_time),
           CEREAL_NVP(strong_branching_ubd_calculation_count),
           CEREAL_NVP(strong_branching_ubd_calculation_time),
           CEREAL_NVP(total_lbd_calculation_count),
           CEREAL_NVP(total_lbd_calculation_time),
           CEREAL_NVP(strong_branching_lbd_calculation_count),
           CEREAL_NVP(strong_branching_lbd_calculation_time),
           CEREAL_NVP(LBD_value_records)
        );
    }
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

        virtual int branchNodeAtIdx(int idx,double tolerance,withinStrongBranching flag=withinStrongBranching::no)=0;
        virtual double solve(double tolerance,withinStrongBranching flag)=0;
        virtual double calculateLBD(T* node,double tolerance,withinStrongBranching flag=withinStrongBranching::no)=0;
        virtual double calculateUBD(T* node,double tolerance,withinStrongBranching flag=withinStrongBranching::no)=0;
        virtual void strongbranching(T* node,double tolerance)=0; 
};
class outsideAlgo:public Algo<BBNode>{
    public:
        outsideAlgo(STModel* model,double provided_UBD,UBDSolver solver=UBDSolver::IPOPT);
        outsideAlgo()=default; // default constructor
        outsideAlgo(const outsideAlgo& other)=default;

        std::vector<int> LBD_calculation_records;
        std::vector<std::vector<std::pair<double, double>>> first_stage_IX_record;
        double cheatstrongbranching(BBNode* node,double tolerance);
        int branchNodeAtIdx(int idx,double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;
        double solve(double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;
        double calculateLBD(BBNode* node,double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;
        double calculateUBD(BBNode* node,double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;
        void strongbranching(BBNode* node,double tolerance) override;
    
};
class insideAlgo:public Algo<xBBNode>{
    public:
        insideAlgo(STModel* model,ScenarioNames scenario_name,double provided_UBD=INFINITY,solveFullmodel solve_full_model_flag=solveFullmodel::no,UBDSolver solver=UBDSolver::IPOPT);

        double provided_UBD;
        solveFullmodel solve_full_model_flag;
        ScenarioNames scenario_name;

        double solve(double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;
        int branchNodeAtIdx(int idx,double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;
        void strongbranching(xBBNode* node,double tolerance) override;
        double calculateLBD(xBBNode* node,double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;
        double calculateUBD(xBBNode* node,double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;

};
#include "Algo.tpp" // Include the implementation file for template definitions
#endif // ALGO_H