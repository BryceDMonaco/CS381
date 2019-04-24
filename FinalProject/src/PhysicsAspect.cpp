#include "PhysicsAspect.h"
#include "Entity381.h"

#define PI 3.14159265

PhysicsAspect::PhysicsAspect (Entity381* ent) : Aspect (ent)
{

}

PhysicsAspect::~PhysicsAspect ()
{

}

/*
void PhysicsAspect::Accelerate (Ogre::Vector3 vec)
{
	mEntity381->desiredSpeed += mEntity381->acceleration * vec.x * -1;

	// Clamp the desiredSpeed
	if (mEntity381->desiredSpeed > mEntity381->maxSpeed)
	{
		mEntity381->desiredSpeed = mEntity381->maxSpeed;

	} else if (mEntity381->desiredSpeed < mEntity381->minSpeed)
	{
		mEntity381->desiredSpeed = mEntity381->minSpeed;

	}

}
*/

/*
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
*/

void PhysicsAspect::Tick (float dt)
{
	/*
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

	if (mEntity381->climbRate != 0)
	{
		float direction = (mPosition->y < mEntity381->desiredAltitude) ? 1 : -1;

		mEntity381->altitude += direction * mEntity381->climbRate * dt;

	}

	if (mPosition != nullptr)
	{
		//Convert 1D Speed to 2D velocity vector, -90 degrees because the models are parallel with x axis instead of z
		mVelocity->x = -mEntity381->speed * std::cos(((mEntity381->heading - 90) * PI) / 180);
		mVelocity->y = -mEntity381->speed * std::sin(((mEntity381->heading - 90) * PI) / 180);

		mPosition->x += mVelocity->y * dt;
		mPosition->y = mEntity381->altitude;
		mPosition->z += mVelocity->x * dt;

	}

	Rotate (dt);

	return;
	*/

	/*
	// get world Orientation from local orientation
	Ogre::Quaternion localOrientation = mEntity381->mSceneNode->getOrientation();
	Ogre::Quaternion worldOrientation = mEntity381->mSceneNode->convertLocalToWorldOrientation(
		localOrientation);

	Ogre::Matrix3 rotationMatrix;

	worldOrientation.ToRotationMatrix(rotationMatrix);

	Ogre::Radian yaw;
	Ogre::Radian pitch;
	Ogre::Radian roll;

	rotationMatrix.ToEulerAnglesXYZ(yaw, pitch, roll);

	Ogre::Degree yawDegree = yaw;
	Ogre::Degree pitchDegree = pitch;
	Ogre::Degree rollDegree = roll;
	*/

	/*
	// used to check if at north pole or south pole
	float poleCheck = worldOrientation.x * worldOrientation.y + worldOrientation.z * worldOrientation.w;

	// set roll to zero if at north pole or south pole, else set it normally
	if ((poleCheck > 0.499 && poleCheck < 0.501)
	 || (poleCheck > -0.501 && poleCheck < -0.499))
	{
		roll = Ogre::Radian(0.0f);
	}
	else
	{
		roll = Ogre::Math::ATan2(2 * worldOrientation.x * worldOrientation.w - 2 * worldOrientation.y * worldOrientation.z,
			1 - 2 * Ogre::Math::Sqr(worldOrientation.x) - 2 * Ogre::Math::Sqr(worldOrientation.z));
	}

	// set pitch
	pitch = Ogre::Math::ASin(2 * worldOrientation.x * worldOrientation.y
		+ 2 * worldOrientation.z * worldOrientation.w);
	*/

	// position
	if (mEntity381->mPosition.x < mEntity381->targetPosition.x)
	{
		mEntity381->mPosition.x += mEntity381->mSpeed * dt;
	}
	else
	{
		mEntity381->mPosition.x -= mEntity381->mSpeed * dt;
	}

	if (mEntity381->mPosition.y < mEntity381->targetPosition.y)
	{
		mEntity381->mPosition.y += mEntity381->mSpeed * dt;
	}
	else
	{
		mEntity381->mPosition.y -= mEntity381->mSpeed * dt;
	}

	if (mEntity381->mPosition.z < mEntity381->targetPosition.z)
	{
		mEntity381->mPosition.z += mEntity381->mSpeed * dt;
	}
	else
	{
		mEntity381->mPosition.z -= mEntity381->mSpeed * dt;
	}

	// rotation
	if (mEntity381->pitchDegree < mEntity381->targetPitch)
	{
		mEntity381->pitchDegree += mEntity381->mTurnRate * dt;
	}
	else
	{
		mEntity381->pitchDegree -= mEntity381->mTurnRate * dt;
	}


	if (mEntity381->rollDegree < mEntity381->targetRoll)
	{
		mEntity381->rollDegree += mEntity381->mTurnRate * dt;
	}
	else
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
