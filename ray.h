#ifndef RAY_H
#define RAY_H

#include "vec3.h"

/*
	Define a ray class. Here, the ray is described by the formula:
	P(t) = A + tb
	Where P(t) is a 3D position along a line, A is the ray origin, b is the ray direction.
	t is a scalar and controls the position of the ray.
*/

class ray {
	public:
		// CONSTRUCTORS

		ray() {}
		ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

		// MEMBER FUNCTIONS

		const point3& origin() const { return orig; }
		const vec3& direction() const { return dir; }

		point3 at(double t) const {
			return orig + t*dir;
		}

	private:
		point3 orig;
		vec3 dir;
};

#endif
