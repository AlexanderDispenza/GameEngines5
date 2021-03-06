#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H


#include <iostream>
#include "Component.h"
#include "../Rendering/3D/GameObject.h"

class AudioSource : public Component
{
public:

	AudioSource(std::string soundName_, bool shouldLoop, bool audio3D_, bool audioCompressed_);
	virtual ~AudioSource();

	virtual bool OnCreate(GameObject* go_) override;
	
	virtual void Update(const float deltaTime_) override;

    void PlaySound();
	bool isPlaying();

private:

	std::string soundName;

	int channelID;

};

#endif