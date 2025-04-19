#include "BeckSolver.h"

BeckSolver::BeckSolver(const std::vector<LocatorData>& locators)
    : position_mat(locators.size(), 4),
        value_column(locators.size()),
        proj_mat(4, 4),
        q_vec(4),
        position_square(4, 4) 
{
    const int n = static_cast<int>(locators.size());
    for (int i = 0; i < n; ++i) {
        position_mat.row(i) << 2 * locators[i].position.x(),
                                2 * locators[i].position.y(),
                                2 * locators[i].position.z(),
                                -1;
    }

    position_square = position_mat.transpose() * position_mat;

    for (int i = 0; i < n; ++i) {
        value_column(i) = locators[i].position.dot_square() - locators[i].distance * locators[i].distance;
    }

    proj_mat.setZero();
    proj_mat.topLeftCorner(3, 3) = Eigen::MatrixXd::Identity(3, 3);

    q_vec << 0, 0, 0, -1./2.;
}

double BeckSolver::FindLeftValue() const {
    Eigen::GeneralizedEigenSolver<Eigen::MatrixXd> ges(proj_mat, position_square);
    const double max_eigen = ges.eigenvalues().transpose().real().maxCoeff();
    return -1. / max_eigen;
}

Eigen::Vector4d BeckSolver::getZVec(double lambda) const {
    Eigen::MatrixXd trans = position_mat.transpose();
    Eigen::MatrixXd mat = position_square + lambda * proj_mat;
    Eigen::MatrixXd inv = mat.inverse();
    Eigen::Vector4d vec = trans * value_column - lambda * q_vec;
    return inv * vec;
}

double BeckSolver::target(const Eigen::Vector4d& vec) {
    return vec(0) * vec(0) + vec(1) * vec(1) + vec(2) * vec(2) - vec(3);
}

double BeckSolver::target(double lambda) const {
    auto z_vec = getZVec(lambda);
    return target(z_vec);
}

double BeckSolver::bisection(double left) const {
    double length = 1;
    while (target(left + length) > 0) {
        length *= 2;
    }
    double right = left + length;
    while (right - left > 1e-11) {
        const double mid = left + (right - left) / 2;
        if (mid <= left || mid >= right) {
            break;
        }
        if (target(mid) > 0) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return left + (right - left) / 2;
}

Vector3d BeckSolver::solve() const {
    const double left = FindLeftValue();
    const double lambda = bisection(left);
    const auto z_vec = getZVec(lambda);
    return { z_vec(0), z_vec(1), z_vec(2) };
}

Vector3d BeckSolver::locate_beck(const std::vector<LocatorData>& locators) {
    BeckSolver beck_solver(locators);
    return beck_solver.solve();
}


