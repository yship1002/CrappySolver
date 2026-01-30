#include "src/Algo.h"
#include "src/BBNode.h"
#include <example/ProcessModel.h>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>   // <-- THIS is the important one
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

int main() {

    ProcessModel model(BranchingStrategy::pseudo);

    Algo CZalgo(&model);

    CZalgo.solve(0.001); // 0.1% tolerance

    // {
    //     std::ofstream os("/Users/jyang872/Desktop/CrappySolver/processl.json");
    //     cereal::JSONOutputArchive oarchive(os);
    //     oarchive(cereal::make_nvp("Algo", CZalgo));
    // }

    return 0;   
}