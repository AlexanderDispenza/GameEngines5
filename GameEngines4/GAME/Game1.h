#ifndef GAME1_H
#define GAME1_H

#include "../Engine/Core/CoreEngine.h"
#include "Scenes/StartScene.h"
#include "Scenes/GameScene.h"


class Game1 : public GameInterface
{
public:
	Game1();
	virtual ~Game1(); 

	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();

private:
	
	int currentSceneNum;
	Scene* currentScene;
	void BuildScene();

	float windowColourR = 0;
	float windowColourG = 0;
	float windowColourB = 0;


};
#endif
