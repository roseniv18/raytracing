#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
  public:
    double coords[3];

    vec3() : coords{0,0,0} {}
    vec3(double x, double y, double z) : coords{x, y, z} {}

    double x() const { return coords[0]; }
    double y() const { return coords[1]; }
    double z() const { return coords[2]; }

    vec3 operator-() const { return vec3(-coords[0], -coords[1], -coords[2]); }
    double operator[](int i) const { return coords[i]; }
    double& operator[](int i) { return coords[i]; }

    vec3& operator+=(const vec3& v) {
        coords[0] += v.coords[0];
        coords[1] += v.coords[1];
        coords[2] += v.coords[2];
        return *this;
    }

    vec3& operator*=(double t) {
        coords[0] *= t;
        coords[1] *= t;
        coords[2] *= t;
        return *this;
    }

    vec3& operator/=(double t) {
        return *this *= 1/t;
    }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return coords[0]*coords[0] + coords[1]*coords[1] + coords[2]*coords[2];
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.coords[0] << ' ' << v.coords[1] << ' ' << v.coords[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.coords[0] + v.coords[0], u.coords[1] + v.coords[1], u.coords[2] + v.coords[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.coords[0] - v.coords[0], u.coords[1] - v.coords[1], u.coords[2] - v.coords[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.coords[0] * v.coords[0], u.coords[1] * v.coords[1], u.coords[2] * v.coords[2]);
}

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.coords[0], t*v.coords[1], t*v.coords[2]);
}

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.coords[0] * v.coords[0]
         + u.coords[1] * v.coords[1]
         + u.coords[2] * v.coords[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.coords[1] * v.coords[2] - u.coords[2] * v.coords[1],
                u.coords[2] * v.coords[0] - u.coords[0] * v.coords[2],
                u.coords[0] * v.coords[1] - u.coords[1] * v.coords[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif
