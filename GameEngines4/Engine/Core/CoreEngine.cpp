#include "CoreEngine.h"
#include "Debugger.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine()
{
	rendType = RenderType::OPENGL;
	window = nullptr;
	isRunning = false;
	fps = 144;
	gameInterface = nullptr;
	currentSceneNum = 0; 
	camera = nullptr;
}

CoreEngine::~CoreEngine()
{
	ImGui_ImplSdlGL3_Shutdown();
	ImGui::DestroyContext();
	OnDestroy();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	Debugger::DebugInit();
	Debugger::SetSeverity(MessageType::TYPE_INFO);

	if (rendType == RenderType::OPENGL)
	{
		renderer = new OpenGLRenderer();

		window = new Window();
		if (!window->OnCreate(name_, width_, height_, renderer))
		{
			Debugger::FatalError("Window failed to initialize ", "CoreEngine.cpp ", __LINE__);
			isRunning = false;
		}

	}
	else if (rendType == RenderType::VULKAN)
	{
		//vulkan stuff here...
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth()/2, window->GetHeight()/2);

	MouseEventListener::RegisterEngineObject(this);
	
	/*
	ShaderHandler::GetInstance()->CreateProgram("colourShader",
		"Engine/Shaders/ColourVertexShader.glsl",
		"Engine/Shaders/ColourFragmentShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("basicShader", 
		"Engine/Shaders/VertexShader.glsl",
		"Engine/Shaders/FragementShader.glsl");

	ShaderHandler::GetInstance()->CreateProgram("particleShader",
		"Engine/Shaders/VertexParticleShader.glsl",
		"Engine/Shaders/FragmentParticleShader.glsl");
		*/

	if (gameInterface) 
	{
		if (!gameInterface->OnCreate()) 
		{
			Debugger::FatalError("GameInterface failed to initialize! ", "CoreEngine.cpp ", __LINE__);
		}
	}

	timer.Start();

	//initalise ImGUI
	ImGui::CreateContext();
	ImGui_ImplSdlGL3_Init(window->GetWindow());
	ImGui::StyleColorsDark();

	Debugger::Info("Engine launched successfully ", "CoreEngine.cpp ", __LINE__);
	
	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning)
	{
		timer.UpdateFrameTick();
		EventListener::Update();
		Update(timer.GetDeltaTime());
		
		ImGui_ImplSdlGL3_NewFrame(window->GetWindow());
		
		Render();
		SDL_Delay(timer.GetSleepTime(fps));
	}

	if (!isRunning) 
	{
		OnDestroy();
	}
}

bool CoreEngine::GetIsRunning() const
{
	return isRunning;
}

CoreEngine* CoreEngine::GetInstance()
{
	if (engineInstance.get() == nullptr) 
	{
		engineInstance.reset(new CoreEngine());
	}
	return engineInstance.get();
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_, RenderType rendType_)
{
	rendType = rendType_;
	gameInterface = gameInterface_;

}

int CoreEngine::GetCurrentScene()
{
	return currentSceneNum;
}

void CoreEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

glm::vec2 CoreEngine::GetWindowSize() const
{
	return glm::vec2(window->GetWidth(), window->GetHeight());
}

Camera* CoreEngine::GetCamera() const
{
	return camera;
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void CoreEngine::Exit()
{
	isRunning = false;
}

void CoreEngine::NotifyOfMousePressed(glm::vec2 mouse_)
{

}

void CoreEngine::NotifyOfMouseReleased(glm::vec2 mouse_, int buttonType_)
{
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);
}

void CoreEngine::NotifyOfMouseMove(glm::vec2 mouse_)
{
	if (camera)
	{
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffset());
	}
}

void CoreEngine::NotifyOfMouseScroll(int direction_)
{
	if (camera) 
	{
		camera->ProcessMouseZoom(direction_);
	}
}

RenderType CoreEngine::GetRendererType()
{
	return rendType;
}

void CoreEngine::SetRendererType(RenderType rendType_)
{
	rendType = rendType_;
}

Renderer* CoreEngine::GetRenderer()
{
	return renderer;
}

void CoreEngine::SetRenderer(Renderer* renderer_)
{
	renderer = renderer_;
}

Window* CoreEngine::GetWindow() const
{
	return window;
}

void CoreEngine::Update(const float deltaTime_)
{
	if (gameInterface)
	{
		gameInterface->Update(deltaTime_);
	}
}

void CoreEngine::Render()
{
	/*
	glClearColor(windowColourR, windowColourG, windowColourB, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	*/
	//Rend Game
	
	//ImGui::Begin("Test GUI");

	//if (ImGui::Button("Button Test"))
	//{
	//	std::cout << ("Button has been pressed\n");
	//}

	//ImGui::SliderFloat("R", &windowColourR, 0.0f, 1.0f);
	//ImGui::SliderFloat("G", &windowColourG, 0.0f, 1.0f);
	//ImGui::SliderFloat("B", &windowColourB, 0.0f, 1.0f);

	/*
	glClearColor(windowColourR, windowColourG, windowColourB, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	*/

	//ImGui::End();
	
	if (gameInterface) 
	{
		gameInterface->Render();
	}

	//ImGui::Render();
	//ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
	
	//SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()
{
	delete camera;
	camera = nullptr;

	ShaderHandler::GetInstance()->OnDestroy();
	TextureHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();
	CollisionHandler::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();
	AudioHandler::GetInstance()->OnDestroy();

	delete gameInterface;
	gameInterface = nullptr;

	delete window;
	window = nullptr;

	SDL_Quit();
	exit(0);
}

