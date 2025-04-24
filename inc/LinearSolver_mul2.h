#ifndef LINEAR_SOLVERMUL2
#define LINEAR_SOLVERMUL2

#include <vector3d.h>
#include <basics.h>
#include <vector>

class LinearSolver_mul2 {
public:
    static Vector3d locate_linear(const std::vector<LocatorData>& locators);
};

#endif

