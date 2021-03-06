/*
 * Command.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: alex
 */

#include "Command.h"
#include "Entity381.h"
#include "Utils.h"

Command::Command(Entity381* ent)
{
	entity = ent;
	isDone = false;
	runOnce = false;
	physics = nullptr;
}

Command::~Command()
{

}

void Command::init()
{
	physics = (PhysicsAspect*) entity->GetAspect(1);
}

void Command::tick(float dt)
{

}

bool Command::done()
{
	return isDone;
}

MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 target) : Command(ent)
{
	targetLocation = target;
	MOVE_DISTANCE_THRESHOLD = 100;
	acceptanceRadius = 1;
}

MoveTo::~MoveTo()
{

}

void MoveTo::tick(float dt)
{
	/*
	float distance = entity->mPosition->distance(targetLocation);

	Ogre::Vector3 direction = targetLocation - *entity->mPosition;

	if (distance > acceptanceRadius)
	{
		// set desired speed based on amount of turn remaining
		if (Ogre::Math::Abs(entity->desiredHeading - entity->heading) > 90)
		{
			entity->desiredSpeed = 0;
		}
		else if (Ogre::Math::Abs(entity->desiredHeading - entity->heading) > 45)
		{
			entity->desiredSpeed = 25;
		}
		else
		{
			entity->desiredSpeed = entity->maxSpeed;
		}

		// set desired heading
		entity->desiredHeading = FixAngle(Ogre::Math::ATan2(direction.x, direction.z).valueDegrees() - 90);
	}
	else
	{
		entity->desiredSpeed = 0;
		isDone = true;
	}
	*/
}

Intercept::Intercept(Entity381* ent, Entity381* target) : Command(ent)
{
	targetEntity = target;
	MOVE_DISTANCE_THRESHOLD = 100;
	acceptanceRadius = 100;
	lastTargetPosition = target->mPosition;
}

Intercept::~Intercept()
{

}

void Intercept::tick(float dt)
{
	/*
	float distance = entity->mPosition->distance(*targetEntity->mPosition);

	// get change in target position since last tick
	Ogre::Vector3 deltaTargetPos = *targetEntity->mPosition - lastTargetPosition;

	// predict next position
	Ogre::Vector3 nextTargetPos = *targetEntity->mPosition + deltaTargetPos;

	Ogre::Vector3 direction = nextTargetPos - *entity->mPosition;

	if (distance > acceptanceRadius)
	{
		// set desired speed based on amount of turn remaining
		if (Ogre::Math::Abs(entity->desiredHeading - entity->heading) > 90)
		{
			entity->desiredSpeed = 0;
		}
		else if (Ogre::Math::Abs(entity->desiredHeading - entity->heading) > 45)
		{
			entity->desiredSpeed = 25;
		}
		else
		{
			entity->desiredSpeed = entity->maxSpeed;
		}

		// set desired heading
		entity->desiredHeading = FixAngle(Ogre::Math::ATan2(direction.x, direction.z).valueDegrees() - 90);
	}
	else
	{
		entity->desiredSpeed = 0;
		isDone = true;
	}

	lastTargetPosition = *targetEntity->mPosition;
	*/
}
