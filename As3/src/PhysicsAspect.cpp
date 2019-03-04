#include "PhysicsAspect.h"
#include "Entity381.h"

#define PI 3.14159265

PhysicsAspect::PhysicsAspect (Entity381* ent, Ogre::Vector3* pos) : Aspect (ent)
{
	mPosition = pos;
	mVelocity = new Ogre::Vector3(0, 0, 0);

	mEntity381->desiredHeading = 45;

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

void PhysicsAspect::Accelerate (Ogre::Vector3* vec)
{
	mEntity381->desiredSpeed += mEntity381->acceleration * vec->x * -1;

	// Clamp the desiredSpeed
	if (mEntity381->desiredSpeed > mEntity381->maxSpeed)
	{
		mEntity381->desiredSpeed = mEntity381->maxSpeed;

	} else if (mEntity381->desiredSpeed < mEntity381->minSpeed)
	{
		mEntity381->desiredSpeed = mEntity381->minSpeed;

	}

}

void PhysicsAspect::Rotate (float dt)
{
	mEntity381->desiredHeading = ClampRotation(mEntity381->desiredHeading);

	if (std::abs(mEntity381->heading - mEntity381->desiredHeading) > 180)
	{
		if(mEntity381->desiredHeading > mEntity381->heading)
		{
			mEntity381->heading -= mEntity381->turnRate * dt;

		}else if (mEntity381->desiredHeading < mEntity381->heading)
		{
			mEntity381->heading += mEntity381->turnRate * dt;

		}

	} else
	{
		if(mEntity381->desiredHeading > mEntity381->heading)
		{
			mEntity381->heading += mEntity381->turnRate * dt;

		}else if (mEntity381->desiredHeading < mEntity381->heading)
		{
			mEntity381->heading -= mEntity381->turnRate * dt;

		}

	}



	// If within 0.1%, just set it to prevent stuttering infinitely
	if (std::abs(mEntity381->heading - mEntity381->desiredHeading) < 0.36f)
	{
		mEntity381->heading = mEntity381->desiredHeading;

	}


	mEntity381->heading = ClampRotation(mEntity381->heading);

}

Ogre::Vector3* PhysicsAspect::GetVelocity ()
{
	return mVelocity;

}

void PhysicsAspect::Tick (float dt)
{
	// Update speed
	if (mEntity381->speed < mEntity381->desiredSpeed)
	{
		mEntity381->speed += mEntity381->acceleration;

	} else if (mEntity381->speed > mEntity381->desiredSpeed)
	{
		mEntity381->speed -= mEntity381->acceleration;

	}

	// If speed and desiredSpeed have a 1% difference, just set speed = desiredSpeed to prevent ping ponging
	if (std::abs(mEntity381->speed - mEntity381->desiredSpeed)/((mEntity381->speed + mEntity381->desiredSpeed) / 2 < 0.01f))
	{
		mEntity381->speed = mEntity381->desiredSpeed;

	}

	if (mPosition != nullptr)
	{
		//Convert 1D Speed to 2D velocity vector
		mVelocity->x = -mEntity381->speed * std::cos(((mEntity381->heading - 90) * PI) / 180);
		mVelocity->y = -mEntity381->speed * std::sin(((mEntity381->heading - 90) * PI) / 180);

		mPosition->x += mVelocity->y * dt;
		mPosition->z += mVelocity->x * dt;

	}

	Rotate (dt);

	return;

}

// Just a small helper function to clamp a float in [0, 360)
float PhysicsAspect::ClampRotation (float rotation)
{
	if (rotation < 0)
	{
		while (rotation < 0)
		{
			rotation += 360;

		}

	} else if (rotation >= 360)
	{
		while (rotation >= 360)
		{
			rotation -= 360;

		}

	}

	return rotation;

}
