#include "EnemyAI.h"
#include "Player.h"

EnemyAI::EnemyAI (Entity381* ent) : Aspect(ent)
{
	mPlayer = nullptr;
}

EnemyAI::~EnemyAI ()
{

}

void EnemyAI::Tick (float dt)
{
	// set target position
	mEntity381->targetPosition = mPlayer->mPosition;

	// set target orientation
	Ogre::Quaternion orientation;
	mEntity381->mSceneNode->lookAt(mPlayer->mPosition, Ogre::Node::TransformSpace::TS_WORLD);
	orientation = mEntity381->mSceneNode->getOrientation();
	mEntity381->targetPitch = orientation.getPitch().valueDegrees();
	mEntity381->targetYaw = orientation.getYaw().valueDegrees();
	mEntity381->targetRoll = orientation.getRoll().valueDegrees();
	mEntity381->pitchDegree = mEntity381->targetPitch;
	mEntity381->yawDegree = mEntity381->targetYaw;
	mEntity381->rollDegree = mEntity381->targetRoll;

}

void EnemyAI::SetPlayer(Player* player)
{
	mPlayer = player;
}
