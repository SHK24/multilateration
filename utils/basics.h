#ifndef BASICS_H
#define BASICS_H

#include <Vector3D.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using std::vector;

struct Statistics {
    double max;
    double min;
    double avg;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &container);

std::ostream &operator<<(std::ostream &stream, const Statistics &stat);

struct NamedStatistics {
    Statistics stat;
    std::string name;
};

struct StatisticsPoint {
    double deviation = 0;
    vector<NamedStatistics> stats;
};

Statistics CollectStatistics(const vector<double> &values);

struct Cube {
    Vector3d low;
    Vector3d high;
};

Cube diagonalCube(double low, double high);

struct Scene {
    vector<Vector3d> observers;
    Vector3d target;
};

struct LocatorData {
    Vector3d position;
    double distance = 0;
};

std::ostream &operator<<(std::ostream &stream, const LocatorData &locator);

struct Scenario {
    vector<LocatorData> locators;
    Vector3d latent;
};

struct NoisySelection {
    vector<Scenario> scenarios;
    double deviation;
};

double Interpolate(double left, double right, double portion);

Vector3d Interpolate(Vector3d low, Vector3d high, Vector3d portion);

vector<double> ComputeDistances(const vector<Vector3d> &observers, const Vector3d &target);

vector<double> ComputeDistances(const Scene &scene);

vector<LocatorData> CreateLocators(const vector<Vector3d> &observers, const vector<double> &distances);

vector<LocatorData> CreateLocators(const Scene &scene);

#endif // BASICS_H
