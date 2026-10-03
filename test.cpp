#include <string>
#include <csignal>
#include <thread>
#include "src/Algo.h"
#include "src/BBNode.h"
// Include ONLY the model you want to run (and set MODEL_TYPE below to match).
//#include <Crappy_Fuzzy_Problem_Library/Ex722.h>
#include <Crappy_Fuzzy_Problem_Library/ProcessModel.h>
// #include <Crappy_Fuzzy_Problem_Library/Ex844.h>
// #include <Crappy_Fuzzy_Problem_Library/CrudeModel.h>
// #include <Crappy_Fuzzy_Problem_Library/CHPModel.h>
// #include <Crappy_Fuzzy_Problem_Library/EDUnits.h>
// #include <Crappy_Fuzzy_Problem_Library/EDUnits_nocp.h>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>   // <-- THIS is the important one
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
int Tracker::total_ubd_calculation_count=0;
std::vector<double> Tracker::total_ubd_calculation_time={};
int Tracker::strong_branching_ubd_calculation_count=0; // onlyfor CZ
std::vector<double> Tracker::strong_branching_ubd_calculation_time={}; // only for CZ

int Tracker::total_lbd_calculation_count=0; // include strong branching calculations
std::vector<double> Tracker::total_lbd_calculation_time={};
double Tracker::nonsb_lbd_cplex_time=0.0;
int Tracker::strong_branching_lbd_calculation_count=0;
std::vector<double> Tracker::strong_branching_lbd_calculation_time={};
std::vector<double> Tracker::LBD_value_records={}; 
std::string Tracker::file_name="test.json"; 
static volatile std::sig_atomic_t terminate_flag = 0;
std::vector<std::vector<std::pair<double,double>>> BBHeuristic::weights;
int BBHeuristic::branch_counter=0;
// ============================ USER CONFIG (edit only this block) ============================
using MODEL_TYPE = ProcessModel;   // must match the included header (Ex722Model, ProcessModel, Ex844Model, CrudeModel, CHPModel, EDUnits, EDUnits_nocp)
constexpr int       NUM_SCENARIOS = 40;   // max: Ex722 20, Process 40, Ex844 20, Crude 3, CHP 8, EDUnits 3
constexpr UBDSolver UBD_SOLVER    = UBDSolver::IPOPT;
constexpr double    TOLERANCE     = 7.2;                // absolute gap
constexpr double    PROVIDED_UBD  = -7264.69;           // UBD provided to the algorithm
// =============================================================================================

void handle_signal(int)
{
    terminate_flag = 1;
}
int BBNode::node_counter=0;
int main(int argc, char* argv[]) {
    std::signal(SIGTERM, handle_signal);
    Tracker::file_name=argv[1];
    std::thread watcher([]{
        while (!terminate_flag) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::ofstream os(Tracker::file_name);
        cereal::JSONOutputArchive oarchive(os);
        Tracker::serialize(oarchive);
    });

    // Reference notes: ProcessModel: -4422.39(20s) -7264.69(40s); Ex844: 583.156(10s) 20s: UBD 748.34;
    // CrudeModel: -18502.5(3s); Ex722: -92551.4(5s) 20s: UBD -37283.5;

    Ipopt::SmartPtr<STModel> model = new MODEL_TYPE(BranchingStrategy::pseudo, NUM_SCENARIOS);
    std::cout << "Model config: scenarios=" << NUM_SCENARIOS << ", UBD=" << PROVIDED_UBD << ", tol=" << TOLERANCE << std::endl;

    insideAlgo CZalgo(GetRawPtr(model), ScenarioNames::SCENARIO1, PROVIDED_UBD, solveFullmodel::yes, UBD_SOLVER);
    CZalgo.bestUBDforInfinity = true; // use bestUBD for strong branching weight update when infeasible, false uses 0
    CZalgo.solve(TOLERANCE);

    // {
    //     std::ofstream os(Tracker::file_name);
    //     cereal::JSONOutputArchive oarchive(os);
    //     Tracker::serialize(oarchive);
    // }
    watcher.join();

    return 0;
}