#include "basics.h"

template<typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &container) {
    for (auto &el: container) {
        os << el << "; ";
    }
    return os;
}

std::ostream &operator<<(std::ostream &stream, const Statistics &stat) {
    const std::string separator = " ";
    stream << stat.min << separator << stat.avg << separator << stat.max;
    return stream;
}

Statistics CollectStatistics(const vector<double> &values) {
    if (values.empty()) {
        return {0, 0, 0};
    }
    return {
            *std::max_element(values.begin(), values.end()),
            *std::min_element(values.begin(), values.end()),
            std::reduce(values.begin(), values.end()) / static_cast<double>(values.size()),
    };
}

Cube diagonalCube(double low, double high) {
    return {
            {low, low, low},
            {high, high, high}
    };
}

std::ostream &operator<<(std::ostream &stream, const LocatorData &locator) {
    const std::string separator = " ";
    //TO FIX
    //stream << locator.position << separator << locator.distance;
    return stream;
}

double Interpolate(double left, double right, double portion) {
    return left + (right - left) * portion;
}

Vector3d Interpolate(Vector3d low, Vector3d high, Vector3d portion) {
    return {
            Interpolate(low.x(), high.x(), portion.x()),
            Interpolate(low.y(), high.y(), portion.y()),
            Interpolate(low.z(), high.z(), portion.z())
    };
}

vector<double> ComputeDistances(const vector<Vector3d> &observers, const Vector3d &target) {
    vector<double> distances;
    std::transform(observers.begin(), observers.end(), std::back_inserter(distances),
                    [target](const Vector3d &locator) {
                        return locator.distance(target);
                    });
    return distances;
}

vector<double> ComputeDistances(const Scene &scene) {
    return ComputeDistances(scene.observers, scene.target);
}

vector<LocatorData> CreateLocators(const vector<Vector3d> &observers, const vector<double> &distances) {
    vector<LocatorData> locators;
    std::transform(observers.begin(), observers.end(),
                    distances.begin(), std::back_inserter(locators),
                    [](const Vector3d &observer, double distance) {
                        return LocatorData{
                                observer,
                                distance
                        };
                    });
    return locators;
}

vector<LocatorData> CreateLocators(const Scene &scene) {
    const vector<double> distances = ComputeDistances(scene);
    return CreateLocators(scene.observers, distances);
}
