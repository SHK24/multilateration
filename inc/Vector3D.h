#ifndef VECTOR3D_H
#define VECTOR3D_H


#include <cmath>
#include <iostream>

class Vector3d {
public:
    double x_[3];

    Vector3d();
    Vector3d(double x, double y, double z);
    explicit Vector3d(const double *const x);
    explicit Vector3d(const float *const x);
    Vector3d(const Vector3d &) = default;
    Vector3d &operator=(const Vector3d &) = default;

    [[nodiscard]] constexpr double x() const;
    [[nodiscard]] constexpr double y() const;
    [[nodiscard]] constexpr double z() const;
    constexpr double operator[](size_t i) const;

    [[nodiscard]] double dot_square() const;
    [[nodiscard]] double modulus() const;

    Vector3d operator*(double scalar) const;
    Vector3d operator+(const Vector3d& vec) const;
    Vector3d operator-() const;
    Vector3d operator-(const Vector3d& vec) const;
    Vector3d operator/(double scalar) const;

    Vector3d &operator*=(double scalar);
    Vector3d &operator/=(double scalar);
    Vector3d &operator+=(const Vector3d &vec);
    Vector3d &operator-=(const Vector3d &vec);

    [[nodiscard]] double distance(const Vector3d& vec) const;
    Vector3d &normalize();
    Vector3d &rotate(const Vector3d &v, double alpha);
    [[nodiscard]] Vector3d rotate_x(double alpha) const;
    [[nodiscard]] Vector3d rotate_y(double alpha) const;
    [[nodiscard]] Vector3d rotate_z(double alpha) const;
    Vector3d &rotate_x(double alpha);
    Vector3d &rotate_y(double alpha);
    Vector3d &rotate_z(double alpha);
};

std::ostream &operator<<(std::ostream &os, const Vector3d &vec);
Vector3d cross_prod(const Vector3d &v1, const Vector3d &v2);
Vector3d operator*(const double scalar, const Vector3d& vec);

#endif

