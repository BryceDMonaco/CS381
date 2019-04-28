#include "CollisionAspect.h"
#include "Entity381.h"
#include "EntityMgr.h"

CollisionAspect::CollisionAspect(Entity381* entity) : Aspect(entity)
{
	mCollisionRadius = 50.0f;
}

CollisionAspect::~CollisionAspect()
{
	mCollisions.clear();
}

void CollisionAspect::Tick(float dt)
{
	// check for collisions
	bool collisionHappened = CheckCollisions();

	// for each collision, call OnCollision function for this entity
	for (int i = 0; i < mCollisions.size(); i++)
	{

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
			if (mEntity381->mPosition.distance(it->second->mPosition) >= mCollisionRadius)
			{
				collisionHappened = true;
				mCollisions.push_back(it->second);
			}
		}
	}

	return false;
}
