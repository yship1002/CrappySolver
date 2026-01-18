#include "CrappySolver.h"
CrappySolver::CrappySolver(STModel model,BranchingStrategy strategy) {
    // Constructor implementation (if needed)
    this->algo = Algo(model,strategy);
}
double CrappySolver::solve(double tolerance) {
    // Solve implementation (if needed)
    algo.solve(tolerance);
    return algo.best_solution;
}