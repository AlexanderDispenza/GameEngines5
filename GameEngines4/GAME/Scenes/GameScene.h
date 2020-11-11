#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "../../Engine/Core/CoreEngine.h" 
#include <glm/gtx/string_cast.hpp>
#include "../../Engine/Components/ComponentA.h"
#include "../../Engine/Rendering/Particles/ParticleEmitter.h"

class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();
	
	virtual bool OnCreate();
	virtual void Update(const float deltaTime_);
	virtual void Render();

private:
	ParticleEmitter* particleEmitter;

};
#endif

