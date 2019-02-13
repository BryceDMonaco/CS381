#include "PhysicsAspect.h"

PhysicsAspect::PhysicsAspect (Ogre::Vector3* posVector)
{
	mPosition = posVector;

}

PhysicsAspect::~PhysicsAspect ()
{
	mPosition = nullptr;

}

void PhysicsAspect::SetVelocity (float x, float y, float z)
{
	mVelocity.x = x;
	mVelocity.y = y;
	mVelocity.z = z;

	return;

}

void PhysicsAspect::SetVelocity (Ogre::Vector3 vel)
{
	mVelocity = vel;

	return;

}

void PhysicsAspect::Tick (float dt)
{
	(*mPosition) = (*mPosition) + mVelocity * dt;

	return;

}
