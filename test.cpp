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
double insideAlgo::lbd_calculation_time=0;
int BBNode::node_idx=-1;
int main(int argc, char* argv[]) {


    Ipopt::SmartPtr<Ipopt::TNLP> mynlp = new ProcessModel_IPOPT(BranchingStrategy::pseudo);
    ProcessModel_IPOPT* pm =dynamic_cast<ProcessModel_IPOPT*>(GetRawPtr(mynlp));
    Ipopt::SmartPtr<Ipopt::IpoptApplication> app = IpoptApplicationFactory();
    app->Options()->SetNumericValue("tol", 3.82e-6);
    app->Options()->SetStringValue("hessian_approximation", "limited-memory");
    app->Options()->SetStringValue("mu_strategy", "adaptive");
    app->Options()->SetStringValue("output_file", "ipopt.out");
    Ipopt::ApplicationReturnStatus status;
    status = app->Initialize();
    if( status != Ipopt::Solve_Succeeded )
    {
        std::cout << std::endl << std::endl << "*** Error during initialization!" << std::endl;
        return (int) status;
    }

    // Ask Ipopt to solve the problem
    status = app->OptimizeTNLP(mynlp);

    if( status == Ipopt::Solve_Succeeded )
    {
        std::cout << std::endl << std::endl << "*** The problem solved!" << std::endl;
    }
    else if (status == Ipopt::Infeasible_Problem_Detected)
    {
        std::cout << std::endl << std::endl << "*** The problem FAILED!" << std::endl;
    }
    // outsideAlgo CZalgo(&model,-1126.4218270121305); // provide UBD for outer layer
    // //insideAlgo CZalgo(&model,ScenarioNames::SCENARIO1, -1126.4218270121305,true); // provide UBD for outer layer
    // CZalgo.bestUBDforInfinity=true; // set this to true if you want to use the bestUBD for strong branching weight update when infeasible, set to false if you want to use 0 for weight update when infeasible
    // CZalgo.solve(1); // relgap=0.1% tolerance, abs=1
    // {
    //     std::ofstream os(argv[1]);
    //     cereal::JSONOutputArchive oarchive(os);
    //     oarchive(cereal::make_nvp("outsideAlgo", CZalgo));
    // }
    // {
    //     std::ofstream os(argv[1]);
    //     cereal::JSONOutputArchive oarchive(os);
    //     oarchive(cereal::make_nvp("outsideAlgo", CZalgo));
    // }
    return 0;
}