#include <iostream>
#include <cstdlib>
#include "vec3.h"
#include "color.h"

int main() {
	// IMAGE

	int image_width = 256;
	int image_height = 256;

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
			auto r = double(x) / (image_width - 1);
			auto g = double(y) / (image_height - 1);
			auto b = 0.0;

			auto pixel_color = color(r, g, b);
			write_color(std::cout, pixel_color);
		}
	}

	std::clog << "\rDone.                 \n";

	return 0;
}
