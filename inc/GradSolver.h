#ifndef GRAD_SOLVER
#define GRAD_SOLVER

//#include "Vector3D.h"
#include "basics.h"
#include <vector>

//#include "PseudorangeMultilateration.h"
//#include <solvers/locate_simple.h>
//#include <Eigen/Dense>

class GradSolver {
public:

    Vector3d locate_grad(const std::vector<LocatorData>& locators);

    Vector3d locate_grad_slow(const std::vector<LocatorData>& locators);
}


#endif
