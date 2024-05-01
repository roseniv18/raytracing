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
		// Is the ray inside or outside the sphere? (front face = outside)
		bool front_face;

		/* 
			Sets normal to be opposite of ray direction.
		*/
		void set_face_normal(const ray& r, const vec3& outward_normal) {
			// Sets the hit record normal vector.
        	// NOTE: the parameter `outward_normal` is assumed to have unit length.

			front_face = dot(r.direction(), outward_normal) < 0;
			normal = front_face ? outward_normal : -outward_normal;
		}
};

class hittable {
	public:
		virtual ~hittable() = default;

		// Function will be used in derived classes to determine if ray intersects with an object.
		virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif
