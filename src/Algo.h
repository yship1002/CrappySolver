#ifndef ALGO_H
#define ALGO_H
#include <string>
#include <cmath>
#include <map>
#include <iomanip>
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

enum class withinStrongBranching { yes, no };
enum class solveFullmodel { yes, no };
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
    static double nonsb_lbd_cplex_time; // cumulative pure cplex.solve() time of LBD calculations (exclude strong branching)
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
        // open nodes ordered by LBD (key == node.LBD at insertion): worst node is begin(), fathoming is a tail erase, no O(n) vector shifts.
        // If a node's LBD is changed while it is stored, call rekeyRoot()/insertNode() so the key stays in sync.
        using NodeMap = std::multimap<double,T>;
        using NodeIt = typename NodeMap::iterator;
        NodeMap activeNodes;
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

        virtual int branchNodeAtIdx(NodeIt it,double tolerance,withinStrongBranching flag=withinStrongBranching::no)=0;
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
        int branchNodeAtIdx(NodeIt it,double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;
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
        int branchNodeAtIdx(NodeIt it,double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;
        void strongbranching(xBBNode* node,double tolerance) override;
        double calculateLBD(xBBNode* node,double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;
        double calculateUBD(xBBNode* node,double tolerance,withinStrongBranching flag=withinStrongBranching::no) override;

};
#include "Algo.tpp" // Include the implementation file for template definitions
#endif // ALGO_H