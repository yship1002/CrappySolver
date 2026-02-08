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
int insideAlgo::fathom_at_start_count=0;
int BBNode::node_idx=-1;
int main() {

    ProcessModel model(BranchingStrategy::pseudo); //ubd=-1126.4218270121305(3) -1134.15(10)

    outsideAlgo CZalgo(&model,-1126.4218270121305); // provide UBD for outer layer
    CZalgo.bestUBDforInfinity=true; // set this to true if you want to use the bestUBD for strong branching weight update when infeasible, set to false if you want to use 0 for weight update when infeasible
    CZalgo.solve(0.001); // 0.1% tolerance

    {
        std::ofstream os("/Users/jyang872/Desktop/CrappySolver/process.json");
        cereal::JSONOutputArchive oarchive(os);
        oarchive(cereal::make_nvp("outsideAlgo", CZalgo));
    }

    return 0;   
}