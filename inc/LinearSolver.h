#ifndef LINEAR_SOLVER
#define LINEAR_SOLVER

#include <vector3d.h>
#include <basics.h>
#include <vector>

class LinearSolver {
public:
    static Vector3d locate_linear(const std::vector<LocatorData>& locators);
};

#endif

