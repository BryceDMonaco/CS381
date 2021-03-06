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
		// ensure iteration is not this entity and not an obstacle
		if (it->first != mEntity381->mEntityID && it->second->mTag != "Obstacle")
		{
			// compare the distance between these entities
			if (mEntity381->mPosition.distance(it->second->mPosition) <= mCollisionRadius)
			{
				//Ogre::LogManager::getSingletonPtr()->logMessage("Collision happened with " + it->second->mEntityName);
				collisionHappened = true;
				mCollisions.push_back(it->second);
			}
		}
		// if it is an obstacle, we'll handle the collision a bit differently
		if (it->first != mEntity381->mEntityID && it->second->mTag == "Obstacle")
		{
			// first compare z-axis values using collision radius
			if (Ogre::Math::Abs(mEntity381->mPosition.z - it->second->mPosition.z) <= mCollisionRadius)
			{
				float obstacleBaseSize = 120.0f;
				Ogre::Vector3 obstaclePos = it->second->mPosition;
				Ogre::Vector3 obstacleScale = it->second->mSceneNode->getScale();

				// then compare x and y values using obstacle's scale
				float upperBound = obstacleBaseSize * obstacleScale.y/2 + obstaclePos.y,
					  lowerBound = obstacleBaseSize * -obstacleScale.y/2 + obstaclePos.y,
					  leftBound = obstacleBaseSize * -obstacleScale.x/2 + obstaclePos.x,
					  rightBound = obstacleBaseSize * obstacleScale.x/2 + obstaclePos.x;

				if ((mEntity381->mPosition.x < rightBound && mEntity381->mPosition.x > leftBound)
				 && (mEntity381->mPosition.y < upperBound && mEntity381->mPosition.y > lowerBound))
				{
					//Ogre::LogManager::getSingletonPtr()->logMessage("Collision happened with " + it->second->mEntityName);
					collisionHappened = true;
					mCollisions.push_back(it->second);
				}
			}
		}
	}

	return collisionHappened;
}
