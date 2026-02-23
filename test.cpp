#include "src/Algo.h"
#include "src/BBNode.h"
#include <example/Ex844.h>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>   // <-- THIS is the important one
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

int insideAlgo::lbd_calculation_count=0;

double insideAlgo::lbd_calculation_time=0;
int BBNode::node_counter=0;
int main(int argc, char* argv[]) {
    //ProcessMode: -1134.15(20s) -1134.15 (10s) -1126.4218270121305. (3s)
    //Ex844:0.332724(3s) 0.325313529673937(10s) 0.325313529673937(20s)
    //CrdueModel:-18350.146929611754(5s)
    Ex844Model model(BranchingStrategy::pseudo);


    //outsideAlgo CZalgo(&model,-1126.4218270121305,UBDSolver::IPOPT); // provide UBD for outer layer
    insideAlgo CZalgo(&model,ScenarioNames::SCENARIO1,0.325313529673937*1000,true,UBDSolver:: GUROBI); // provide UBD for outer layer
    //std::cout << "UBD is: "<<CZalgo.calculateUBD(&(CZalgo.activeNodes[0]), 1)<<std::endl; // calculate LBD for root node before starting the algorithm, this is important for strong branching to have a good initial LBD for weight update when infeasible
    //std::cout << "LBD is: "<<CZalgo.calculateLBD(&(CZalgo.activeNodes[0]), 1)<<std::endl; // calculate LBD for root node before starting the algorithm, this is important for strong branching to have a good initial LBD for weight update when infeasible

    CZalgo.bestUBDforInfinity=true; // set this to true if you want to use the bestUBD for strong branching weight update when infeasible, set to false if you want to use 0 for weight update when infeasible
    CZalgo.solve(0.3); // relgap=0.1% tolerance, abs=1


    // {
    //     std::ofstream os(argv[1]);
    //     cereal::JSONOutputArchive oarchive(os);
    //     oarchive(cereal::make_nvp("outsideAlgo", CZalgo));
    // }
    return 0;
}