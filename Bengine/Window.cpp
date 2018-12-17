#include "Window.h"

#include "Errors.h"


namespace Bengine {

Window::Window() {
	// Empty
}


Window::~Window() {
	// Empty
}

int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags)
{
	Uint32 flags = SDL_WINDOW_OPENGL;

	if (currentFlags & INVISBLE) {
		flags |= SDL_WINDOW_HIDDEN;
	}

	if (currentFlags & FULLSCREEN) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	if (currentFlags & BORDERLESS) {
		flags |= SDL_WINDOW_BORDERLESS;
	}

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	//Open an SDL Window
	_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, flags);

	if (_sdlWindow == nullptr) {
		fatalError("SDL Window could not be created!");
	}

	//Set up openGL Context
	SDL_GLContext glContext = SDL_GL_CreateContext(_sdlWindow);
	if (glContext == nullptr) {
		fatalError("SDL GL context could not be created!");
	}

	//Set up glew
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		fatalError("Could not initialize glew!");
	}

	//CHeck the openGL Version
	std::printf("***    OpenGL Version: %s  ***\n", glGetString(GL_VERSION));

	// Setting default background color
	glClearColor(0.411f, 0.384f, 0.427f, 1.0f);

	// Setting VSYNC off (on is 1)
	SDL_GL_SetSwapInterval(0);

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

void Window::swapBuffer() {
	//Swap our buffer and draw everything to the screen
	SDL_GL_SwapWindow(_sdlWindow);
}


}