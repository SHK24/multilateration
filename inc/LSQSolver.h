#ifndef LSQ_SOLVER
#define LSQ_SOLVER

//#include <vector3d.h>
#include "basics.h"
#include <vector>


class LSQSolver {
public:
    LSQSolver(){}
    static Vector3d locate_LSQ(const std::vector<LocatorData>& locators);
};

#endif