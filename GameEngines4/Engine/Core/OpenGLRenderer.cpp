#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer() : Renderer()
{
}

OpenGLRenderer::~OpenGLRenderer()
{
	OnDestroy();
}

SDL_Window* OpenGLRenderer::CreateWindow(std::string windowName_, int width_, int height_)
{
	SetPreAttributes();

	window = SDL_CreateWindow(windowName_.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width_, height_, SDL_WINDOW_OPENGL);

	if (!window)
	{
		Debugger::Error("Failed to create window ", "Window.cpp ", __LINE__);
		return nullptr;
	}

	context = SDL_GL_CreateContext(window);

	SetPostAttributes();

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		Debugger::FatalError("Failied to initialize glew ", "Window.cpp ", __LINE__);
		return nullptr;
	}

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width_, height_);


	return window;
}

void OpenGLRenderer::OnDestroy() 
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

void OpenGLRenderer::SetPreAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
}

void OpenGLRenderer::SetPostAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
