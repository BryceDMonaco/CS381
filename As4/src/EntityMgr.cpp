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
	for (int i = 0; i < (int) entities->size(); i++)
	{
		entities->at(i)->Tick(dt);

	}

}

void EntityMgr::CreateAs2Scene ()
{
	for (int i = 0; i < 5; i ++)
	{
		CreateEntityOfTypeAtPositionAndHeading (i, std::to_string(i), new Ogre::Vector3(500 * i, 0, 0), 45 * i);

	}



}

void EntityMgr::CreateEntityOfTypeAtPositionAndHeading(int entity381Type, std::string name, Ogre::Vector3* pos, float heading)
{
	Entity381* newEntity = nullptr;

	if (entity381Type == 0)  // CVN68
	{
		newEntity = new CVN68Entity381 (mSceneMgr, RenderableAspect::OTHER, name, heading);

	} else if (entity381Type == 1)  // Cig
	{
		newEntity = new CigBoatEntity381 (mSceneMgr, RenderableAspect::OTHER, name, heading);

	} else if (entity381Type == 2)  // DDG51
	{
		newEntity = new DDG51Entity381 (mSceneMgr, RenderableAspect::OTHER, name, heading);

	} else if (entity381Type == 3)  // Sleek
	{
		newEntity = new SleekEntity381 (mSceneMgr, RenderableAspect::OTHER, name, heading);

	} else if (entity381Type == 4)  // Alienship
	{
		newEntity = new AShipEntity381 (mSceneMgr, RenderableAspect::OTHER, name, heading);

	} else
	{
		//By default, create a cube
		newEntity = new Entity381(mSceneMgr, RenderableAspect::CUBE, name, heading, false);

	}

	newEntity->SetPosition (pos);
	newEntity->heading = heading;
	newEntity->entityName = name;

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

void EntityMgr::ChangeEntityDesiredHeading (int index, float deltaDH)
{
	entities->at(selectedEntityIndex)->desiredHeading += deltaDH;

	if (deltaDH != 0)
	{
		std::cout << "Selected Ent's DH=" << entities->at(selectedEntityIndex)->desiredHeading << std::endl;

	}

}

void EntityMgr::SetEntityVelocity (int index, Ogre::Vector3* vel)
{
	PhysicsAspect* target = (PhysicsAspect*) entities->at(selectedEntityIndex)->GetAspect(1);
	target->SetVelocity(vel);

}

void EntityMgr::AccelerateEntity (int index, Ogre::Vector3* vec)
{
	PhysicsAspect* target = (PhysicsAspect*) entities->at(selectedEntityIndex)->GetAspect(1);
	target->Accelerate(vec);

}

Ogre::Vector3* EntityMgr::GetEntityVelocity (int index)
{
	PhysicsAspect* target = (PhysicsAspect*) entities->at(selectedEntityIndex)->GetAspect(1);
	return target->GetVelocity();

}
