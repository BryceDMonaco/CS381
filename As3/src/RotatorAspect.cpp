#include "RotatorAspect.h"

RotatorAspect::RotatorAspect (Entity381* ent, Ogre::SceneNode* myNode) : Aspect (ent)
{
	mSceneNode = myNode;

}

RotatorAspect::~RotatorAspect ()
{
	mSceneNode = nullptr;

}

void RotatorAspect::SetRotationalVelocity (float x, float y, float z)
{
	mVelocity.x = x;
	mVelocity.y = y;
	mVelocity.z = z;

	return;

}

void RotatorAspect::SetRotationalVelocity (Ogre::Vector3 vel)
{
	mVelocity = vel;

	return;

}

void RotatorAspect::Tick (float dt)
{
	mSceneNode->yaw(Ogre::Degree(mVelocity.y));

	return;

}
