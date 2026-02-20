#include "example/STModel.h"
class ProcessModel:public STModel {
    public:


        ProcessModel(BranchingStrategy branching_strategy);
        ProcessModel(const ProcessModel& other)=default;
        ProcessModel()=default; // default constructor
        /// A vector of ScenarioNames

        Ipopt::SmartPtr<STModel> clone() override;
        void buildDAG() override;
        void clearDAG() override;
        void buildFullModelDAG() override;
        void convertToCentralizedModel() override;
        void generateMINLP(GRBModel* grbmodel) override;
        void generateLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) override;
        // this is to solve centralzied model
        void generateFullLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) override;


        bool get_nlp_info(
            Ipopt::Index& n,
            Ipopt::Index& m,
            Ipopt::Index& nnz_jac_g,
            Ipopt::Index& nnz_h_lag,
            Ipopt::TNLP::IndexStyleEnum& index_style
        ) override;
        bool get_bounds_info(
            Ipopt::Index   n,
            Ipopt::Number* x_l,
            Ipopt::Number* x_u,
            Ipopt::Index   m,
            Ipopt::Number* g_l,
            Ipopt::Number* g_u
        ) override;
        bool get_starting_point(
            Ipopt::Index   n,
            bool    init_x,
            Ipopt::Number* x,
            bool    init_z,
            Ipopt::Number* z_L,
            Ipopt::Number* z_U,
            Ipopt::Index   m,
            bool    init_lambda,
            Ipopt::Number* lambda
        ) override;
        bool eval_f(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Number&       obj_value
        ) override;
        bool eval_grad_f(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Number*       grad_f
        ) override;
        bool eval_g(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Index         m,
            Ipopt::Number*       g
        ) override;
        bool eval_jac_g(
            Ipopt::Index         n,
            const Ipopt::Number* x,
            bool          new_x,
            Ipopt::Index         m,
            Ipopt::Index         nele_jac,
            Ipopt::Index*        iRow,
            Ipopt::Index*        jCol,
            Ipopt::Number*       values
        ) override;
        void finalize_solution(
            Ipopt::SolverReturn               status,
            Ipopt::Index                      n,
            const Ipopt::Number*              x,
            const Ipopt::Number*              z_L,
            const Ipopt::Number*              z_U,
            Ipopt::Index                      m,
            const Ipopt::Number*              g,
            const Ipopt::Number*              lambda,
            Ipopt::Number                     obj_value,
            const Ipopt::IpoptData*           ip_data,
            Ipopt::IpoptCalculatedQuantities* ip_cq
        ) override;
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