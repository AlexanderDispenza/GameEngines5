#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Model.h"
#include "../../Core/Component.h"

class GameObject
{
public:
	GameObject(Model* model_, glm::vec3 position_ = glm::vec3());
	~GameObject();
	
	void Render(Camera* camera_);
	void Update(const float deltaTime_);

	void SetPosition(glm::vec3 position_);
	void SetAngle(float angle_);
	void SetRotation(glm::vec3 rotation_);
	void SetScale(glm::vec3 scale_);
	void SetTag(std::string tag_);
	void SetHit(bool hit_, int buttonType_);

	std::string GetTag() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	float GetAngle() const;
	glm::vec3 GetScale() const;

	bool GetHit() const;

	BoundingBox GetBoundingBox();

private:

	Model* model;

	glm::vec3 position;
	glm::vec3 rotation;
	float angle;
	glm::vec3 scale;

	int modelInstance;

	BoundingBox box;

	std::string tag;

	bool hit;

	std::vector<Component*> components;

public:

	template<typename compToGet>
	Component* GetComponent()
	{
		//Check if there are any components on the gameobject 
		if (components.size() <= 0)
		{
			std::cout << ("Component list is empty\n");
			return nullptr;
		}

		for (auto comp : components) 
		{
			// return that there is a component attached to the gameobject
			if (dynamic_cast<compToGet*>(comp) != nullptr)
			{
				std::cout << ("returned template component\n");
				return comp;
			}
			else 
			{
				return nullptr;
			}
		}
	}

	template<typename compToAdd, typename...Args>
	void AddComponent(Args&& ... args_)
	{
		compToAdd* newComp = new compToAdd(std::forward<Args>(args_)...);

		//Check if the new component is a parented to the Component class
		if (dynamic_cast<Component*>(newComp) == nullptr)
		{
			Debugger::Error("Component is not a child of the component class", "GameObject.h", __LINE__);
			delete newComp;
			newComp = nullptr;

			return;
		}
		//Check if the component has already been added, if yes then remove it.
		if (GetComponent<compToAdd>() != nullptr)
		{
			Debugger::Error("This component already exsits on this object", "GameObject.h", __LINE__);
			delete newComp;
			newComp = nullptr;

			return;
		}

		components.push_back(newComp);
		newComp->OnCreate(this);

	}

	template<typename compToRemove>
	void RemoveComponent()
	{
		for (int i = 0; i < components.size(); i++)
		{
			if (dynamic_cast<compToRemove*>(components[i]) != nullptr) 
			{
				components.erase(components.begin() + i);
				std::cout << ("Component removed\n");
			}
			
		}
	}
};
#endif
