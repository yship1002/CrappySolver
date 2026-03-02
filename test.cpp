#include <string>
#include <csignal>
#include <thread>
#include "src/Algo.h"
#include "src/BBNode.h"
#include <example/ProcessModel.h>
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
int Tracker::strong_branching_lbd_calculation_count=0;
std::vector<double> Tracker::strong_branching_lbd_calculation_time={};
std::vector<double> Tracker::LBD_value_records={}; 
std::string Tracker::file_name="test.json"; 
static volatile std::sig_atomic_t terminate_flag = 0;
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

    //ProcessMode: -1134.15(20s) -1134.15 (10s) -1126.4218270121305. (3s)
    //Ex844:0.332724(3s) 0.325313529673937(10s) 0.325313529673937(20s)
    //CrudeModel:-23273.75(5s)
    ProcessModel model(BranchingStrategy::pseudo);

    //outsideAlgo CZalgo(&model,-1126.4218270121305,UBDSolver::IPOPT); // provide UBD for outer layer
    
    insideAlgo CZalgo(&model,ScenarioNames::SCENARIO1,-1134.15,solveFullmodel::yes,UBDSolver:: IPOPT); // provide UBD for outer layer
    //std::cout << "UBD is: "<<CZalgo.calculateUBD(&(CZalgo.activeNodes[0]), 1)<<std::endl; // calculate LBD for root node before starting the algorithm, this is important for strong branching to have a good initial LBD for weight update when infeasible
    //std::cout << "LBD is: "<<CZalgo.calculateLBD(&(CZalgo.activeNodes[0]), 1)<<std::endl; // calculate LBD for root node before starting the algorithm, this is important for strong branching to have a good initial LBD for weight update when infeasible

    CZalgo.bestUBDforInfinity=true; // set this to true if you want to use the bestUBD for strong branching weight update when infeasible, set to false if you want to use 0 for weight update when infeasible
    CZalgo.solve(1); // relgap=0.1% tolerance, abs=1

    {
        std::ofstream os(Tracker::file_name);
        cereal::JSONOutputArchive oarchive(os);
        Tracker::serialize(oarchive);
    }
    watcher.join();

    return 0;
}