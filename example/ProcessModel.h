#include "example/STModel.h"
class ProcessModel:public STModel{
    public:

        ProcessModel(BranchingStrategy branching_strategy);
        ProcessModel(const ProcessModel& other)=default;
        ProcessModel()=default; // default constructor
        /// A vector of ScenarioNames
        void convertToCentralizedModel();
        void generateMINLP(GRBModel* grbmodel) override;
        void generateLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) override;
        void generateFullLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) override;
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