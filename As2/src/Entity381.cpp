#include "Entity381.h"

Entity381::Entity381 (Ogre::SceneManager* manager)
{
	mSceneMgr = manager;
	aspects = new std::vector<Aspect*>;
	mPosition = Ogre::Vector3::ZERO;

	RenderableAspect* renderable = new RenderableAspect(&this->mPosition, mSceneMgr, RenderableAspect::CUBE, "testcube");
	PhysicsAspect* physics = new PhysicsAspect(&this->mPosition);

	this->AddAspect(renderable);
	this->AddAspect(physics);

}

Entity381::~Entity381 ()
{
	mSceneMgr = nullptr;
	delete aspects;
	aspects = nullptr;

}

void Entity381::Tick (float dt)
{
	for (int i = 0; i < aspects->size(); i++)
	{
		aspects->at(i)->Tick(dt);

	}

	return;

}

void Entity381::AddAspect (Aspect* aspect)
{
	aspects->push_back(aspect);

}
