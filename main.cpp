#include <iostream>
#include "config.h"

int main(int argc, char **argv) {
	std::cout << "Hello World" << std::endl;
	std::cout << "Version " << Ticking_VERSION_MAJOR << "." << Ticking_VERSION_MINOR << std::endl;
	return 0;
}
