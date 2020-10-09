#ifndef COMPONENTA_H
#define COMPONENTA_H

#include "../Core/Component.h"
#include <iostream>

class ComponentA : public Component
{
public:

	ComponentA();
	virtual ~ComponentA();

	bool OnCreate(GameObject* go_) override;
	void Update(const float deltaTime_) override;

private:
};

#endif

