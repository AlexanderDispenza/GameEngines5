#include "OctSpatialPartition.h"

int OctNode::childNum = 0;

OctNode::OctNode(glm::vec3 pos_, float size_, OctNode* parent_) : octBounds(nullptr), parent(nullptr), children(), 
objectList(std::vector<GameObject*>())
{
	objectList.reserve(10);
	octBounds = new BoundingBox();

	octBounds->minVert = pos_;
	octBounds->maxVert = pos_ + glm::vec3(size_);

	size = size_;

	parent = parent_;

	for (int i = 0; i < CHILDREN_NUMBER; i++)
	{
		children[i] = nullptr;
	}
}

OctNode::~OctNode()
{
	OnDestroy();
}

void OctNode::OnDestroy()
{
	delete octBounds;
	octBounds = nullptr;

	if (objectList.size() > 0) 
	{
		for (auto obj : objectList) 
		{
			obj = nullptr;
		}
		objectList.clear();
	}

	for (int i = 0; i < CHILDREN_NUMBER; i++)
	{
		if (children[i] != nullptr)
		{
			delete children[i];
		}
		children[i] = nullptr;
	}
}

void OctNode::Octify(int depth_)
{
	if (depth_ > 0 && this) 
	{
		float half = size / 2.0f;

		children[static_cast<int>(OctChildren::OCT_TLF)] = new OctNode(glm::vec3(octBounds->minVert.x,
			octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);


		children[static_cast<int>(OctChildren::OCT_BLF)] = new OctNode(glm::vec3(octBounds->minVert.x + half,
			octBounds->minVert.y, octBounds->minVert.z + half), half, this);


		children[static_cast<int>(OctChildren::OCT_BRF)] = new OctNode(glm::vec3(octBounds->minVert.x,
			octBounds->minVert.y, octBounds->minVert.z + half), half, this);


		children[static_cast<int>(OctChildren::OCT_TRF)] = new OctNode(glm::vec3(octBounds->minVert.x,
			octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);


		children[static_cast<int>(OctChildren::OCT_TLR)] = new OctNode(glm::vec3(octBounds->minVert.x,
			octBounds->minVert.y + half, octBounds->minVert.z - half), half, this);


		children[static_cast<int>(OctChildren::OCT_BLR)] = new OctNode(glm::vec3(octBounds->minVert.x,
			octBounds->minVert.y, octBounds->minVert.z - half), half, this);


		children[static_cast<int>(OctChildren::OCT_BRR)] = new OctNode(glm::vec3(octBounds->minVert.x,
			octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);

		
		children[static_cast<int>(OctChildren::OCT_TRR)] = new OctNode(glm::vec3(octBounds->minVert.x,
			octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);


		childNum += CHILDREN_NUMBER;
	}
	if (depth_ > 0 && this)
	{
		for (int i = 0; i < CHILDREN_NUMBER; i++)
		{
			children[i]->Octify(depth_ - 1);
		}
	}
}

OctNode* OctNode::GetParent()
{
	return parent;
}

OctNode* OctNode::GetChild(OctChildren childPos_)
{
	return children[static_cast<int>(childPos_)];
}

void OctNode::AddCollisionObject(GameObject* obj_)
{
	objectList.push_back(obj_);
}

int OctNode::GetObjectCount() const
{
	return objectList.size();
}

bool OctNode::isLeaf() const
{
	if (children[0] == nullptr)
	{
		return true;
	}	
	return false;
}

BoundingBox* OctNode::GetBoundingBox() const
{
	return octBounds;
}

int OctNode::GetChildCount() const
{
	return childNum;
}


//////Class OctSpatialPartition//////

OctSpatialPartition::OctSpatialPartition(float worldSize_) : 
	root(nullptr), rayIntersectionList(std::vector<OctNode*>())
{
	root = new OctNode(glm::vec3(-(worldSize_ / 2.0f)), worldSize_, nullptr);
	root->Octify(3);
	std::cout << "There are " << root->GetChildCount() << " child nodes" << std::endl;

	rayIntersectionList.reserve(20);
}

OctSpatialPartition::~OctSpatialPartition()
{
	OnDestroy();
}

void OctSpatialPartition::OnDestroy()
{
	if (rayIntersectionList.size() > 0)
	{
		for (auto cell : rayIntersectionList)
		{
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}

	delete root;
	root = nullptr;
}

void OctSpatialPartition::AddObject(GameObject* obj_)
{
	AddObjectToCell(root, obj_);
}

GameObject* OctSpatialPartition::GetCollision(Ray ray_)
{
	if (rayIntersectionList.size() > 0)
	{
		for (auto cell : rayIntersectionList)
		{
			cell = nullptr;
		}
		rayIntersectionList.clear();
	}
	PrepareCollisionQuery(root, ray_);
	GameObject* resualt = nullptr;
	float shortestDist = FLT_MAX;

	for (auto cell : rayIntersectionList)
	{
		for (auto obj : cell->objectList)
		{
			if (ray_.IsColliding(&obj->GetBoundingBox()) )
			{
				if (ray_.intersectionDistance < shortestDist)
				{
					resualt = obj;
					shortestDist = ray_.intersectionDistance;
				}
			}
		}
		if (resualt != nullptr)
		{
			return resualt;
		}
	}
	return nullptr;
}

void OctSpatialPartition::AddObjectToCell(OctNode* cell_, GameObject* obj_)
{
	//hmwk

	if (cell_ == nullptr)
	{
		return;
	}

	BoundingBox tempCellBBox = *cell_->GetBoundingBox();

	if (tempCellBBox.Intersects(&obj_->GetBoundingBox()))
	{
		if (cell_->isLeaf())
		{
			cell_->AddCollisionObject(obj_);

		}
		else 
		{
			for (int i = 0; i < CHILDREN_NUMBER; i++)
			{
				AddObjectToCell(cell_->children[i], obj_);
			}
		}
	}

}

void OctSpatialPartition::PrepareCollisionQuery(OctNode* cell_, Ray ray_)
{
	//hmwk

	if (cell_ == nullptr)
	{
		return;
	}

	BoundingBox tempCellBBox = *cell_->GetBoundingBox();

	if (ray_.IsColliding(&tempCellBBox))
	{
		if (cell_->isLeaf())
		{
			rayIntersectionList.push_back(cell_);
		}
		else
		{
			for (int i = 0; i < CHILDREN_NUMBER; i++)
			{
				PrepareCollisionQuery(cell_->children[i], ray_);
			}
		}
	}
}
