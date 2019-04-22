#include "EntityMgr.h"

EntityMgr::EntityMgr (Engine* engine) : Mgr (engine)
{
	mSceneMgr = nullptr;  // Should be passed by graphics when it is init'd
	mEntities = new std::map<int, Entity381*>();
	mSelectedEntityID = -1;
	mNextEntityID = 0;
}

EntityMgr::EntityMgr (Ogre::SceneManager* mgr, Engine* engine) : Mgr (engine)
{
	mSceneMgr = mgr;
	mEntities = new std::map<int, Entity381*>();
	mSelectedEntityID = -1;
	mNextEntityID = 0;
}

EntityMgr::~EntityMgr ()
{
	delete mEntities;

	mSceneMgr = nullptr;
	mEntities = nullptr;

}

void EntityMgr::Tick (float dt)
{
	/*
	for (int i = 0; i < (int) mEntities->size(); i++)
	{
		mEntities->at(i)->Tick(dt);

	}
	*/
	for (std::map<int, Entity381*>::iterator it = mEntities->begin();
			it != mEntities->end(); it++)
	{
		it->second->Tick(dt);
	}

}

void EntityMgr::CreateEntityOfType(
		EntityType type,
		std::string name,
		std::string meshFileName,
		Ogre::Vector3 position,
		Ogre::Quaternion orientation,
		bool showAabb)
{
	Entity381* newEntity;

	// create the new entity based on the type parameter
	switch (type)
	{
	default:
		newEntity = new Entity381(
			mSceneMgr,
			mNextEntityID,
			name,
			meshFileName);
	}

	// initialize the new entity
	newEntity->Initialize();

	// enable/disable the bounding box
	newEntity->ShowAABB(showAabb);

	// add the entity to the map
	mEntities->insert(std::pair<int, Entity381*>(mNextEntityID, newEntity));
	mNextEntityID++;
}

void EntityMgr::DestroyEntity(int entityID)
{
	// get the iterator to the entity
	std::map<int, Entity381*>::iterator it = mEntities->find(entityID);

	// if it exists, destroy it
	if (it != mEntities->end())
		mEntities->erase(it);

}

void EntityMgr::IncrementSelectedID ()
{
	// if map is empty set to -1
	if (mEntities->size() <= 0)
	{
		mSelectedEntityID = -1;
		return;
	}

	// get the iterator to the entity
	std::map<int, Entity381*>::iterator it = mEntities->find(mSelectedEntityID);

	// increment it
	it++;

	// if at the end, loop back
	if (it == mEntities->end())
		it = mEntities->begin();

	// set the selected id to the key
	mSelectedEntityID = it->first;
}

Entity381* EntityMgr::GetSelectedEntity ()
{
	// get the iterator to the entity
	std::map<int, Entity381*>::iterator it = mEntities->find(mSelectedEntityID);

	// if it exists, return it
	if (it != mEntities->end())
		return it->second;
	else
		return nullptr;

}

std::map<int, Entity381*>* EntityMgr::GetEntities ()
{
	return mEntities;
}

int EntityMgr::GetSelectedEntityID ()
{
	return mSelectedEntityID;
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

void EntityMgr::SetSelectedEntityID (int id)
{
	// get the iterator to the entity
	std::map<int, Entity381*>::iterator it = mEntities->find(id);

	// if it exists, return it
	if (it != mEntities->end())
		mSelectedEntityID = id;
}

/*
void EntityMgr::ChangeEntityDesiredHeading (int index, float deltaDH)
{
	entities->at(selectedEntityIndex)->desiredHeading += deltaDH;

	if (deltaDH != 0)
	{
		std::cout << "Selected Ent's DH=" << entities->at(selectedEntityIndex)->desiredHeading << std::endl;

	}

}

void EntityMgr::SetEntitySpeed (int index, float sentSpeed)
{
	PhysicsAspect* target = (PhysicsAspect*) entities->at(selectedEntityIndex)->GetAspect(1);
	target->SetSpeed(sentSpeed);

}

void EntityMgr::SetEntityVelocity (int index, Ogre::Vector3* vel)
{
	PhysicsAspect* target = (PhysicsAspect*) entities->at(selectedEntityIndex)->GetAspect(1);
	target->SetVelocity(vel);

}

void EntityMgr::AccelerateEntity (int index, Ogre::Vector3* vec)
{
	PhysicsAspect* target = (PhysicsAspect*) entities->at(selectedEntityIndex)->GetAspect(1);
	target->Accelerate(*vec);

}

Ogre::Vector3* EntityMgr::GetEntityVelocity (int index)
{
	PhysicsAspect* target = (PhysicsAspect*) entities->at(selectedEntityIndex)->GetAspect(1);
	return target->GetVelocity();

}

void EntityMgr::IncreaseEntityHeight (int index, float amount)
{
	PhysicsAspect* target = (PhysicsAspect*) entities->at(selectedEntityIndex)->GetAspect(1);
	target->SetDesiredAltitude(amount + entities->at(selectedEntityIndex)->desiredAltitude);

}
*/