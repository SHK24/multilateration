#ifndef SIMPLE_SOLVER
#define SIMPLE_SOLVER

#include <vector3d.h>
#include "basics.h"
#include <vector>


class SimpleSolver {
public:
    SimpleSolver(){}
    static Vector3d locate_simple(const std::vector<LocatorData>& locators);
};

#endif