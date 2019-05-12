#include "EntityMgr.h"
#include "Command.h"

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
	//std::cout << mEntities->size() << std::endl;
	if (mEntities->size() > 0)
	{
		for (std::map<int, Entity381*>::iterator it = mEntities->begin();
				it != mEntities->end(); it++)
		{
			//std::cout << "in loop: " + std::to_string((int)mEntities->size() )<< std::endl;
			if (mEntities->size() > 0)
				it->second->Tick(dt);
			else
				break;
		}
	}


}

Entity381* EntityMgr::CreateEntityOfType(
		EntityType type,
		std::string name,
		std::string meshFileName,
		Ogre::Vector3 position,
		Ogre::Vector3 scale,
		Ogre::Quaternion orientation,
		bool showAabb)
{
	Entity381* newEntity;

	// create the new entity based on the type parameter
	switch (type)
	{
	case PLAYER:
		newEntity = new Player(
			mSceneMgr,
			this,
			mNextEntityID,
			name,
			"pCube2.mesh",
			position);

		scale *= 50;
		scale.z *= -1;

		break;
	case ENEMY_STATIC:
		newEntity = new StaticEnemy(
			mSceneMgr,
			this,
			mNextEntityID,
			name,
			"pCube3.mesh",
			position);

		scale *= 50;
		//scale.z *= -1;

		break;
	case ENEMY_DYNAMIC:
		newEntity = new DynamicEnemy(
			mSceneMgr,
			this,
			mNextEntityID,
			name,
			"pCube3.mesh",
			position);

		scale *= 50;
		//scale.z *= -1;

		break;
	case ENTITY_OBSTACLE:
		newEntity = new Entity381(
				mSceneMgr,
				this,
				mNextEntityID,
				name,
				meshFileName,
				position);

		newEntity->mTag = "Obstacle";

		break;
	case ENTITY_DESTRUCTIBLE:
		newEntity = new Entity381(
			mSceneMgr,
			this,
			mNextEntityID,
			name,
			"pCube1.mesh",
			position);

		newEntity->mTag = "Destructible";

		break;
	case PLAYER_BULLET:
		newEntity = new PlayerBullet(
			mSceneMgr,
			this,
			mNextEntityID,
			name,
			meshFileName,
			position);
		break;
	case WIN_TRIGGER:
		newEntity = new WinTrigger(
			mSceneMgr,
			this,
			mNextEntityID,
			name,
			"pCube1.mesh",
			position);
		break;
	default:
		newEntity = new Entity381(
			mSceneMgr,
			this,
			mNextEntityID,
			name,
			meshFileName,
			position);
	}

	// add the entity to the map
	mEntities->insert(std::pair<int, Entity381*>(mNextEntityID, newEntity));
	mNextEntityID++;

	// initialize the new entity
	newEntity->Initialize();

	// enable/disable the bounding box
	newEntity->ShowAABB(showAabb);

	// Scale the entity
	//newEntity->mPosition = position;
	newEntity->mSceneNode->setScale(scale);

	//For obstacles, randomly assign colors for now and give them a target
	if (type == ENTITY_OBSTACLE)
	{
		newEntity->AddAspect(new ObstacleHide(newEntity, 100));

		int choice = rand() % 3;  // If more than 3 colors, increase mod value
		//int choice = mNextEntityID % 3;

		if (choice == 0)
		{
			newEntity->mEntity->setMaterialName("Red");

		} else if (choice == 1)
		{
			newEntity->mEntity->setMaterialName("RadioactiveGreen");

		} else if (choice == 2)
		{
			newEntity->mEntity->setMaterialName("Blue");

		}

		//This comment can be changed to actual code once Alex's targetPosition code is merged
		newEntity->targetPosition = newEntity->mPosition + Ogre::Vector3::UNIT_Z * 200000;
		//newEntity->mSpeed *= 5;

	} else if (type == ENTITY_DESTRUCTIBLE)
	{
		newEntity->AddAspect(new ObstacleHide(newEntity, 100));

		newEntity->targetPosition = newEntity->mPosition + Ogre::Vector3::UNIT_Z * 200000;
		scale *= 20;
		newEntity->mSceneNode->setScale(scale);
		// Give health here

	} else if (type == WIN_TRIGGER)
	{
		newEntity->targetPosition = newEntity->mPosition + Ogre::Vector3::UNIT_Z * 200000;
		scale *= 0;
		newEntity->mSceneNode->setScale(scale);
	} /*else if (type == ENEMY_DYNAMIC)
	{
		DynamicEnemy* newEnemy = (DynamicEnemy*) newEntity;

		std::cout << "Adding player to enemy..." << std::endl;
		std::cout << "newEnemy location: " << newEnemy->mPosition << std::endl;

		std::map<int, Entity381*>::iterator it;
		for (it = mEntities->begin(); it != mEntities->end(); it++)
		{
			if (it->second->mEntityName == "Player")
				newEnemy->SetPlayer((Player*) it->second);
		}

		std::cout << "player location: " << newEnemy->mPlayer->mPosition << std::endl;

		newEntity = newEnemy;

		std::cout << "new entity location: " << newEntity->mPlayer->mPosition << std::endl;
	}*/

	//newEntity->mEntity->setMaterialName("Template/Red");
	return newEntity;
}

void EntityMgr::DestroyEntity(int entityID)
{
	// get the iterator to the entity
	std::map<int, Entity381*>::iterator it = mEntities->find(entityID);

	// if it exists, destroy it
	if (it != mEntities->end())
	{
		mSceneMgr->destroySceneNode(it->second->mSceneNode);
		//delete it->second;
		mEntities->erase(it);
	}
}

void EntityMgr::DestroyAll()
{
	std::map<int, Entity381*>::iterator it;
	for (it = mEntities->begin(); it != mEntities->end(); it++)
	{
		mSceneMgr->destroySceneNode(it->second->mSceneNode);
		//delete it->second;
		mEntities->erase(it);
	}

	mEntities->clear();
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
