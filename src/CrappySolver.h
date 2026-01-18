#ifndef CRAPPYSOLVER_H
#define CRAPPYSOLVER_H
#include "example/STModel.h"
#include "src/Algo.h"

class CrappySolver {
    public:
    CrappySolver(STModel model,BranchingStrategy strategy);
    Algo algo;
    double solve(double tolerance);

};
#endif // CRAPPYSOLVER_H