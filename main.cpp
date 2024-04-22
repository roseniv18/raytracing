#include <iostream>
#include <cstdlib>
#include "vec3.h"
#include "color.h"
#include "ray.h"

color ray_color(const ray& r) {
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
	auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
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
