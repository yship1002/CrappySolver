#include "src/CrappySolver.h"
#include "src/Algo.h"
#include "src/BBNode.h"
#include <example/STModel.h>

int main() {
    STModel model(BranchingStrategy::relwidth);
    int n_first_stage_vars = model.first_stage_IX.size();

    // Loop over each scenario to build subproblem

    const int nvars = n_first_stage_vars + model.second_stage_IX.size();
    mc::FFGraph DAG;
    mc::FFVar X[nvars];


    for (int i = 0; i < nvars; ++i) X[i].set(&DAG);

    // scenario perturbation
    double p = model.perturb[model.scenario_name];
    //std::cout << "Building LP for " << scenario_name << " with perturbation " << p << std::endl;
    // Constraints translated from the Pyomo example (indices assume:
    // X[0]=m.x1, X[1]=m.x2, X[2]=m.x3, X[3]=m.x5,X[4]=m.x4[s], X[5]=m.x6[s],
    // X[6]=m.x7[s], X[7]=m.x8[s], X[8]=m.x9[s], X[9]=m.x10[s]
    // Constraints (mapped from the Pyomo model)
    mc::FFVar c1,c2,c3,c4,c5,c6,c7,c8;
    mc::FFVar nc1,nc2,nc3,nc4,nc5,nc6,nc7,nc8;

    // e1: -x1 * (-0.00667*x8^2 + 0.13167*x8 + 1.12) + x4 == perturb
    double t1=-0.00667;
    double t2=0.13167;
    double t3=1.12;
    c1 = (-X[0] * (t1 * pow(X[7],2) + t2 * X[7] + t3) + X[4]) - p;
    nc1 = -c1;

    // e2_1: -x1 + 1.22*x4 - x5 <= perturb  --> (expr - p) <= 0
    c2 = (-X[0] + 1.22 * X[4] - X[3]) - p;

    // e2_2: -x1 + 1.22*x4 - x5 >= -perturb  --> -(expr + p) <= 0
    c3 = X[0] - 1.22 * X[4] + X[3] - p;

    // e3: -0.001 * x4 * x9 * x6 / (98 - x6) + x3 == perturb
    c4 = (-0.001 * X[4] * X[8] * X[5])/(98 - X[5])+X[2]-p;     // this is the problem
    nc4 = -c4;

    // e4: 0.038*x8^2 - 1.098*x8 - 0.325*x6 + x7 == 57.425
    c5 = (0.038 * pow(X[7],2) - 1.098 * X[7] - 0.325 * X[5] + X[6]) - 57.425;
    nc5 = -c5;

    // e5: -(x2 + x5)/x1 + x8 == 0
    c6 = (-(X[1] + X[3]) / X[0] + X[7]);
    nc6 = -c6;

    // e6: x9 + 0.222*x10 == 35.82
    c7 = (X[8] + 0.222 * X[9]) - 35.82;
    nc7 = -c7;

    // e7: -3*x7 + x10 == -133  -> (-3*x7 + x10) + 133 == 0
    c8 = (-3 * X[6] + X[9]) + 133;
    nc8 = -c8;


    mc::FFVar objective =0.333333333*( 5.04 * X[0] + 0.035 * X[1] + 10.0 * X[2] + 3.36 * X[3]- 0.063 * X[4] * X[6]);



    //mc::PolVar<mc::Interval> PF[15];
    std::vector<mc::FFVar> F = {c1,c2,c3,c4,c5,c6,c7,c8,nc1,nc4,nc5,nc6,nc7,nc8,objective};
    mc::FFSubgraph sg = DAG.subgraph(std::vector<mc::FFVar> {F[0]});
    int k = 0;
    for (const mc::FFOp* op : sg.l_op) {
        std::cout << k++ << ": " << op->name() << "\n";

        std::cout << "   out: ";
        print_var(op->varout[0]);
        std::cout << "\n";

        std::cout << "   in : ";
        for (size_t i = 0; i < op->varin.size(); ++i) {
            if (i) std::cout << ", ";
            print_var(op->varin[i]);
        }
        std::cout << "\n\n";
    }


    //DAG.eval(15, F, PF, nvars, X, PX);


    int a=1;
    return 0;   
}