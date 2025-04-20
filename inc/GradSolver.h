#ifndef GRAD_SOLVER
#define GRAD_SOLVER

#include <vector3d.h>
#include <basics.h>
#include <vector>
#include "SimpleSolver.h"

class GradSolver {

public:
    static Vector3d calculate_delta(const Vector3d& target, const std::vector<LocatorData>& locators, double step);
    static Vector3d locate_grad(const std::vector<LocatorData>& locators);
    static Vector3d locate_grad_slow(const std::vector<LocatorData>& locators);
};


#endif
