#include "Vector3D.h"
#include <Eigen/Dense>

bool is_surface(const Vector3d& position, double sigma) {
    return true; // Needs to be improved somehow
}

const Vector3d& choose_by_standard_deviation(const int n, const Eigen::MatrixX3d& N, const Eigen::Vector3d& X01, const Eigen::Vector3d& X02, const Eigen::VectorXd& R0, const Vector3d& X1, const Vector3d& X2, const double L01, const double L02) {
    Eigen::VectorXd R01(n), R02(n), S01(n), S02(n);
    double S1 = 0., S2 = 0.;

    for (int i = 0; i < n; ++i) {
        R01(i) = (N(i, 0) - X01(0)) * (N(i, 0) - X01(0)) + (N(i, 1) - X01(1)) * (N(i, 1) - X01(1)) + (N(i, 2) - X01(2)) * (N(i, 2) - X01(2));
        R02(i) = (N(i, 0) - X02(0)) * (N(i, 0) - X02(0)) + (N(i, 1) - X02(1)) * (N(i, 1) - X02(1)) + (N(i, 2) - X02(2)) * (N(i, 2) - X02(2));
        S01(i) = R01(i) / (R0(i) * R0(i)) - 1;
        S02(i) = R02(i) / (R0(i) * R0(i)) - 1;
        S1 += S01(i) * S01(i);
        S2 += S02(i) * S02(i);
    }

    return S1 > S2 ? X2 : X1;
}

double  minkowski4d(const Eigen::Vector4d& a, const Eigen::Vector4d& b) {
    return a(0) * b(0) + a(1) * b(1) + a(2) * b(2) - a(3) * b(3);
}

// std::ostream &operator<<(std::ostream &os, const Vector3d &vec) {
//     os << "(" << vec.x() << ", "
//               << vec.y() << ", "
//               << vec.z()
//        << ")";
//     return os;
// }

// Vector3d cross_prod(const Vector3d &v1, const Vector3d &v2) {
//     return {v1.y() * v2.z() - v1.z() * v2.y(),
//             v1.z() * v2.x() - v1.x() * v2.z(),
//             v1.x() * v2.y() - v1.y() * v2.x()};
// }

// Vector3d operator*(const double scalar, const Vector3d& vec) {
//     return vec * scalar;
// }
