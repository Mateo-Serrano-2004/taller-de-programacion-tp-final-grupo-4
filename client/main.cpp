#include "client.h"

int main(int argc, char* argv[]) try {
	char* hostname = argv[1];
	char* port = argv[2];

	std::string join;

	if (argc == 4) join = ".";

	Client client(hostname, port, join);

	return 0;
} catch (std::exception& e) {
	std::cerr << e.what() << std::endl;
	return 1;
}
