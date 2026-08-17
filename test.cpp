#include "src/Algo.h"
#include "src/BBNode.h"
#include <Crappy_Fuzzy_Problem_Library/EDUnits_nocp.h>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>   // <-- THIS is the important one
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

//
//obbt: LBD, good strong branching, expression polyhedral relaxtion lienar theory testing optinal conditon
//scip: resolved

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
    EDUnits_nocp model(BranchingStrategy::pseudo);

    //outsideAlgo CZalgo(&model,56844,UBDSolver::GUROBI); // provide UBD for outer layer
    //CZalgo.activeNodes[0].branchheuristic.strategy=BranchingStrategy::relwidth; // set branching strategy for outer layer
    insideAlgo CZalgo(&model,ScenarioNames::SCENARIO1,INFINITY,false,UBDSolver::GUROBI); // provide UBD for outer layer
    //std::cout << "UBD is: "<<CZalgo.calculateUBD(&(CZalgo.activeNodes[0]), 1)<<std::endl; // calculate LBD for root node before starting the algorithm, this is important for strong branching to have a good initial LBD for weight update when infeasible
    std::cout << "LBD is: "<<CZalgo.calculateLBD(&(CZalgo.activeNodes[0]), 1,true)<<std::endl; // calculate LBD for root node before starting the algorithm, this is important for strong branching to have a good initial LBD for weight update when infeasible
    //CZalgo.OBBT(&(CZalgo.activeNodes[0]), 1); // calculate OBBT for root node before starting the algorithm, this is important for strong branching to have a good initial LBD for weight update when infeasible
    
    //CZalgo.bestUBDforInfinity=true; // set this to true if you want to use the bestUBD for strong branching weight update when infeasible, set to false if you want to use 0 for weight update when infeasible
    //CZalgo.solve(568); // relgap=0.1% tolerance, abs=1

    // {
    //     std::ofstream os(argv[1]);
    //     cereal::JSONOutputArchive oarchive(os);
    //     oarchive(cereal::make_nvp("outsideAlgo", CZalgo));
    // }
    return 0;
}


// have to be use unit if given a first stage interval to verify
// have to be used unit with CZ with OBBT worth try template let's reuse it.
// have to use currentdensity = 0
// weirdSB on a particular pt from feasible solution 
// weight recent info vs distant info strong branching

// weird strong branching
//LBD:1e-4,1e-4
//OBBT:1e-4,1e-4
// outside use relwidth please delete
// 0.01-0.03 interesting
// strong branching on a very small interval to see improvemen LP solution find optimal
// objective <  cut to the problem
// break chain
// more empahiss on cpaex
// FBBT later since OBBT is more comprehensive 
// make sure current has reasonal number from tarun
// Kannan's paper on 2018
