#include "GradSolver.h"


 Vector3d GradSolver::calculate_delta(const Vector3d& target, const std::vector<LocatorData>& locators, double step) {
    Vector3d delta;
    for (const auto& locator : locators) {
        const double dist = target.distance(locator.position);
        const double err = dist - locator.distance;
        const double max_dist = std::max(locator.distance, dist);
        const double scale = step * err / max_dist;
        const Vector3d loc_dir = locator.position - target;
        Vector3d diff = loc_dir * scale;
        delta = delta + diff;
    }
    delta = delta * (1.0 / static_cast<double>(locators.size()));
    return delta;
}

Vector3d GradSolver::locate_grad(const std::vector<LocatorData>& locators) {
    constexpr int iter_count = 2000;
    constexpr double first_step = 3;
    constexpr double step_scale = 0.99;

    SimpleSolver tempSimpleSolver;

    Vector3d target = tempSimpleSolver.locate_simple(locators);
    double step = first_step;
    for (int iter = 0; iter < iter_count; ++iter) {
        Vector3d delta = calculate_delta(target, locators, step);
        step *= step_scale;
        target = target + delta;
    }
    return target;
}

Vector3d GradSolver::locate_grad_slow(const std::vector<LocatorData>& locators) {
    constexpr int iter_count = 200000;
    constexpr double first_step = 3;
    constexpr double step_scale = 0.9999;

    Vector3d target;
    double step = first_step;
    for (int iter = 0; iter < iter_count; ++iter) {
        Vector3d delta = calculate_delta(target, locators, step);
        step *= step_scale;
        target = target + delta;
    }
    return target;
}

