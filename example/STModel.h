/**
* @file process.h
* @author Jingzhi Yang
* @brief Header file for process instance
* It defines details of the problem instance including heusristic for pseduo cost calculation
*/
#ifndef STMODEL_H
#define STMODEL_H
#include "ilcplex/ilocplex.h"
#include "gurobi_c++.h"
#include <vector>
#include <mcpp/include/interval.hpp>
#include <mcpp/include/polimage.hpp>
#include <mcpp/include/ffunc.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
// std::vector<std::string> OPTYPE{
//     "CNST", "VAR",
//     "PLUS", "SHIFT", "NEG", "MINUS", "TIMES", "SCALE", "DIV", "INV",
//     "PROD", "IPOW", "DPOW", "CHEB", "SQR", "SQRT", "EXP", "LOG", "XLOG",
//     "SIN", "COS", "TAN", "ASIN", "ACOS", "ATAN", "COSH", "SINH", "TANH",
//     "ERF", "FABS", "FSTEP", "MINF", "MAXF", "INTER", "EXTERN"};
// std::vector<std::string> VARTYPE {"VAR", "AUX", "CINT", "CREAL"};
enum ScenarioNames { SCENARIO1=0, SCENARIO2=1, SCENARIO3=2 };
enum class BranchingStrategy { relwidth, pseudo };
class STModel{
    public:
        STModel(BranchingStrategy branching_strategy);
        STModel(const STModel& other)=default;
        STModel()=default; // default constructor
        BranchingStrategy branching_strategy;
        /// A vector of ScenarioNames
        std::vector<ScenarioNames> scenario_names = {ScenarioNames::SCENARIO1, ScenarioNames::SCENARIO2, ScenarioNames::SCENARIO3};
        std::map<ScenarioNames, double> perturb={
            {ScenarioNames::SCENARIO1, 1.0976270078546495},
            {ScenarioNames::SCENARIO2, 9.430378732744838},
            {ScenarioNames::SCENARIO3, 6.6027633760716435}
        };
        /// initial variable intervals for first stage variables
        std::vector<mc::Interval> first_stage_IX = {
            mc::Interval(10, 2000),       
            mc::Interval(0,16000),    
            mc::Interval(0,120),      
            mc::Interval(0,2000)  
        };
        /// initial variable intervals for second stage variables
        std::vector<mc::Interval> second_stage_IX = {
            mc::Interval(0, 5000),       
            mc::Interval(85,93),    
            mc::Interval(90,95),      
            mc::Interval(3,12), 
            mc::Interval(1.2,4),
            mc::Interval(145,162)
        };

        ScenarioNames scenario_name; //by default
        void generateMINLP(GRBModel* grbmodel);
        void generateLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x);
        void LFRR(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x,int var_index,bool max);
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
                default:
                    throw std::runtime_error("MC++ FFOp type not mapped to Gurobi NL opcode");
            }
        };
        /**
        * @brief tell cereal what data to save
        * @tparam Archive 
        * @param ar 
        */
        template<class Archive>
        void serialize(Archive& ar) {
        CEREAL_NVP(first_stage_IX), CEREAL_NVP(second_stage_IX);
        }

};
#endif // STMODEL_H