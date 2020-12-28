#include <SFML/Graphics.hpp>
#include <iostream>


const int W = 960;
const int H = 540;
const int max_iteration = 128;

double low_scale_x = -2.5, high_scale_x = 1;
double low_scale_y = -1, high_scale_y = 1;


int main() {

	sf::RenderWindow window(sf::VideoMode(W, H), "Mandlebrot Visualize");
	sf::Image image;

	image.create(W, H);
	sf::Texture texture;
	sf::Sprite sprite;


	while (window.isOpen()) {

		sf::Event e;
		while (window.pollEvent(e)) {

			if (e.type == sf::Event::Closed) window.close();

			if (e.type == sf::Event::MouseWheelMoved) {

				double x1 = low_scale_x + (high_scale_x - low_scale_x) * e.mouseWheel.x / W;
				double y1 = low_scale_y + (high_scale_y - low_scale_y) * e.mouseWheel.y / H;

				double z = (e.mouseWheel.delta >= 0) ? 5 : (1.0/5);
				double temp_low_x = x1 - (high_scale_x - low_scale_x) / 2 / z;
				high_scale_x = x1 + (high_scale_x - low_scale_x) / 2 / z;
				low_scale_x = temp_low_x;


				double temp_low_y = y1 - (high_scale_y - low_scale_y) / 2 / z;
				high_scale_y = y1 + (high_scale_y - low_scale_y) / 2 / z;
				low_scale_y = temp_low_y;

			}
		}

		for (int y = 0; y < H; ++y) {

			for (int x = 0; x < W; ++x) {

				double x0 = low_scale_x + (high_scale_x - low_scale_x) * x / W;
				double y0 = low_scale_y + (high_scale_y - low_scale_y) * y / H;

				double crx = 0, cry = 0;

				int iteration = 0;

				while (crx * crx + cry * cry <= 4 && iteration < max_iteration) {

					double xtemp = crx * crx - cry * cry + x0;
					cry = 2 * crx * cry + y0;
					crx = xtemp;
					iteration++;

				}
				//int r = 255-(255 * iteration / max_iteration*257456)%255;
				//int g = 255 - (255 * iteration / max_iteration * 15375) % 255;
				//int b = 255 - (255 * iteration / max_iteration * 9343) % 255;
				int r = 255 - (255 * iteration / max_iteration * 7673) % 255;
				int g = 255 - (255 * iteration / max_iteration * 6353) % 255;
				int b = 255 - (255 * iteration / max_iteration * 5851) % 255;
				image.setPixel(x, y, sf::Color(b,g,r));

			}

		}

		texture.loadFromImage(image);
		sprite.setTexture(texture);
		window.draw(sprite);
		window.display();


	}
	return 1;

}