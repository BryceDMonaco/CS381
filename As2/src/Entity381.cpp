#include "Entity381.h"

Entity381::Entity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name)
{
	mSceneMgr = manager;
	aspects = new std::vector<Aspect*>;
	mPosition = new Ogre::Vector3(0, 0, 0);

	RenderableAspect* renderable = new RenderableAspect(mPosition, mSceneMgr, type, name);
	PhysicsAspect* physics = new PhysicsAspect(mPosition);

	mSceneNode = renderable->GetSceneNode();

	RotatorAspect* rotate = new RotatorAspect(mSceneNode);
	rotate->SetRotationalVelocity(0, 1, 0);

	this->AddAspect(renderable);
	this->AddAspect(physics);
	this->AddAspect(rotate);

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
