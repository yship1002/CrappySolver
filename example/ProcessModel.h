#include "example/STModel.h"
class ProcessModel:public STModel {
    public:


        ProcessModel(BranchingStrategy branching_strategy);
        ProcessModel(const ProcessModel& other)=default;
        ProcessModel()=default; // default constructor
        /// A vector of ScenarioNames
        double probability;
        Ipopt::SmartPtr<STModel> clone(solveFullmodel flag)override;
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