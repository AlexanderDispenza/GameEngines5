#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* MouseEventListener::engineInstance = nullptr;
glm::vec2 MouseEventListener::mouse = glm::vec2();
glm::vec2 MouseEventListener::prevMouse = glm::vec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener()
{
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(CoreEngine* engine_)
{
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event event_)
{
	if (event_.type == SDL_MOUSEBUTTONDOWN)
	{
		UpdateMousePosition();
		NotifyOfMousePressed(event_.button.button);
	}
	else if (event_.type == SDL_MOUSEBUTTONUP)
	{
		UpdateMousePosition();
		NotifyOfMouseReleased(event_.button.button);
	}
	else if (event_.type == SDL_MOUSEMOTION)
	{
		UpdateMousePosition();
		NotifyOfMouseMove();
	}
	else if (event_.type == SDL_MOUSEWHEEL)
	{
		NotifyOfMouseScroll(event_.wheel.y);
	}
}

void MouseEventListener::NotifyOfMousePressed(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseMove(mouse);
	}
}

void MouseEventListener::NotifyOfMouseReleased(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseReleased(mouse, buttonType_);
	}
}

void MouseEventListener::NotifyOfMouseMove()
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseMove(mouse);
	}
}

void MouseEventListener::NotifyOfMouseScroll(int y_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseScroll(y_);
	}
}

glm::vec2 MouseEventListener::GetPreviousMousePosition()
{
	return prevMouse;
}

glm::vec2 MouseEventListener::GetMousePosition()
{
	return mouse;
}

glm::vec2 MouseEventListener::GetMouseOffset()
{
	return glm::vec2(mouse.x - prevMouse.x, prevMouse.y - mouse.y);
}

void MouseEventListener::UpdateMousePosition()
{
	int tempMouseX, tempMouseY;
	SDL_GetMouseState(&tempMouseX, &tempMouseY);
	tempMouseY = engineInstance->GetWindowSize().y - tempMouseY;
	if (firstUpdate)
	{
		prevMouse.x = mouse.x = tempMouseX;
		prevMouse.y = mouse.y = tempMouseY;

		firstUpdate = false;
	}
	else
	{
		prevMouse.x = mouse.x;
		prevMouse.y = mouse.y;
		mouse.x = tempMouseX;
		mouse.y = tempMouseY;
	}

}
