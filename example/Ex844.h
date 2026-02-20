#include "example/STModel.h"
class Ex844Model:public STModel {
    public:


        Ex844Model(BranchingStrategy branching_strategy);
        Ex844Model(const Ex844Model& other)=default;
        Ex844Model()=default; // default constructor
        /// A vector of ScenarioNames

        Ipopt::SmartPtr<STModel> clone() override;
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