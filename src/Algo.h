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
    int total_ubd_calculation_count=0;
    std::vector<double> total_ubd_calculation_time;
    int strong_branching_ubd_calculation_count=0; // onlyfor CZ
    std::vector<double> strong_branching_ubd_calculation_time; // only for CZ

    // LBD related bookeeping variables
    int total_lbd_calculation_count=0; // include strong branching calculations
    std::vector<double> total_lbd_calculation_time;
    int strong_branching_lbd_calculation_count=0;
    std::vector<double> strong_branching_lbd_calculation_time;
    std::vector<double> LBD_value_records; // for every LBD calculation recrod result value (exclude strong branching)
    void merge_from(const Tracker& other) {
        total_lbd_calculation_count += other.total_lbd_calculation_count;
        total_ubd_calculation_count += other.total_ubd_calculation_count;
        strong_branching_ubd_calculation_count += other.strong_branching_ubd_calculation_count;
        strong_branching_lbd_calculation_count += other.strong_branching_lbd_calculation_count;

        total_lbd_calculation_time.insert(
            total_lbd_calculation_time.end(),
            other.total_lbd_calculation_time.begin(),
            other.total_lbd_calculation_time.end()
        );

        total_ubd_calculation_time.insert(
            total_ubd_calculation_time.end(),
            other.total_ubd_calculation_time.begin(),
            other.total_ubd_calculation_time.end()
        );
        strong_branching_ubd_calculation_time.insert(
            strong_branching_ubd_calculation_time.end(),
            other.strong_branching_ubd_calculation_time.begin(),
            other.strong_branching_ubd_calculation_time.end()
        );
        strong_branching_lbd_calculation_time.insert(
            strong_branching_lbd_calculation_time.end(),
            other.strong_branching_lbd_calculation_time.begin(),
            other.strong_branching_lbd_calculation_time.end()
        );

        // repeat for any other fields you care about:
        // strong_branching_* counts, strong_branching_* times, etc.
        }
    };
    static void gather_vector_double_to_root(
        const std::vector<double>& local,
        std::vector<double>& out_on_root,
        int root,
        MPI_Comm comm)
        {
        int rank, size;
        MPI_Comm_rank(comm, &rank);
        MPI_Comm_size(comm, &size);

        int local_n = (int)local.size();

        std::vector<int> recv_counts;
        if (rank == root) recv_counts.resize(size);

        MPI_Gather(&local_n, 1, MPI_INT,
                    rank == root ? recv_counts.data() : nullptr, 1, MPI_INT,
                    root, comm);

        std::vector<int> displs;
        if (rank == root) {
            displs.resize(size);
            int total = 0;
            for (int r = 0; r < size; ++r) { displs[r] = total; total += recv_counts[r]; }
            out_on_root.resize(total);
        }

        MPI_Gatherv(local_n ? local.data() : nullptr, local_n, MPI_DOUBLE,
                    rank == root ? out_on_root.data() : nullptr,
                    rank == root ? recv_counts.data() : nullptr,
                    rank == root ? displs.data() : nullptr,
                    MPI_DOUBLE,
                    root, comm);
    };
    void merge_across_ranks_to_root(int root, MPI_Comm comm)
    {
        int rank;
        MPI_Comm_rank(comm, &rank);

        // 4a) reduce scalar counts
        long long lbd_sum = 0, ubd_sum = 0;
        long long strong_branching_ubd_calculation_count_sum = 0;
        long long strong_branching_lbd_calculation_count_sum = 0;

        MPI_Reduce(&total_lbd_calculation_count, &lbd_sum,
                    1, MPI_LONG_LONG, MPI_SUM, root, comm);

        MPI_Reduce(&total_ubd_calculation_count, &ubd_sum,
                    1, MPI_LONG_LONG, MPI_SUM, root, comm);
        MPI_Reduce(&strong_branching_ubd_calculation_count, &strong_branching_ubd_calculation_count_sum,
                    1, MPI_LONG_LONG, MPI_SUM, root, comm);
        MPI_Reduce(&strong_branching_lbd_calculation_count, &strong_branching_lbd_calculation_count_sum,
                    1, MPI_LONG_LONG, MPI_SUM, root, comm); 

        // 4b) gather timing vectors
        std::vector<double> lbd_times_gathered;
        std::vector<double> ubd_times_gathered;
        std::vector<double> strong_branching_lbd_times_gathered;
        std::vector<double> strong_branching_ubd_times_gathered;

        gather_vector_double_to_root(total_lbd_calculation_time, lbd_times_gathered, root, comm);
        gather_vector_double_to_root(total_ubd_calculation_time, ubd_times_gathered, root, comm);
        gather_vector_double_to_root(strong_branching_lbd_calculation_time, strong_branching_lbd_times_gathered, root, comm);
        gather_vector_double_to_root(strong_branching_ubd_calculation_time, strong_branching_ubd_times_gathered, root, comm);
        // 4c) root becomes the merged tracker; others keep local (or clear)
        if (rank == root) {
            total_lbd_calculation_count = lbd_sum;
            total_ubd_calculation_count = ubd_sum;
            total_lbd_calculation_time.swap(lbd_times_gathered);
            total_ubd_calculation_time.swap(ubd_times_gathered);
            strong_branching_lbd_calculation_count = strong_branching_lbd_calculation_count_sum;
            strong_branching_ubd_calculation_count = strong_branching_ubd_calculation_count_sum;
            strong_branching_lbd_calculation_time.swap(strong_branching_lbd_times_gathered);
            strong_branching_ubd_calculation_time.swap(strong_branching_ubd_times_gathered);
        }
    };
    template<class Archive>
    void serialize(Archive& ar)
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
        Tracker tracker;
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