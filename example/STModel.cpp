#include "example/STModel.h"

// Provide definitions for base-class virtuals and constructor so the
// vtable for STModel is emitted (fixes linker undefined vtable errors).

void STModel::generateMINLP(GRBModel* grbmodel){

}
void STModel::generateLP(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x) {

}

void STModel::LFRR(IloEnv* cplex_env,IloModel* cplexmodel,
                              IloRangeArray* cplex_constraints,
                              IloObjective* cplex_obj,
                              IloNumVarArray* cplex_x,int var_index,bool max){
    // Modify the objective to relax the variable at var_index
    if (max){
        cplexmodel->remove(*cplex_obj);
        IloExpr objExpr(*cplex_env);
        objExpr+=(*cplex_x)[var_index];
        *cplex_obj = IloMaximize(*cplex_env, objExpr);
        objExpr.end();
        cplexmodel->add(*cplex_obj);
    }else{
        cplexmodel->remove(*cplex_obj);
        IloExpr objExpr(*cplex_env);
        objExpr+=(*cplex_x)[var_index];
        *cplex_obj = IloMinimize(*cplex_env, objExpr);
        objExpr.end();
        cplexmodel->add(*cplex_obj);
    }
}
void STModel::dfs(GRBModel* grbmodel, int parent_idx,std::vector<int>& opcode,std::vector<double>& data,std::vector<int>& parent,mc::FFVar* var){
    // Implementation to be provided in derived classes
    if (var->opdef().first->varin.size()==0){
        if (var->opdef().first->varout[0]->id().first == mc::FFVar::CREAL || var->opdef().first->varout[0]->id().first == mc::FFVar::CINT) {
            opcode.push_back(GRB_OPCODE_CONSTANT);
            data.push_back(var->opdef().first->varout[0]->num().val());
            parent.push_back(parent_idx);
        }else if (var->opdef().first->varout[0]->id().first == mc::FFVar::VAR) {
            opcode.push_back(GRB_OPCODE_VARIABLE);
            data.push_back(grbmodel->getVarByName("x"+std::to_string(var->opdef().first->varout[0]->id().second)).index());
            parent.push_back(parent_idx);
        }else{
            throw std::runtime_error("Unexpected operation with zero inputs");
        }

    }else if (var->opdef().first->varin.size()==1){
        // opcode , data, parent
        int node_idx = opcode.size();
        if (var->opdef().first->type == mc::FFOp::SQR) {
            opcode.push_back(GRB_OPCODE_POW);
            data.push_back(-1.0);
            parent.push_back(parent_idx);
            opcode.push_back(GRB_OPCODE_CONSTANT);
            data.push_back(2.0);
            parent.push_back(parent.size()-1);
            dfs(grbmodel,parent.size()-2,opcode,data,parent,var->opdef().first->varin[0]);
        }else{
            opcode.push_back(map_ffop_to_grb(var->opdef().first->type));
            data.push_back(-1.0);
            parent.push_back(parent_idx);
            dfs(grbmodel,parent.size()-1,opcode,data,parent,var->opdef().first->varin[0]);
        }

    }else if (var->opdef().first->varin.size()==2){
        int node_idx = opcode.size();
        opcode.push_back(map_ffop_to_grb(var->opdef().first->type));
        data.push_back(-1.0);
        parent.push_back(parent_idx);
        int home_idx = opcode.size()-1;
        dfs(grbmodel,home_idx,opcode,data,parent,var->opdef().first->varin[0]); //left
        dfs(grbmodel,home_idx,opcode,data,parent,var->opdef().first->varin[1]); //right
    }
}
