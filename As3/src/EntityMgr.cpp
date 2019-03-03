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

void EntityMgr::CreateAs2Scene ()
{
	for (int i = 0; i < 2; i ++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 0) // Cube
			{
				CreateEntity (RenderableAspect::Types::CUBE, std::to_string((i*5) + j), new Ogre::Vector3(250 * i, 100, 250 * j));


			} else // Sphere
			{
				CreateSphereEntity (RenderableAspect::Types::SPHERE, std::to_string((i*5) + j), new Ogre::Vector3(250 * i, 100, 250 * j));

			}

		}

	}



}

void EntityMgr::CreateSphereEntity(RenderableAspect::Types type, std::string name, Ogre::Vector3* pos)
{
	//Assume for now we just want a cube entity
	Entity381* newEntity = new SphereEntity381(mSceneMgr, type, name);

	newEntity->SetPosition (pos);

	entities->push_back(newEntity);

	//If this is the first entity, show the box
	if (entities->size() == 1)
	{
		RenderableAspect* target = (RenderableAspect*) entities->at(selectedEntityIndex)->GetAspect(0);
		target->ShowAABB (true);

	}

	return;


}

void EntityMgr::CreateEntity(RenderableAspect::Types type, std::string name, Ogre::Vector3* pos)
{
	//Assume for now we just want a cube entity
	Entity381* newEntity = new Entity381(mSceneMgr, type, name, false);

	newEntity->SetPosition (pos);

	entities->push_back(newEntity);

	//If this is the first entity, show the box
	if (entities->size() == 1)
	{
		RenderableAspect* target = (RenderableAspect*) entities->at(selectedEntityIndex)->GetAspect(0);
		target->ShowAABB (true);

	}

	return;


}

void EntityMgr::DestroyEntity()
{


}


bool EntityMgr::SetSceneMgr (Ogre::SceneManager* mgr) //Should only be called once
{
	if (mSceneMgr != nullptr) //Already assigned
	{
		return false;

	}

	mSceneMgr = mgr;

	return true;

}

Entity381* EntityMgr::GetSelectedEntity ()
{
	return entities->at(selectedEntityIndex);

}

void EntityMgr::IncrementSeclectedIndex ()
{
	//Turn off the old bounding box
	RenderableAspect* target = (RenderableAspect*) entities->at(selectedEntityIndex)->GetAspect(0);
	target->ShowAABB (false);

	selectedEntityIndex = (selectedEntityIndex + 1) % entities->size();

	//Turn on the new bounding box
	target = (RenderableAspect*) entities->at(selectedEntityIndex)->GetAspect(0);
	target->ShowAABB (true);

	return;

}

int EntityMgr::GetSelectedEntityIndex ()
{
	return selectedEntityIndex;

}

void EntityMgr::SetEntityVelocity (int index, Ogre::Vector3* vel)
{
	PhysicsAspect* target = (PhysicsAspect*) entities->at(selectedEntityIndex)->GetAspect(1);
	target->SetVelocity(vel);

}

Ogre::Vector3* EntityMgr::GetEntityVelocity (int index)
{
	PhysicsAspect* target = (PhysicsAspect*) entities->at(selectedEntityIndex)->GetAspect(1);
	return target->GetVelocity();

}
