#include "CollisionAspect.h"
#include "Entity381.h"
#include "EntityMgr.h"

CollisionAspect::CollisionAspect(Entity381* entity) : Aspect(entity)
{
	mCollisionRadius = 100.0f;
	mCollisionTimer = 0.0f;
}

CollisionAspect::~CollisionAspect()
{
	mCollisions.clear();
}

void CollisionAspect::Tick(float dt)
{
	mCollisionTimer += dt;

	// check for collisions
	bool collisionHappened = CheckCollisions();

	// for each collision, call OnCollision function for this entity
	if (collisionHappened)
	{
		for (int i = 0; i < mCollisions.size(); i++)
		{
			mEntity381->OnCollision(mCollisions[i], mCollisionTimer);
		}

		mCollisionTimer = 0.0f;
	}

}

bool CollisionAspect::CheckCollisions()
{
	bool collisionHappened = false;

	mCollisions.clear();

	std::map<int, Entity381*>* entities = mEntity381->mEntityMgr->GetEntities();
	std::map<int, Entity381*>::iterator it;
	for (it = entities->begin(); it != entities->end(); it++)
	{
		// ensure iteration is not this entity
		if (it->first != mEntity381->mEntityID)
		{
			// compare the distance between these entities
			if (mEntity381->mPosition.distance(it->second->mPosition) <= mCollisionRadius)
			{
				//Ogre::LogManager::getSingletonPtr()->logMessage("Collision happened with " + it->second->mEntityName);
				collisionHappened = true;
				mCollisions.push_back(it->second);
			}
		}
	}

	return collisionHappened;
}
