#ifndef ALGO_H
#define ALGO_H
#include <string>
#include <mpi.h>
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
    static int strong_branching_ubd_calculation_count;
    static std::vector<double> strong_branching_ubd_calculation_time;

    static int total_lbd_calculation_count;
    static std::vector<double> total_lbd_calculation_time;
    static int strong_branching_lbd_calculation_count;
    static std::vector<double> strong_branching_lbd_calculation_time;
    static std::vector<double> LBD_value_records;
    static std::string file_name;

    // NEW: global aggregated scalars (rank 0 will fill these)
    static long long global_total_lbd_count;
    static long long global_total_ubd_count;
    static long long global_sb_lbd_count;
    static long long global_sb_ubd_count;

    static double global_total_lbd_time_sum;
    static double global_total_ubd_time_sum;
    static double global_sb_lbd_time_sum;
    static double global_sb_ubd_time_sum;

    static void mpi_reduce_to_root(MPI_Comm comm = MPI_COMM_WORLD, int root = 0)
    {
        int rank = 0;
        MPI_Comm_rank(comm, &rank);

        auto sum_vec = [](const std::vector<double>& v){
            double s = 0.0;
            for(double x: v) s += x;
            return s;
        };

        long long local_counts[4] = {
            (long long)total_lbd_calculation_count,
            (long long)total_ubd_calculation_count,
            (long long)strong_branching_lbd_calculation_count,
            (long long)strong_branching_ubd_calculation_count
        };

        double local_sums[4] = {
            sum_vec(total_lbd_calculation_time),
            sum_vec(total_ubd_calculation_time),
            sum_vec(strong_branching_lbd_calculation_time),
            sum_vec(strong_branching_ubd_calculation_time)
        };

        long long global_counts[4] = {0,0,0,0};
        double global_sums[4] = {0,0,0,0};

        MPI_Reduce(local_counts, global_counts, 4, MPI_LONG_LONG, MPI_SUM, root, comm);
        MPI_Reduce(local_sums,   global_sums,   4, MPI_DOUBLE,    MPI_SUM, root, comm);

        if(rank == root){
            global_total_lbd_count = global_counts[0];
            global_total_ubd_count = global_counts[1];
            global_sb_lbd_count    = global_counts[2];
            global_sb_ubd_count    = global_counts[3];

            global_total_lbd_time_sum = global_sums[0];
            global_total_ubd_time_sum = global_sums[1];
            global_sb_lbd_time_sum    = global_sums[2];
            global_sb_ubd_time_sum    = global_sums[3];
        }
    }
        template<class Archive>
    static void serialize(Archive& ar)
    {
        ar(


          // NEW: global aggregated fields (rank 0 only meaningful)
          CEREAL_NVP(global_total_lbd_count),
          CEREAL_NVP(global_total_ubd_count),
          CEREAL_NVP(global_sb_lbd_count),
          CEREAL_NVP(global_sb_ubd_count),
          CEREAL_NVP(global_total_lbd_time_sum),
          CEREAL_NVP(global_total_ubd_time_sum),
          CEREAL_NVP(global_sb_lbd_time_sum),
          CEREAL_NVP(global_sb_ubd_time_sum)
        );
    }
}
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
        double calculateLBD_MPI(BBNode* node, double tolerance, withinStrongBranching flag);
        void mpi_worker_loop();
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