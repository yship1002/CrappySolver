#include "src/Algo.h"
#include "src/BBNode.h"
#include <example/ProcessModel.h>
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
    //ProcessMode: -1134.15 (10s) -1126.4218270121305. (3s)
    //CrdueModel:-18350.146929611754(5s)
    ProcessModel model(BranchingStrategy::pseudo);

    outsideAlgo CZalgo(&model,-1126.4218270121305,UBDSolver::IPOPT); // provide UBD for outer layer
    //insideAlgo CZalgo(&model,ScenarioNames::SCENARIO1, -1126.4218270121305,false,UBDSolver::GUROBI); // provide UBD for outer layer
    //std::cout<<"UBD is: "<<CZalgo.calculateUBD(&(CZalgo.activeNodes[0]), 1)<<std::endl; // calculate UBD for root node before starting the algorithm, this is important for strong branching to have a good initial UBD for weight update when infeasible
    CZalgo.bestUBDforInfinity=true; // set this to true if you want to use the bestUBD for strong branching weight update when infeasible, set to false if you want to use 0 for weight update when infeasible
    CZalgo.solve(1.0); // relgap=0.1% tolerance, abs=1

    {
        std::ofstream os(argv[1]);
        cereal::JSONOutputArchive oarchive(os);
        oarchive(cereal::make_nvp("outsideAlgo", CZalgo));
    }
    // {
    //     std::ofstream os(argv[1]);
    //     cereal::JSONOutputArchive oarchive(os);
    //     oarchive(cereal::make_nvp("outsideAlgo", CZalgo));
    // }
    return 0;
}