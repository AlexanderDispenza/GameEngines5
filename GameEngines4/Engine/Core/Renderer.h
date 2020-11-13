#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <string>


class Renderer
{
public:

	Renderer() {}
	virtual ~Renderer() {}

	virtual SDL_Window* CreateWindow(std::string windowName_, int width_, int height_) = 0;

	virtual void OnDestroy() = 0;
};

enum class RenderType
{
	OPENGL,
	VULKAN
};

#endif
