/*  MC++ (FFGraph/FFVar)  ->  Gurobi GenConstrNL
    Strategy A: one MC++ op -> one tiny Gurobi NL constraint, using aux GRBVars.

    Usage:
      - Build DAG + X[] + F[] in MC++ (NO eval needed)
      - Create Gurobi vars gX[] for original X[]
      - Call build_nl_for_one(model, DAG, Xvec, gX, F[k]) to get GRBVar gFk
      - Add final constraint: model.addConstr(gFk <= 100.0);

    Notes:
      - This assumes MC++ headers provide: mc::FFGraph, mc::FFVar, mc::FFOp, mc::FFSubgraph
        and FFOp::TYPE values like PLUS, TIMES, DIV, SIN, IPOW, DPOW, SHIFT, SCALE, NEG, SQR, etc.
      - If your MC++ build uses slightly different enum names, adjust map_ffop_to_grb().
*/
#include <mcpp/include/interval.hpp>
#include <mcpp/include/ffunc.hpp>
#include <mcpp/include/polimage.hpp>
#include "gurobi_c++.h"
#include "example/STModel.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <iostream>

int map_ffop_to_grb(int ffop_type) {
    using T = mc::FFOp::TYPE;
    switch ((T)ffop_type) {
        case T::PLUS:   return GRB_OPCODE_PLUS;
        case T::SHIFT:  return GRB_OPCODE_PLUS;        // x + c
        case T::MINUS:  return GRB_OPCODE_MINUS;
        case T::TIMES:  return GRB_OPCODE_MULTIPLY;
        case T::SCALE:  return GRB_OPCODE_MULTIPLY;    // c * x
        case T::DIV:    return GRB_OPCODE_DIVIDE;
        case T::INV:    return GRB_OPCODE_DIVIDE;      // 1/x
        case T::NEG:    return GRB_OPCODE_UMINUS;
        case T::SIN:    return GRB_OPCODE_SIN;
        case T::COS:    return GRB_OPCODE_COS;
        case T::TAN:    return GRB_OPCODE_TAN;
        case T::EXP:    return GRB_OPCODE_EXP;
        case T::LOG:    return GRB_OPCODE_LOG;
        case T::SQRT:   return GRB_OPCODE_SQRT;
        case T::IPOW:   return GRB_OPCODE_POW;
        case T::DPOW:   return GRB_OPCODE_POW;
        case T::SQR:    return GRB_OPCODE_POW;
        // Unsupported or require special handling
        case T::CNST:
        case T::VAR:
        case T::PROD:
        case T::CHEB:
        case T::XLOG:
        case T::ERF:
        case T::FSTEP:
        case T::MINF:
        case T::MAXF:
        case T::INTER:
        case T::EXTERN:
        default:
            throw std::runtime_error("MC++ FFOp type not mapped to Gurobi NL opcode");
    }
}

int main() {
    std::vector<std::string> OPTYPE{
        "CNST", "VAR",
        "PLUS", "SHIFT", "NEG", "MINUS", "TIMES", "SCALE", "DIV", "INV",
        "PROD", "IPOW", "DPOW", "CHEB", "SQR", "SQRT", "EXP", "LOG", "XLOG",
        "SIN", "COS", "TAN", "ASIN", "ACOS", "ATAN", "COSH", "SINH", "TANH",
        "ERF", "FABS", "FSTEP", "MINF", "MAXF", "INTER", "EXTERN"};
    std::vector<std::string> VARTYPE {"VAR", "AUX", "CINT", "CREAL"};
    STModel model(BranchingStrategy::relwidth);
    int n_first_stage_vars = model.first_stage_IX.size();
    int n_second_stage_vars = model.second_stage_IX.size();

    // Loop over each scenario to build subproblem

    const int nvars = n_first_stage_vars + n_second_stage_vars;
    mc::FFGraph DAG;
    std::vector<mc::FFVar> X(nvars);


    for (int i = 0; i < nvars; ++i) X[i].set(&DAG);

    // scenario perturbation

        double p = model.perturb[scenario_name];
        //std::cout << "Building LP for " << scenario_name << " with perturbation " << p << std::endl;
        // Constraints translated from the Pyomo example (indices assume:
        // X[0]=m.x1, X[1]=m.x2, X[2]=m.x3, X[3]=m.x5,X[4]=m.x4[s], X[5]=m.x6[s],
        // X[6]=m.x7[s], X[7]=m.x8[s], X[8]=m.x9[s], X[9]=m.x10[s]
        // Constraints (mapped from the Pyomo model)
        mc::FFVar c1,c2,c3,c4,c5,c6,c7,c8;
        mc::FFVar nc1,nc4,nc5,nc6,nc7,nc8;

        // e1: -x1 * (-0.00667*x8^2 + 0.13167*x8 + 1.12) + x4 == perturb
        c1 = (-X[0] * (-0.00667 * pow(X[7],2) + 0.13167 * X[7] + 1.12) + X[4]) - p;
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

        //e6: x9 + 0.222*x10 == 35.82
        c7 = (X[8] + 0.222 * X[9]) - 35.82;
        nc7 = -c7;

        // e7: -3*x7 + x10 == -133  -> (-3*x7 + x10) + 133 == 0
        c8 = (-3 * X[6] + X[9]) + 133;
        nc8 = -c8;


        mc::FFVar objective =0.333333333*( 5.04 * X[0] + 0.035 * X[1] + 10.0 * X[2] + 3.36 * X[3]- 0.063 * X[4] * X[6]);
        std::vector<mc::FFVar> F = {c1,c2,c3,c4,c5,c6,c7,c8,nc1,nc4,nc5,nc6,nc7,nc8,objective};
        GRBEnv env = GRBEnv("genconstrnl_indexed.log");

        GRBModel grbmodel = GRBModel(env);

        for (int i = 0; i < n_first_stage_vars; ++i) {
            grbmodel.addVar(model.first_stage_IX[i].l(), model.first_stage_IX[i].u(), 0.0, GRB_CONTINUOUS, ("x" + std::to_string(i)));
        }
        for (int i = 0; i < n_second_stage_vars; ++i) {
            grbmodel.addVar(model.second_stage_IX[i].l(), model.second_stage_IX[i].u(), 0.0, GRB_CONTINUOUS, ("x" + std::to_string(i+n_first_stage_vars)));
        }

        grbmodel.update();

        for (int i = 0; i < F.size(); ++i) {
            mc::FFSubgraph subgraph = DAG.subgraph(std::vector<mc::FFVar> {F[i]});
            for (auto op : subgraph.l_op) {
                if (op->varin.size()==0) continue;
                if (op->varout[0]->id().first == mc::FFVar::CINT || op->varout[0]->id().first == mc::FFVar::CREAL || op->varout[0]->id().first == mc::FFVar::VAR) continue;
                // now we have an aux variable as output
                if (op->varout[0]->id().second == F[i].id().second) {
                    if (i == F.size()-1) { // objective
                        grbmodel.addVar(-GRB_INFINITY, GRB_INFINITY, 1.0, GRB_CONTINUOUS, "aux_"+std::to_string(op->varout[0]->id().second));
                    } else {
                        grbmodel.addVar(-GRB_INFINITY, 0, 0.0, GRB_CONTINUOUS, "aux_"+std::to_string(op->varout[0]->id().second)); // this is final output
                    }
                    grbmodel.update();
                }else{
                    grbmodel.addVar(-GRB_INFINITY, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "aux_"+std::to_string(op->varout[0]->id().second));
                    grbmodel.update();
                }
                if (op->varin.size()==1){ // one input -> one output aux var
                    // check if power then need speical handle

                    std::vector<int >opcode1;
                    opcode1.push_back(map_ffop_to_grb(op->type));

                    std::vector<double> data1;
                    data1.push_back(-1.0);

                    std::vector<int> parent1;
                    parent1.push_back(-1); 

                    switch (op->varin[0]->id().first){
                        case mc::FFVar::VAR:
                            data1.push_back(grbmodel.getVarByName("x"+std::to_string(op->varin[0]->id().second)).index());
                            opcode1.push_back(GRB_OPCODE_VARIABLE);
                            parent1.push_back(0);

                        break;
                        case mc::FFVar::AUX:
                            data1.push_back(grbmodel.getVarByName("aux_"+std::to_string(op->varin[0]->id().second)).index());
                            opcode1.push_back(GRB_OPCODE_VARIABLE);
                            parent1.push_back(0);
                        break;
                        case mc::FFVar::CINT:
                            data1.push_back(op->varin[0]->num().val());
                            opcode1.push_back(GRB_OPCODE_CONSTANT);
                            parent1.push_back(0);
                        break;
                        case mc::FFVar::CREAL:
                            data1.push_back(op->varin[0]->num().val());
                            opcode1.push_back(GRB_OPCODE_CONSTANT);
                            parent1.push_back(0);
                        break;
                        default:
                            throw std::runtime_error("Unsupported input var type for NL constraint");
                    }
                    if (op->type==mc::FFOp::SQR){
                        data1.push_back(2.0); // exponent 2 for SQR
                        opcode1.push_back(GRB_OPCODE_CONSTANT);
                        parent1.push_back(0);
                    }
                    grbmodel.addGenConstrNL(
                        grbmodel.getVarByName("aux_"+std::to_string(op->varout[0]->id().second)),
                        data1.size(),
                        opcode1.data(),
                        data1.data(),
                        parent1.data());
                    grbmodel.update();

                }
                else{ // two input -> one output aux var
                    std::vector<int >opcode2;
                    opcode2.push_back(map_ffop_to_grb(op->type));

                    std::vector<double> data2;
                    data2.push_back(-1.0); 

                    std::vector<int> parent2;
                    parent2.push_back(-1);


                    switch (op->varin[0]->id().first){
                        case mc::FFVar::VAR:
                            data2.push_back(grbmodel.getVarByName("x"+std::to_string(op->varin[0]->id().second)).index());
                            opcode2.push_back(GRB_OPCODE_VARIABLE);
                            parent2.push_back(0);

                        break;
                        case mc::FFVar::AUX:
                            data2.push_back(grbmodel.getVarByName("aux_"+std::to_string(op->varin[0]->id().second)).index());
                            opcode2.push_back(GRB_OPCODE_VARIABLE);
                            parent2.push_back(0);

                        break;
                        case mc::FFVar::CINT:
                            data2.push_back(op->varin[0]->num().val());
                            opcode2.push_back(GRB_OPCODE_CONSTANT);
                            parent2.push_back(0);
                        break;
                        case mc::FFVar::CREAL:
                            data2.push_back(op->varin[0]->num().val());
                            opcode2.push_back(GRB_OPCODE_CONSTANT);
                            parent2.push_back(0);
                        break;
                        default:
                            throw std::runtime_error("Unsupported input var type for NL constraint");
                    }
                    switch (op->varin[1]->id().first){
                        case mc::FFVar::VAR:
                            data2.push_back(grbmodel.getVarByName("x"+std::to_string(op->varin[1]->id().second)).index());
                            opcode2.push_back(GRB_OPCODE_VARIABLE);
                            parent2.push_back(0);
                        break;
                        case mc::FFVar::AUX:
                            data2.push_back(grbmodel.getVarByName("aux_"+std::to_string(op->varin[1]->id().second)).index());
                            opcode2.push_back(GRB_OPCODE_VARIABLE);
                            parent2.push_back(0);
                        break;
                        case mc::FFVar::CINT:
                            data2.push_back(op->varin[1]->num().val());
                            opcode2.push_back(GRB_OPCODE_CONSTANT);
                            parent2.push_back(0);
                        break;
                        case mc::FFVar::CREAL:
                            data2.push_back(op->varin[1]->num().val());
                            opcode2.push_back(GRB_OPCODE_CONSTANT);
                            parent2.push_back(0);
                        break;
                        default:
                            throw std::runtime_error("Unsupported input var type for NL constraint");
                    }
                    grbmodel.addGenConstrNL(
                        grbmodel.getVarByName("aux_"+std::to_string(op->varout[0]->id().second)),
                        data2.size(),
                        opcode2.data(),
                        data2.data(),
                        parent2.data());
                    grbmodel.update();

                }

            }
        }
        grbmodel.optimize();
        std::cout << "Obj: " << grbmodel.get(GRB_DoubleAttr_ObjVal) << std::endl;
    }
    return 0;
}
