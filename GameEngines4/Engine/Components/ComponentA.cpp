#include "ComponentA.h"

ComponentA::ComponentA()
{
}

ComponentA::~ComponentA()
{
	std::cout << ("ComponentA has been removed\n");
}

bool ComponentA::OnCreate(GameObject* go_)
{
	std::cout << ("ComponentA has been created\n");
	return true;
}

void ComponentA::Update(const float deltaTime_)
{
	std::cout << "ComponentA is updating\n";
}
