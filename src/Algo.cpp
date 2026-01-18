#include "Algo.h"
Algo::Algo(STModel model,BranchingStrategy strategy) {
    this->model = model;
    this->best_solution = std::numeric_limits<double>::infinity();
    this->root= BBNode(this->model.first_stage_IX,this->model.second_stage_IX,strategy);
    this->activeNodes.push_back(this->root);

}
int Algo::getWorstNodeIdx() {
    double worstLBD = std::numeric_limits<double>::infinity();
    int worstNodeIdx = 0;
    for (size_t i = 0; i < this->activeNodes.size(); ++i) {
        if (this->activeNodes[i].LBD < worstLBD) {
            worstLBD = this->activeNodes[i].LBD;
            worstNodeIdx = i;
        }
    }
    return worstNodeIdx;
}
void Algo::branchNodeAtIdx(int idx) {
    std::vector<BBNode> newNodes = this->activeNodes[idx].branch();
    this->calculateLBD(newNodes[0]);
    this->calculateLBD(newNodes[1]);
    this->calculateUBD(newNodes[0]);
    this->calculateUBD(newNodes[1]);
    this->activeNodes.push_back(newNodes[0]);
    this->activeNodes.push_back(newNodes[1]);
    this->activeNodes.erase(this->activeNodes.begin() + idx);
}

double Algo::getBestUBD() {
    double bestUBD = std::numeric_limits<double>::infinity();
    for (const auto& node : this->activeNodes) {
        if (node.UBD < bestUBD) {
            bestUBD = node.UBD;
        }
    }
    return bestUBD;
}

double Algo::getWorstLBD() {
    double worstLBD = std::numeric_limits<double>::infinity();
    for (const auto& node : this->activeNodes) {
        if (node.LBD < worstLBD) {
            worstLBD = node.LBD;
        }
    }
    return worstLBD;
}

void Algo::fathomNodes(double UBD) {
    this->activeNodes.erase(
        std::remove_if(this->activeNodes.begin(), this->activeNodes.end(),
                       [UBD](const BBNode& node) { return node.LBD >= UBD; }),
        this->activeNodes.end());
}

double Algo::solve(double tolerance) {
    // Placeholder implementation of the solve method
    // In a real implementation, this would contain the algorithm to solve the STModel
    // For now, we just set best_solution to a dummy value

    double UBD= this->calculateUBD(this->root);
    double LBD = this->calculateLBD(this->root);
    double gap = std::abs(UBD - LBD); // Dummy gap calculation
    while (gap > tolerance) {
        if (this->activeNodes.empty()) {
            break; // No more nodes to process
        }
        //get worst node idx
        int idx=this->getWorstNodeIdx();
        
        // branch worstnode and calculate new UBD and LBD for both children and delete worstnode
        this->branchNodeAtIdx(idx);

        //update UBD of nodeList and fathom by inf or value dominance
        UBD= this->getBestUBD();
        this->fathomNodes(UBD);
        LBD=this->getWorstLBD();

        // update gap
        gap = std::abs(UBD - LBD);
        
    }
    this->best_solution = UBD;
    return this->best_solution;
}
double Algo::calculateLBD(BBNode node) {
    // Placeholder implementation of LBD calculation
    double totalLBD = 0.0;
    // calculate scenario LBD by solving the LP relaxation with CPLEX
    for (auto scenario_name : this->model.scenario_names) {
        this->model.scenario_name = scenario_name;
        this->model.first_stage_IX = node.first_stage_IX;
        this->model.second_stage_IX = node.second_stage_IX;

        ILOSTLBEGIN
        IloEnv env;
        env.setOut(env.getNullStream());
        env.setWarning(env.getNullStream());
        IloModel cplexmodel(env);
        IloRangeArray c(env);
        IloObjective obj (env);
        IloNumVarArray x(env);

        this->model.generateLP(&env,&cplexmodel,&c,&obj,&x);
        IloCplex cplex(cplexmodel);
        cplex.setParam(IloCplex::Param::ClockType, 2);
        //cplex.setParam(IloCplex::Param::Simplex::Tolerances::Optimality, tol);

        //cplex.exportModel(("/Users/jyang872/Desktop/fuzzy-tribble/scenario" + std::to_string(static_cast<int>(this->model.scenario_name)) + ".lp").c_str());
        cplex.setOut(env.getNullStream());

        cplex.solve();
        totalLBD += cplex.getObjValue();
    }
    return totalLBD;
}
double Algo::calculateUBD(BBNode node) {


    /* Indexed-variable version of the nonlinear example:

        minimize    y[0] + y[1]
        subject to  y[0] = x[1]^2
                    y[1] = sin(2.5 * x[0]) + x[1]
                    y free
                    -1 <= x[i] <= 1
    */


//     GRBEnv env = GRBEnv("genconstrnl_indexed.log");

//     // Create an empty model
//     GRBModel model = GRBModel(env);

//     const int n_first_stage = 2;
//     const int n_second_stage = 2;

//     // Create indexed variables
//     vector<GRBVar> first_stage_vars(n_first_stage);
//     vector<GRBVar> second_stage_vars(n_second_stage);
    
//     // x[i] in [-1, 1] with objective coefficient 0.0
//     for (int i = 0; i < n_first_stage; ++i) {
//       first_stage_vars[i] = model.addVar(-1.0, 1.0, 0.0, GRB_CONTINUOUS,
//                           ("y[" + to_string(i) + "]"));
//     }

//     // y[i] are free and have objective coefficient 1.0
//     for (int i = 0; i < n_second_stage; ++i) {
//       second_stage_vars[i] = model.addVar(-GRB_INFINITY, GRB_INFINITY, 1.0, GRB_CONTINUOUS,
//                           ("x[" + to_string(i) + "]"));
//     }


//     // --- Nonlinear constraint 1: y[0] = x[1]^2 ---
//     // Expression tree for pow(variable, constant)
//     //   pow
//     //   ├─ variable(x[1])
//     //   └─ constant(2.0)
//     int    opcode1[3] = { GRB_OPCODE_POW, GRB_OPCODE_VARIABLE, GRB_OPCODE_CONSTANT };
//     double data1[3]   = { -1.0, (double) x[1].index(), 2.0 };
//     int    parent1[3] = { -1, 0, 0 };

//     model.addGenConstrNL(y[0], 3, opcode1, data1, parent1);

//     // --- Nonlinear constraint 2: y[1] = sin(2.5*x[0]) + x[1] ---
//     // Expression tree:
//     //   plus
//     //   ├─ sin
//     //   │  └─ multiply
//     //   │     ├─ constant(2.5)
//     //   │     └─ variable(x[0])
//     //   └─ variable(x[1])
//     int    opcode2[6] = { GRB_OPCODE_PLUS, GRB_OPCODE_SIN, GRB_OPCODE_MULTIPLY,
//                           GRB_OPCODE_CONSTANT, GRB_OPCODE_VARIABLE, GRB_OPCODE_VARIABLE };
//     double data2[6]   = { -1.0, -1.0, -1.0, 2.5, (double) x[0].index(), (double) x[1].index() };
//     int    parent2[6] = { -1, 0, 1, 2, 2, 0 };

//     model.addGenConstrNL(y[1], 6, opcode2, data2, parent2);

//     // Optimize model
//     model.optimize();

//     // Print solution
//     for (int i = 0; i < n; ++i) {
//       cout << y[i].get(GRB_StringAttr_VarName) << " "
//            << y[i].get(GRB_DoubleAttr_X) << "\n";
//     }
//     for (int i = 0; i < n; ++i) {
//       cout << x[i].get(GRB_StringAttr_VarName) << " "
//            << x[i].get(GRB_DoubleAttr_X) << "\n";
//     }

//     cout << "Obj: " << model.get(GRB_DoubleAttr_ObjVal) << "\n";

//   } catch (GRBException& e) {
//     cout << "Error code = " << e.getErrorCode() << "\n";
//     cout << e.getMessage() << "\n";
//   } catch (...) {
//     cout << "Exception during optimization\n";
//   }

//   return 0;
// }

    return 0.0;
}
