#ifndef RTKLib_SOLVER
#define RTKLib_SOLVER

#include <Eigen/Dense>
#include <lapacke.h>
#include "basics.h"
#include "common.h"

class RtkLibSolver {

    public:
        //void test();
        static Vector3d locate_rtk_lsq(const std::vector<LocatorData>& locators);
};

#endif