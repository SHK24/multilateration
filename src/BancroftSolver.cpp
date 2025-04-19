#include "../inc/BancroftSolver.h"


Vector3d  BancroftSolver::locate_bancroft(const std::vector<LocatorData>& locators) {
    const int n = static_cast<int>(locators.size());
    Eigen::Matrix4Xd A_transpose(4, n);
    Eigen::VectorXd r(n), i0(n);

    for (int i = 0; i < n; ++i) {
        A_transpose.col(i) << locators[i].position.x(), locators[i].position.y(), locators[i].position.z(), locators[i].distance;
        r(i) = minkowski4d(A_transpose.col(i), A_transpose.col(i)) / 2;
        i0(i) = 1.;
    }

    const Eigen::MatrixX4d A = A_transpose.transpose();
    const Eigen::Matrix4Xd B = (A_transpose * A_transpose.transpose()).inverse() * A_transpose;
    const Eigen::Vector4d u = B * i0;
    const Eigen::Vector4d v = B * r;
    const double E = minkowski4d(u, u);
    const double F = minkowski4d(u, v) - 1;
    const double G = minkowski4d(v, v);
    double D4 = F * F - E * G;

    if (D4 < 0.)
        D4 = 0.;

    const double lambda01 = (-F - std::sqrt(D4)) / E;
    const Eigen::Vector4d X01 = lambda01 * u + v;
    const Vector3d X1(X01(0), X01(1), X01(2));
    const double lambda02 = (-F + std::sqrt(D4)) / E;
    const Eigen::Vector4d X02 = lambda02 * u + v;
    const Vector3d X2(X02(0), X02(1), X02(2));

    if (!is_surface(X1, 0.)) {
        if (is_surface(X2, 0.))
            return X2;

        return Vector3d(); // Incorrect input data
    }

    if (!is_surface(X2, 0.))
        return X1;

    return choose_by_standard_deviation(n, A.leftCols<3>(), X01.head<3>(), X02.head<3>(), A.rightCols<1>(), X1, X2, lambda01, lambda02);
}


