#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "Renderer.h"
#include "../Core/Debugger.h"

class OpenGLRenderer : public Renderer
{
public:

	OpenGLRenderer();
	virtual ~OpenGLRenderer();

	 SDL_Window* CreateWindow(std::string windowName_, int width_, int height_) override;

	  void OnDestroy() override;

private:

	void SetPreAttributes();
	void SetPostAttributes();
	int width;
	int height;

	SDL_Window* window;
	SDL_GLContext context;
};

#endif

