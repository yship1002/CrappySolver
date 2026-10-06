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
#include <Crappy_Fuzzy_Problem_Library/STModel.h>
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
        int iterations;
        int getWorstNodeIdx();
        double getBestUBD();
        double getWorstLBD();   
        void fathomNodes(double UBD);

        bool bestUBDforInfinity=false;

        virtual int branchNodeAtIdx(int idx,double tolerance)=0;
        virtual double solve(double tolerance)=0;
        virtual double calculateLBD(T* node,double tolerance,bool verbose=false)=0;
        virtual double calculateUBD(T* node,double tolerance)=0;
        virtual void strongbranching(T* node,double tolerance)=0;
        virtual void printFirstStageIX(T* node)=0;
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
        double calculateLBD(BBNode* node,double tolerance,bool verbose=false) override;
        double calculateUBD(BBNode* node,double tolerance) override;
        void strongbranching(BBNode* node,double tolerance) override;
        void printFirstStageIX(BBNode* node) override;
        bool validitycheck(BBNode* node);
        // Lagrangean decomposition (LG) bound at each node: the scenario subproblems get the extra
        // objective term mu_w^T x_w, mu is updated with Polyak-step subgradient iterations.
        // lg_iterations=1 reduces to the CZ bound (mu=0).
        int lg_iterations_root=10;
        int lg_iterations_node=3;
        double lg_theta=1.0; // initial Polyak step scaling, halved after 2 non-improving iterations
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
        std::vector<double> LBD_calculation_time_records;
        static int lbd_calculation_count;
        static double lbd_calculation_time;
        // LBD solves issued while in_strong_branching is true (outer/inner root strong branching and
        // reliability probes) go to the sb_* counters instead of lbd_calculation_*.
        static bool in_strong_branching;
        static int sb_lbd_calculation_count;
        static double sb_lbd_calculation_time;
        struct StrongBranchingScope { // RAII: flags LBD solves as strong branching for the current scope
            bool previous;
            StrongBranchingScope():previous(in_strong_branching){in_strong_branching=true;}
            ~StrongBranchingScope(){in_strong_branching=previous;}
        };
        static int ubd_calculation_count; // root UBD solves at the start of insideAlgo::solve
        static double ubd_calculation_time;
        std::vector<double> LBD_values_records;
        double solve(double tolerance) override;
        int branchNodeAtIdx(int idx,double tolerance) override;
        void strongbranching(xBBNode* node,double tolerance) override;
        double calculateLBD(xBBNode* node,double tolerance,bool verbose=false) override;
        double calculateUBD(xBBNode* node,double tolerance) override;
        void printFirstStageIX(xBBNode* node) override;
        void printSecondStageIX(xBBNode* node);
        void weirdstrongbranching(xBBNode* node,double tolerance);
        // Lagrangean multipliers on the first-stage variables of this scenario (empty = original objective).
        std::vector<double> mu;
        // Solution of the root UBD solve (first-stage entries first); used as the subgradient point by outsideAlgo.
        std::vector<double> root_UBD_solution;
        // Adds mu^T x_first_stage to the objective F[0] of m's current scenario DAG.
        void applyLagrangeanTerm(STModel* m);
        // Reliability branching: strong-branch probe variables whose pseudocost is unreliable
        // (fewer than reliability_eta samples, or pseudocost==0) before picking the branching variable.
        // Probed variables are ranked by their FRESH probe score (the averaged pseudocost history goes
        // stale as boxes shrink). probe_all=true probes every non-fixed variable (full strong branching).
        bool reliabilityBranching=true;
        bool probe_all=true;
        int reliability_eta=4;
        std::vector<double> probe_scores; // NaN = variable not probed at this node
        void reliabilityProbe(xBBNode* node,double tolerance);
        bool validitycheck(xBBNode* node);
        void printLBDsolution(xBBNode* node);
        bool OBBT(xBBNode* node,double tolerance);
        bool getOBBTbounds_lower(xBBNode* node, int var_idx);
        bool getOBBTbounds_upper(xBBNode* node, int var_idx);
        template<class Archive>
        void serialize(Archive& ar) {
            ar(
               cereal::make_nvp("lbd_calculation_count", lbd_calculation_count),
               cereal::make_nvp("lbd_calculation_time", lbd_calculation_time),
               cereal::make_nvp("sb_lbd_calculation_count", sb_lbd_calculation_count),
               cereal::make_nvp("sb_lbd_calculation_time", sb_lbd_calculation_time),
               cereal::make_nvp("ubd_calculation_count", ubd_calculation_count),
               cereal::make_nvp("ubd_calculation_time", ubd_calculation_time),
               cereal::make_nvp("LBD_values_records", LBD_values_records),
               cereal::make_nvp("LBD_calculation_time_records", LBD_calculation_time_records)
            );
        }
};
#include "Algo.tpp" // Include the implementation file for template definitions
#endif // ALGO_H