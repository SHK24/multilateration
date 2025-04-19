#ifndef ZHIL_SOLVER
#define ZHIL_SOLVER

#include <vector3d.h>
#include <basics.h>
#include <vector>

class ZhilSolver {
    public:
        static Vector3d locate_zhil(const std::vector<LocatorData>& locators);
};

#endif