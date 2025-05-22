#include "game/counter_strike_app.h"

int main() try {
	App::CounterStrikeApp cs_app;

	return 0;
} catch (std::exception& e) {
	std::cerr << e.what() << std::endl;
	return 1;
}
