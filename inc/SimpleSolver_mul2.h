#ifndef SIMPLE_SOLVERMUL2
#define SIMPLE_SOLVERMUL2

#include <vector3d.h>
#include "basics.h"
#include <vector>


class SimpleSolver_mul2 {
public:
    SimpleSolver_mul2(){}
    static Vector3d locate_simple(const std::vector<LocatorData>& locators);
};

#endif