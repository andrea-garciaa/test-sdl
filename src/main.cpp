#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO); // init SDL2

	SDL_Window* window = SDL_CreateWindow("SDL2/OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_GLContext glc = SDL_GL_CreateContext(window);

	glMatrixMode(GL_PROJECTION | GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-320, 320, 240, -240, 0, 1);

	SDL_Event e;
	ZeroMemory(&e, sizeof(e));
	float x = 0.0, y = 30.0;

	while (e.type != SDL_KEYDOWN && e.type != SDL_QUIT) {
		SDL_PollEvent(&e);
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glRotatef(10.0, 0.0, 0.0, 1.0);

		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0); glVertex2f(x, y + 90.0);
		glColor3f(0.0, 1.0, 0.0); glVertex2f(x + 90.0, y - 90.0);
		glColor3f(0.0, 0.0, 1.0); glVertex2f(x - 90.0, y - 90.0);
		glEnd();

		SDL_GL_SwapWindow(window);
	}

	return 0;
}