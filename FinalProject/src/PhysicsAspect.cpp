#include "PhysicsAspect.h"
#include "Entity381.h"

#define PI 3.14159265

PhysicsAspect::PhysicsAspect (Entity381* ent) : Aspect (ent)
{

}

PhysicsAspect::~PhysicsAspect ()
{

}

void PhysicsAspect::Tick (float dt)
{
	Ogre::Vector3 distanceVector = mEntity381->targetPosition - mEntity381->mPosition;

	// position
	/*
	if (mEntity381->mPosition.x < mEntity381->targetPosition.x)
	{
		mEntity381->mPosition.x += mEntity381->mSpeed * dt;
	}
	else if (mEntity381->mPosition.x > mEntity381->targetPosition.x)
	{
		mEntity381->mPosition.x -= mEntity381->mSpeed * dt;
	}

	if (mEntity381->mPosition.y < mEntity381->targetPosition.y)
	{
		mEntity381->mPosition.y += mEntity381->mSpeed * dt;
	}
	else if (mEntity381->mPosition.y > mEntity381->targetPosition.y)
	{
		mEntity381->mPosition.y -= mEntity381->mSpeed * dt;
	}

	if (mEntity381->mPosition.z < mEntity381->targetPosition.z)
	{
		mEntity381->mPosition.z += mEntity381->mSpeed * dt;
	}
	else if (mEntity381->mPosition.z > mEntity381->targetPosition.z)
	{
		mEntity381->mPosition.z -= mEntity381->mSpeed * dt;
	}
	*/

	// position
	mEntity381->mVelocity = distanceVector.normalisedCopy() * mEntity381->mSpeed;
	mEntity381->mPosition = mEntity381->mPosition + mEntity381->mVelocity * dt;

	// rotation
	if (mEntity381->pitchDegree < mEntity381->targetPitch)
	{
		mEntity381->pitchDegree += mEntity381->mTurnRate * dt;
	}
	else if (mEntity381->pitchDegree > mEntity381->targetPitch)
	{
		mEntity381->pitchDegree -= mEntity381->mTurnRate * dt;
	}


	if (mEntity381->rollDegree < mEntity381->targetRoll)
	{
		mEntity381->rollDegree += mEntity381->mTurnRate * dt;
	}
	else if (mEntity381->rollDegree > mEntity381->targetRoll)
	{
		mEntity381->rollDegree -= mEntity381->mTurnRate * dt;
	}

	/*
	rotationMatrix.FromEulerAnglesYXZ(
		yawDegree,
		pitchDegree,
		rollDegree);

	mEntity381->mOrientation.FromRotationMatrix(rotationMatrix);
	*/
}
