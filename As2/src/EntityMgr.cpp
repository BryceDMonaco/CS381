#include "EntityMgr.h"

EntityMgr::EntityMgr (Ogre::SceneManager* mgr)
{
	mSceneMgr = mgr;
	entities = new std::vector<Entity381*>;

}

EntityMgr::~EntityMgr ()
{
	delete entities;

	mSceneMgr = nullptr;
	entities = nullptr;

}

void EntityMgr::Tick (float dt)
{
	for (int i = 0; i < entities->size(); i++)
	{
		entities->at(i)->Tick(dt);

	}

}

void EntityMgr::CreateEntity()
{
	//Assume for now we just want a cube entity
	Entity381* newEntity = new Entity381(mSceneMgr);

	entities->push_back(newEntity);

	return;


}

void EntityMgr::DestroyEntity()
{


}
;
