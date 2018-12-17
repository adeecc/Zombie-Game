#include "Errors.h"

#include <cstdlib>

#include <iostream>
#include <SDL/SDL.h>

namespace Bengine {

void fatalError(std::string errorString) {
	std::cout << errorString << std::endl;
	SDL_Quit();

	std::cout << "Enter any key to quit...\n";
	std::cin.get();
	exit(69);
}
}