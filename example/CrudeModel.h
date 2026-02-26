#include "example/STModel.h"
class CrudeModel:public STModel {
    public:


        CrudeModel(BranchingStrategy branching_strategy);
        CrudeModel(const CrudeModel& other)=default;
        CrudeModel()=default; // default constructor
        /// A vector of ScenarioNames
        double probability;

        Ipopt::SmartPtr<STModel> clone(solveFullmodel flag) override;
        void buildDAG() override;
        void buildFullModelDAG() override;

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