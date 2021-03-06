#include "Entity381.h"

Entity381::Entity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head, bool isSubClass)
{
	mSceneMgr = manager;
	aspects = new std::vector<Aspect*>;
	mPosition = new Ogre::Vector3(0, 0, 0);
	heading = head;

	if (!isSubClass)  // Subclasses should be initialized at the end of their constructor
	{
		this->Initialize (manager, type, name);

	}

}

Entity381::~Entity381 ()
{
	mSceneMgr = nullptr;
	delete aspects;
	aspects = nullptr;

}

void Entity381::Tick (float dt)
{
	for (int i = 0; i < (int) aspects->size(); i++)
	{
		aspects->at(i)->Tick(dt);

	}

	return;

}

void Entity381::AddAspect (Aspect* aspect)
{
	aspects->push_back(aspect);

}

void Entity381::SetPosition (Ogre::Vector3* pos)
{
	mPosition->x = pos->x;
	mPosition->y = pos->y;
	mPosition->z = pos->z;

	return;

}

void Entity381::TranslatePosition (Ogre::Vector3* trans)
{
	mPosition->x = mPosition->x + trans->x;
	mPosition->y = mPosition->y + trans->y;
	mPosition->z = mPosition->z + trans->z;

	return;

}

Aspect* Entity381::GetAspect (int index)
{
	return aspects->at(index);

}

void Entity381::Initialize (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name)
{
	mSceneMgr = manager;
	aspects = new std::vector<Aspect*>;
	mPosition = new Ogre::Vector3(0, 0, 0);

	RenderableAspect* renderable = new RenderableAspect(this, mPosition, mSceneMgr, type, name);
	PhysicsAspect* physics = new PhysicsAspect(this, mPosition);

	mSceneNode = renderable->GetSceneNode();

	this->AddAspect(renderable);
	this->AddAspect(physics);

}

SphereEntity381::SphereEntity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head) : Entity381 (manager, type, name, head, true)
{
	meshFileName = "sphere.mesh";

	this->Initialize (manager, type, name);

}

CVN68Entity381::CVN68Entity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head) : Entity381 (manager, type, name, head, true)
{
	meshFileName = "cvn68.mesh";

	this->Initialize (manager, type, name);

}

CigBoatEntity381::CigBoatEntity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head) : Entity381 (manager, type, name, head, true)
{
	meshFileName = "cigarette.mesh";
	turnRate *= 3;
	acceleration *= 3;

	this->Initialize (manager, type, name);

}

DDG51Entity381::DDG51Entity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head) : Entity381 (manager, type, name, head, true)
{
	meshFileName = "ddg51.mesh";
	turnRate *= 3;
	acceleration *= 2;

	this->Initialize (manager, type, name);

}

SleekEntity381::SleekEntity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head) : Entity381 (manager, type, name, head, true)
{
	meshFileName = "sleek.mesh";

	turnRate *= 2;
	acceleration *= 4;

	this->Initialize (manager, type, name);

}

AShipEntity381::AShipEntity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head) : Entity381 (manager, type, name, head, true)
{
	meshFileName = "alienship.mesh";

	turnRate *= 15;
	acceleration *= 10;

	this->Initialize (manager, type, name);

}

BansheeEntity381::BansheeEntity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head) : Entity381 (manager, type, name, head, true)
{
	meshFileName = "banshee.mesh";

	turnRate *= 15;
	acceleration *= 10;
	climbRate = 10;

	this->Initialize (manager, type, name);

}
