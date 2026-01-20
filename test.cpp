#include "src/Algo.h"
#include "src/BBNode.h"
#include <example/STModel.h>

int main() {
    STModel model(BranchingStrategy::relwidth);
    Algo CZalgo(model, BranchingStrategy::relwidth);
    CZalgo.solve(0.001); // 1% tolerance
    return 0;   
}