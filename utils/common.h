#ifndef COMMON_H
#define COMMON_H

bool is_surface(const Vector3d& position, double sigma);

const Vector3d& choose_by_standard_deviation(const int n, const Eigen::MatrixX3d& N, const Eigen::Vector3d& X01, const Eigen::Vector3d& X02, const Eigen::VectorXd& R0, const Vector3d& X1, const Vector3d& X2, const double L01, const double L02);

double  minkowski4d(const Eigen::Vector4d& a, const Eigen::Vector4d& b);

#endif