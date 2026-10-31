#ifndef ALGO_H
#define ALGO_H
#include <cmath>
#include <map>
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
        // open nodes ordered by LBD (key == node.LBD at insertion): worst node is begin(), fathoming is a tail erase, no O(n) vector shifts.
        // If a node's LBD is changed while it is stored, call rekeyRoot()/insertNode() so the key stays in sync.
        using NodeMap = std::multimap<double,T>;
        using NodeIt = typename NodeMap::iterator;
        NodeMap activeNodes;
        int iterations;
        NodeIt getWorstNodeIt();
        T& rootNode(){ return this->activeNodes.begin()->second; } // only valid while the tree holds the single root node
        NodeIt insertNode(const T& node){ return this->activeNodes.emplace(node.LBD,node); }
        NodeIt insertNode(T&& node){ double key=node.LBD; return this->activeNodes.emplace(key,std::move(node)); }
        void rekeyRoot(){ // re-sync the key of the (single) root node after its LBD was computed or changed
            auto nh=this->activeNodes.extract(this->activeNodes.begin());
            nh.key()=nh.mapped().LBD;
            this->activeNodes.insert(std::move(nh));
        }
        double getBestUBD();
        double getWorstLBD();   
        void fathomNodes(double UBD);

        bool bestUBDforInfinity=false;

        virtual int branchNodeAtIdx(NodeIt it,double tolerance)=0;
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
        int ubd_every_k_nodes=1; // forwarded to every insideAlgo
        bool ubd_root_only=false; // forwarded to every insideAlgo
        int sb_node_limit=10; // forwarded to every insideAlgo
        bool inherit_scenario_child=true; // CZ: per scenario, the child box containing the parent's incumbent inherits the parent's scenario LBD and skips the inner solve
        std::vector<double> LBD_values_records;
        std::vector<int> LBD_calculation_records;
        std::vector<double> LBD_calculation_time_records;
        std::vector<std::vector<std::pair<double, double>>> first_stage_IX_record;
        double cheatstrongbranching(BBNode* node,double tolerance);
        int branchNodeAtIdx(NodeIt it,double tolerance) override;
        double solve(double tolerance) override;
        double calculateLBD(BBNode* node,double tolerance,bool verbose=false) override;
        double calculateUBD(BBNode* node,double tolerance) override;
        void strongbranching(BBNode* node,double tolerance) override;
        void printFirstStageIX(BBNode* node) override;
        bool validitycheck(BBNode* node);
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
        int ubd_every_k_nodes=1; // local UBD solve at the root and at every k-th child node (1 = every node)
        bool ubd_root_only=false; // true: local UBD solve at the inner root only (with ubd_solver), never at child nodes; overrides ubd_every_k_nodes
        int ubd_node_counter=0; // children seen so far in this tree, used for the every-k-th test
        std::vector<double> incumbent_x; // all-variable point that achieved incumbentUBD (empty if none)
        double incumbentUBD=INFINITY; // best UBD found by any calculateUBD call in this tree, kept even after its node is fathomed or branched
        bool last_ubd_proved_infeasible=false; // set by calculateUBD: the (global) Gurobi solve reported INFEASIBLE or INF_OR_UNBD, i.e. no feasible point in this node's box (never set by Ipopt: a local failure proves nothing)
        int max_inner_iterations=10000; // hard cap on inner B&B iterations; on hitting it, insideAlgo::solve returns the current worst LBD
        double solve(double tolerance) override;
        int branchNodeAtIdx(NodeIt it,double tolerance) override;
        void strongbranching(xBBNode* node,double tolerance) override;
        double calculateLBD(xBBNode* node,double tolerance,bool verbose=false) override;
        double calculateUBD(xBBNode* node,double tolerance) override;
        void printFirstStageIX(xBBNode* node) override;
        void printSecondStageIX(xBBNode* node);
        void weirdstrongbranching(xBBNode* node,double tolerance);
        // Reliability branching: strong-branch probe variables whose pseudocost is unreliable
        // (fewer than reliability_eta samples, or pseudocost==0) before picking the branching variable.
        // Probed variables are ranked by their FRESH probe score (the averaged pseudocost history goes
        // stale as boxes shrink). probe_all=true probes every non-fixed variable (full strong branching).
        bool reliabilityBranching=true;
        bool probe_all=false;
        int sb_node_limit=10; // full strong branching (all non-fixed vars probed) only for the first sb_node_limit branchings of each inner tree, pseudocost history only afterwards
        int sb_branch_count=0;
        int next_node_id=1; // id of the next child created by branchNodeAtIdx (root is 0)
        int reliability_eta=4;
        int max_probe_cands=8; // probe at most this many unreliable candidates per node (ranked by pseudocost score); ignored if probe_all
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