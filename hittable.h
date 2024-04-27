#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

// Contains information about a ray hitting an object.
class hit_record {
	public: 
		// Hit point p.
		point3 p;
		// Normal vector at hit point.
		vec3 normal;
		// Distance along ray where hit occurs.
		double t;
};

class hittable {
	public:
		virtual ~hittable() = default;

		// Function will be used in derived classes to determine if ray intersects with an object.
		virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif
