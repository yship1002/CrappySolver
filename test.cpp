#include "src/Algo.h"
#include "src/BBNode.h"
#include <Crappy_Fuzzy_Problem_Library/EDUnits.h>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>   // <-- THIS is the important one
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

int insideAlgo::lbd_calculation_count=0;

double insideAlgo::lbd_calculation_time=0;
int BBHeuristic::refresh_meter=0;
int BBNode::node_counter=0;
int main(int argc, char* argv[]) {
    //ProcessMode: -1134.15(20s) -1134.15 (10s) -1126.4218270121305. (3s)
    //Ex844:0.332724(3s) 0.325313529673937(10s) 0.325313529673937(20s)
    //CrudeModel: -19658.3 (121) -19204.1(12121)
    //Ex722:   -0.352759(10s)
    // CHPSIze:3.03*1000
    //Edunits:58240 (58216.75904279342+13.16696553855068+10.649036512259626)
    //(42590.3++10.64)
    //edunits_nocp:56844

    // 58240 85440
    EDUnits model(BranchingStrategy::pseudo);

    //outsideAlgo CZalgo(&model,58240,UBDSolver::GUROBI); // provide UBD for outer layer
    insideAlgo CZalgo(&model,ScenarioNames::SCENARIO2,INFINITY,false,UBDSolver::GUROBI); // provide UBD for outer layer
    std::cout << "UBD is: "<<CZalgo.calculateUBD(&(CZalgo.activeNodes[0]), 1)<<std::endl; // calculate LBD for root node before starting the algorithm, this is important for strong branching to have a good initial LBD for weight update when infeasible
    //std::cout << "LBD is: "<<CZalgo.calculateLBD(&(CZalgo.activeNodes[0]), 1)<<std::endl; // calculate LBD for root node before starting the algorithm, this is important for strong branching to have a good initial LBD for weight update when infeasible
    // CZalgo.OBBT(&(CZalgo.activeNodes[0]),1e-2); // perform OBBT for root node to tighten the first stage variable bounds, this is important for strong branching to have a good initial LBD for weight update when infeasible

    
    //CZalgo.bestUBDforInfinity=true; // set this to true if you want to use the bestUBD for strong branching weight update when infeasible, set to false if you want to use 0 for weight update when infeasible
    //CZalgo.solve(58); // relgap=0.1% tolerance, abs=1


    // {
    //     std::ofstream os(argv[1]);
    //     cereal::JSONOutputArchive oarchive(os);
    //     oarchive(cereal::make_nvp("outsideAlgo", CZalgo));
    // }
    return 0;
}
// x[0]: 8.73527
// x[1]: 499.999
// x[2]: 7.69124e-05
// x[3]: 0.149478
// x[4]: 8.73519
// x[5]: 499.849
// x[6]: 8.81584
// x[7]: 499.961
// x[8]: 7.46185
// x[9]: 314.806
// x[10]: 8.51792
// x[11]: 376.459
// x[12]: 12.973
// x[13]: 187.307
// x[14]: 0.0806498
// x[15]: 0.111439
// x[16]: 1
// x[17]: 0.999464
// x[18]: 0.0103979
// x[19]: 0.00999999
// x[20]: 0.000999991
// x[21]: 0.00099999
// x[22]: 3.388
// x[23]: 0.00099999
// x[24]: 2.41251
// x[25]: 0.0719722
// x[26]: 0.115104
// x[27]: 6.98537e-05
// x[28]: 0.00013568
// x[29]: 0.0260378
// x[30]: 0.025513
// x[31]: 1064
// x[32]: 287.528
// x[33]: 0.000151684
// x[34]: 500000
// x[35]: 311.516
// x[36]: 318.62
// x[37]: 100
// x[38]: 0.00999999

// outsidealgo use UBD please delete
//calculaUBD too much please delete
//favor 18,19 membrance please delete
//sclaefactor please delete
//avgConcDilIntCem test please delete
// wreite cuts please delete
// LBD write LP please delete
// change sanwidh cuts please delete
// objective no openx please delete
// temp disbale first stage branching please delete
// outside use relwidth please delete
// 0.01-0.03 interesting
// strong branching on a very small interval to see improvemen LP solution find optimal
// objective <  cut to the problem
// break chain
// more empahiss on cpaex
// FBBT later since OBBT is more comprehensive 
// make sure current has reasonal number from tarun
// Kannan's paper on 2018