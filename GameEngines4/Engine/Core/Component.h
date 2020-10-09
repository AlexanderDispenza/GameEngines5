#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:

	inline Component() : go(nullptr) {}
	virtual ~Component() { go = nullptr; }

	virtual bool OnCreate(GameObject* go_) = 0;
	virtual void Update(const float deltaTime_) = 0;

protected:

	GameObject* go;

};
#endif


