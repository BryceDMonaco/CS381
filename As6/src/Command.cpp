/*
 * Command.cpp
 *
 *  Created on: Apr 7, 2019
 *      Author: alex
 */

Command::Command(Entity381* ent)
{
	entity = ent;
	isDone = false;
	physics = nullptr;
}

virtual Command::~Command()
{

}

void Command::init()
{
	physics = (PhysicsAspect*) entity->GetAspect(1);
}

virtual void Command::tick(float dt)
{

}

virtual bool Command::done()
{
	return isDone;
}

MoveTo::MoveTo(Entity381* ent, Ogre::Vector3 target) : Command(ent)
{
	targetLocation = target;
	MOVE_DISTANCE_THRESHOLD = 100;
	acceptanceRadius = 5;
}

MoveTo::~MoveTo()
{

}

void MoveTo::tick(float dt)
{
	Ogre::Vector3 squareDistance = entity->mPosition->squaredDistance(targetLocation);

	if (squareDistance > acceptanceRadius * acceptanceRadius)
	{
		physics->Accelerate(Ogre::Vector3(squareDistance.normalise()));
	}
	else
	{
		isDone = true;
	}
}

Intercept::Intercept(Entity381* ent, Ogre::Vector3 target) : Command(ent)
{
	targetLocation = target;
	MOVE_DISTANCE_THRESHOLD = 100;
	acceptanceRadius = 100;
}

Intercept::~Intercept()
{

}

void Intercept::tick(float dt)
{

}
