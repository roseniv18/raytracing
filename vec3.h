#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
  public:
    double coords[3];

	// CONSTRUCTORS
	
	// Default constructor.
    vec3() : coords{0,0,0} {}
	// Constructor for specific coordinates.
    vec3(double x, double y, double z) : coords{x, y, z} {}

	// MEMBER FUNCTIONS

    double x() const { return coords[0]; }
    double y() const { return coords[1]; }
    double z() const { return coords[2]; }

    double length() const {
        return sqrt(length_squared());
    }

    double length_squared() const {
        return coords[0]*coords[0] + coords[1]*coords[1] + coords[2]*coords[2];
    }

	// OPERATOR OVERLOADING

	// Operators for vector subtraction, accessing vector components, etc.
    vec3 operator-() const { return vec3(-coords[0], -coords[1], -coords[2]); }
    double operator[](int i) const { return coords[i]; }
    double& operator[](int i) { return coords[i]; }

    vec3& operator+=(const vec3& v) {
        coords[0] += v.coords[0];
        coords[1] += v.coords[1];
        coords[2] += v.coords[2];
        return *this;
    }
	
    vec3& operator*=(double scalar) {
        coords[0] *= scalar;
        coords[1] *= scalar;
        coords[2] *= scalar;
        return *this;
    }

    vec3& operator/=(double scalar) {
        return *this *= 1/scalar;
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// VECTOR UTILITY FUNCTIONS

// Overload output stream operator, so that it can print out vector coordinates.
inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.coords[0] << ' ' << v.coords[1] << ' ' << v.coords[2];
}

// Vector addition.
inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.coords[0] + v.coords[0], u.coords[1] + v.coords[1], u.coords[2] + v.coords[2]);
}

// Vector subtraction.
inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.coords[0] - v.coords[0], u.coords[1] - v.coords[1], u.coords[2] - v.coords[2]);
}

// Component-wise multiplication.
inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.coords[0] * v.coords[0], u.coords[1] * v.coords[1], u.coords[2] * v.coords[2]);
}

// Scalar-vector product.
inline vec3 operator*(double scalar, const vec3& v) {
    return vec3(scalar*v.coords[0], scalar*v.coords[1], scalar*v.coords[2]);
}

// Vector-scalar product.
inline vec3 operator*(const vec3& v, double scalar) {
    return scalar * v;
}

// Scalar division.
inline vec3 operator/(const vec3& v, double scalar) {
    return (1/scalar) * v;
}

// Dot product.
inline double dot(const vec3& u, const vec3& v) {
    return u.coords[0] * v.coords[0]
         + u.coords[1] * v.coords[1]
         + u.coords[2] * v.coords[2];
}

// Cross product.
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.coords[1] * v.coords[2] - u.coords[2] * v.coords[1],
                u.coords[2] * v.coords[0] - u.coords[0] * v.coords[2],
                u.coords[0] * v.coords[1] - u.coords[1] * v.coords[0]);
}

// Unit vector.
inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}

#endif
