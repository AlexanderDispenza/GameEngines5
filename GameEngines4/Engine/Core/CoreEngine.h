#ifndef COREENGINE_H
#define COREENGINE_H



#include <memory>
#include "Window.h"
#include "Timer.h"
#include "GameInterface.h"
#include "Scene.h"
#include "Debugger.h"
#include "AudioHandler.h"
#include "Renderer.h"

#include "../Rendering/3D/GameObject.h"
#include "../Rendering/SceneGraph.h"

#include "../Graphics/ShaderHandler.h"
#include "../Graphics/TextureHandler.h"

#include "../Camera/Camera.h"
#include "../Event/EventListener.h"

#include "../Rendering/2D/ImGui_1.6/imgui.h"
#include "../Rendering/2D/ImGui_1.6/imgui_impl_sdl_gl3.h"

#include "OpenGLRenderer.h"

class CoreEngine
{
public:

	// Singleton 
	CoreEngine(const CoreEngine&) = delete;
	CoreEngine(CoreEngine&&) = delete;
	CoreEngine& operator=(const CoreEngine&) = delete;
	CoreEngine& operator=(CoreEngine&&) = delete;
	
	bool OnCreate(std::string name_, int width_, int height_);

	void Run();
	bool GetIsRunning() const;

	static CoreEngine* GetInstance();

	void SetGameInterface(GameInterface* gameInterface_, RenderType rendType_ = RenderType::OPENGL);

	int GetCurrentScene();
	void SetCurrentScene(int sceneNum_);

	glm::vec2 GetWindowSize() const;

	Camera* GetCamera() const;
	void SetCamera(Camera* camera_);

	void Exit();

	void NotifyOfMousePressed(glm::vec2 mouse_);
	void NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_);
	void NotifyOfMouseMove(glm::vec2 mouse_);
	void NotifyOfMouseScroll(int direction_);

	RenderType GetRendererType();
	void SetRendererType(RenderType rendType_);

	Renderer* GetRenderer();
	void SetRenderer(Renderer* renderer_);

	Window* GetWindow() const;

private:
	CoreEngine();
	~CoreEngine();

	static std::unique_ptr<CoreEngine> engineInstance;
	friend std::default_delete<CoreEngine>;

	void Update(const float deltaTime_);
	void Render();
	void OnDestroy();

	Window* window;
	bool isRunning;

	Timer timer;
	unsigned int fps;

	GameInterface* gameInterface;

	int currentSceneNum;

	Camera* camera;

	float windowColourR = 0;
	float windowColourG = 0;
	float windowColourB = 0;

	
	RenderType rendType;
	Renderer* renderer;
};
#endif

