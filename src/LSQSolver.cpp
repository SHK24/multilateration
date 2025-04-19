#include <vector3d.h>
#include <basics.h>

#include <Eigen/Dense>

#include <vector>
#include "../inc/LSQSolver.h"



Vector3d LSQSolver::locate_LSQ(const std::vector<LocatorData>& locators)
{
    const int n = static_cast<int>(locators.size());
    Eigen::MatrixX3d position_mat(n, 3);

    for (int i = 0; i < n; ++i) {
        position_mat.row(i) << locators[i].position.x(), locators[i].position.y(), locators[i].position.z();
    }
    position_mat *= 2;

    Eigen::VectorXd value_column(n);
    for (int i = 0; i < n; ++i)
    {
        value_column(i) = locators[i].position.dot_square() - locators[i].distance * locators[i].distance;
    }

    Eigen::MatrixXd processing_mat(n, n);
    processing_mat.setZero();
    processing_mat.topLeftCorner(n, 1) = Eigen::MatrixXd::Constant(n, 1, -1);
    processing_mat.topRightCorner(n, n) = Eigen::MatrixXd::Identity(n, n);

    Eigen::MatrixXd answer_position_mat = processing_mat * position_mat;
    Eigen::MatrixXd answer_position_mat_t = answer_position_mat.transpose();
    Eigen::VectorXd answer_value_column = processing_mat * value_column;
    Eigen::VectorXd result = (answer_position_mat_t * answer_position_mat).ldlt()
            .solve(answer_position_mat_t * answer_value_column);

    return { result(0), result(1), result(2) };
}
