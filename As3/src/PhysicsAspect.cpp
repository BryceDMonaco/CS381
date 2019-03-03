#include "PhysicsAspect.h"

PhysicsAspect::PhysicsAspect (Entity381* ent, Ogre::Vector3* pos) : Aspect (ent)
{
	mPosition = pos;
	mVelocity = new Ogre::Vector3(0, 0, 0);

}

PhysicsAspect::~PhysicsAspect ()
{
	mPosition = nullptr;
	mVelocity = nullptr;

}

void PhysicsAspect::SetVelocity (float x, float y, float z)
{
	mVelocity->x = x;
	mVelocity->y = y;
	mVelocity->z = z;

	return;

}

void PhysicsAspect::SetVelocity (Ogre::Vector3* vel)
{
	(*mVelocity) = (*vel);

	return;

}

Ogre::Vector3* PhysicsAspect::GetVelocity ()
{
	return mVelocity;

}

void PhysicsAspect::Tick (float dt)
{
	if (mPosition != nullptr)
	{
		mPosition->x += mVelocity->x * dt;
		mPosition->y += mVelocity->y * dt;
		mPosition->z += mVelocity->z * dt;

	}

	return;

}
