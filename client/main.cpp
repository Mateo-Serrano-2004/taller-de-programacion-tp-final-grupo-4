#include "game/counter_strike_app.h"

#include <iostream>
#include <list>
#include <string>

int main() try {
	const std::list<std::string> images = {
		"../assets/gfx/pointer.bmp",
		"../assets/gfx/hud_arrow.bmp"
	};

	App::CounterStrikeApp cs_app(images);

	return 0;
} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
