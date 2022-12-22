#include "filesystem.h"
#include <iostream>

int main() {
	std::cout << FileSystem::getPathRelativeRoot("testpath") << std::endl;;

	return 0;
}