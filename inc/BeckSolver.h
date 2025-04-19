#ifndef BECK_SOLVER
#define BECK_SOLVER

#include <vector3d.h>
#include <basics.h>
#include <Eigen/Dense>
#include <vector>
#include <Eigen/Eigenvalues>

class BeckSolver {
public:
    explicit BeckSolver(const std::vector<LocatorData>& locators);

    [[nodiscard]] double FindLeftValue() const;
    [[nodiscard]] Eigen::Vector4d getZVec(double lambda) const;
    [[nodiscard]] double target(double lambda) const;
    [[nodiscard]] double bisection(double left) const;
    [[nodiscard]] Vector3d solve() const;

    static double target(const Eigen::Vector4d& vec);
    static Vector3d locate_beck(const std::vector<LocatorData>& locators);

private:
    Eigen::MatrixX4d position_mat;
    Eigen::VectorXd value_column;
    Eigen::MatrixX4d proj_mat;
    Eigen::Vector4d q_vec;
    Eigen::MatrixX4d position_square;
};

#endif