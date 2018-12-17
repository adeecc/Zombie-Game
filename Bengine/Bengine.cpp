#include "Bengine.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

namespace Bengine {

int Bengine::init() {
	//Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	// Tell SDL we want a double buffered windows so we dont get flickering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return 0;
}

}