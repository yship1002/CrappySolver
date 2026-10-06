#include <type_traits>
#include "src/Algo.h"
#include "src/BBNode.h"
// Include ONLY the model you want to run (and set MODEL_TYPE below to match).
#include <Crappy_Fuzzy_Problem_Library/Ex722.h>
// #include <Crappy_Fuzzy_Problem_Library/ProcessModel.h>
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
int insideAlgo::lbd_calculation_count=0;
double insideAlgo::lbd_calculation_time=0;
bool insideAlgo::in_strong_branching=false;
int insideAlgo::sb_lbd_calculation_count=0;
double insideAlgo::sb_lbd_calculation_time=0;
int insideAlgo::ubd_calculation_count=0;
double insideAlgo::ubd_calculation_time=0;
int BBHeuristic::refresh_meter=0;
int BBNode::node_counter=0;

// ============================ USER CONFIG (edit only this block) ============================
using MODEL_TYPE = Ex722Model;   // must match the included header (Ex722Model, ProcessModel, Ex844Model, CrudeModel, CHPModel, EDUnits, EDUnits_nocp)
constexpr int       NUM_SCENARIOS = 5;    // max: Ex722 20, Process 40, Ex844 20, CHP 8. Ignored by models whose constructor has no scenario count (Crude, EDUnits, EDUnits_nocp)
constexpr BranchingStrategy BRANCHING = BranchingStrategy::relwidth; // for testing use relwidth (no strong branching / reliability probing); pseudo for the full heuristic
constexpr UBDSolver UBD_SOLVER    = UBDSolver::GUROBI;
constexpr double    TOLERANCE     = 92;                 // absolute gap
constexpr double    PROVIDED_UBD  = -92551.4;           // UBD provided to the algorithm (outer UBD is not computed)
constexpr int       LG_ITERATIONS_ROOT = 10;           // Lagrangean iterations at the root node
constexpr int       LG_ITERATIONS_NODE = 3;            // Lagrangean iterations at every other node (1 = CZ bound)
// =============================================================================================

int main(int argc, char* argv[]) {
    // Reference notes (scenarios -> provided UBD / tolerance used before):
    // ProcessModel: -4422.39(20s) -7264.69(40s, tol 7.2); Ex844: 583.156(10s) 20s: UBD 748.34;
    // CrudeModel: -18502.5(3s); Ex722: -92551.4(5s, tol 92) 20s: UBD -37283.5;
    // CHPSize: 3.03*1000; EDUnits: 58240; EDUnits_nocp: 56844

    Ipopt::SmartPtr<STModel> model;
    if constexpr (std::is_constructible_v<MODEL_TYPE, BranchingStrategy, int>) {
        model = new MODEL_TYPE(BRANCHING, NUM_SCENARIOS);
    } else {
        model = new MODEL_TYPE(BRANCHING);
    }
    std::cout << "Model config: scenarios=" << model->scenario_names.size() << ", UBD=" << PROVIDED_UBD << ", tol=" << TOLERANCE << std::endl;

    outsideAlgo LGalgo(GetRawPtr(model), PROVIDED_UBD, UBD_SOLVER);
    LGalgo.bestUBDforInfinity = true; // use bestUBD for strong branching weight update when infeasible, false uses 0
    LGalgo.lg_iterations_root = LG_ITERATIONS_ROOT;
    LGalgo.lg_iterations_node = LG_ITERATIONS_NODE;
    LGalgo.solve(TOLERANCE);

    // *************uncooment this part to get the provided_UBD after you change problem
    //insideAlgo CZalgo(GetRawPtr(model),ScenarioNames::SCENARIO1,INFINITY,true,UBDSolver::GUROBI); // solves the full model
    //std::cout << "UBD is: "<<CZalgo.calculateUBD(&(CZalgo.activeNodes[0]), 1)<<std::endl;
    // ***********************

    // {
    //     std::ofstream os(argv[1]);
    //     cereal::JSONOutputArchive oarchive(os);
    //     oarchive(cereal::make_nvp("outsideAlgo", LGalgo));
    // }
    return 0;
}
