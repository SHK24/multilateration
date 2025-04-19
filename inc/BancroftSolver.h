#ifndef BANCROFT_SOLVER
#define BANCROFT_SOLVER

#include <Eigen/Dense>
#include <vector>
#include "basics.h"
#include "common.h"

class BancroftSolver {

    public:
        static Vector3d locate_bancroft(const std::vector<LocatorData>& locators);
};

#endif