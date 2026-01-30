#include "example/STModel.h"
class CrudeModel:public STModel{
    public:

        CrudeModel(BranchingStrategy branching_strategy);
        CrudeModel(const CrudeModel& other)=default;
        CrudeModel()=default; // default constructor
        BranchingStrategy branching_strategy;
        std::map<std::string, int> first_stage_map;
        std::map<std::string, int> second_stage_map;
        /// A vector of ScenarioNames
        void generateMINLP(GRBModel* grbmodel) override;
        void generateLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) override;
        std::vector<double> scenario_1_params;
        std::vector<double> scenario_2_params;
        std::vector<double> scenario_3_params;
        std::vector<double> scenario_4_params;
        std::vector<double> scenario_5_params;

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