#include <iostream>
#include <cstdlib>
#include "vec3.h"
#include "color.h"
#include "ray.h"

/*
	The equation of a sphere of radius r, centered at the origin is x^2 + y^2 + z^2 = r^2
	Depending on the value of the left-hand side of the equation (<0, =0, >0), a point is either
	inside the sphere; on the surface of the sphere; outside the sphere respectively.
	For a sphere with an arbitrary center (point C_x, C_y, C_z):
	(C_x - x)^2 + (C_y - y)^2 + (C_z - z)^2 = r^2
	We note that the vector from point P(x,y,z) to center C(C_x, C_y, C_z) is (C-P)
	Using the fact that the dot product (C-P).(C-P) = (C_x - x)^2 + (C_y - y)^2 + (C_z - z)^2 = r^2
	We want to know if the ray P(t) = Q + td ever hits the sphere. We replace P(t) with Q + td in the
	above equation. Using the rules of vector algebra to distribute the dot product we get:
	t^2d.d - 2td.(C-Q) + (C-Q).(C-Q) - r^2 = 0
	This is a quadratic equation. 
	If discriminant < 0, there are no real solutions, 
	discriminant = 0 means one real solution,
	discriminant > 0 means two real solutions.

*/
double hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 oc = center - r.origin();
	auto a = dot(r.direction(), r.direction());
	auto b = -2.0 * dot(r.direction(), oc);
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = b * b - 4 * a * c;

	if(discriminant < 0) {
		return -1.0;
	}

	else {
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}

color ray_color(const ray& r) {
	auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
	if(t > 0.0) {
		vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1));
		return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
	// IMAGE

	auto aspect_ratio = 16.0 / 9.0;
	int image_width = 400;

	// Calculate the image height and make sure it's at least 1.
	int image_height = int(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	// CAMERA

	auto focal_length = 1.0;
	auto viewport_height = 2.0;
	auto viewport_width = viewport_height * (double(image_width) / image_height);
	auto camera_center = point3(0, 0, 0);

	// Calculate vectors across horizontal and down the vertical viewport edges.
	auto viewport_u = vec3(viewport_width, 0, 0);
	auto viewport_v = vec3(0, -viewport_height, 0);

	// Calculate horizontal and vertical delta vectors from pixel to pixel.
	auto pixel_delta_u = viewport_u / image_width;
	auto pixel_delta_v = viewport_v / image_height;

	// Calculate location of upper left pixel.
	/* 
		First, we need to find point Q - the upper left point of the viewport.
		We subtract the (0,0,focal_length) vector from the camera (Not really necessary when camera is at 0,0,0).
		The resulting vector points to the center of the viewport.
		Then, we subtract the resulting vector with (u_half + v_half). The resulting vector points to Q.
	 */
	auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	/* 
		Next we find the first pixel location. The pixel grid is inset from the viewport edges by half
		of the pixel-to-pixel distance. This way, the viewport is evenly divided into width x height 
		identical regions.
	*/
	auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

	// RENDER

	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	/*
		We are generating a ppm image. PPM (Portable Pixel Map) is a simple way to create and display
		colored images. Each pixel has a corresponding rgb color.
		Below we are generating the pixel grid, top to bottom (first loop), left to right (second loop).
	*/
	for(int y = 0; y < image_height; y++) {
		/* 
			Show progress bar.
			std::flush ensures the output buffer is flushed, that is, ensures that 
			the progress text is shown immediately and updated in real-time.
		*/
		std::clog << "\rScanlines remaining: " << (image_height - y) << ' ' << std::flush;
		for(int x = 0; x < image_width; x++) {
			auto pixel_center = pixel00_loc + (x * pixel_delta_u) + (y * pixel_delta_v);
			auto ray_direction = pixel_center - camera_center;
			ray r(camera_center, ray_direction);

			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}

	std::clog << "\rDone.                 \n";

	return 0;
}
