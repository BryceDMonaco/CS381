#include "CollisionAspect.h"

CollisionAspect::CollisionAspect(Entity381* entity)
{
	mCollisionRadius = 50.0f;
}

CollisionAspect::~CollisionAspect()
{
	mCollisions.clear();
}

virtual void CollisionAspect::Tick(float dt)
{
	mCollisions.clear();

	// check for collisions
	bool collisionHappened = CheckCollisions();

	// for each collision, call OnCollision function for this entity
	for (int i = 0; i < mCollisions.size(); i++)
	{

	}
}

bool CollisionAspect::CheckCollisions()
{
	return false;
}
