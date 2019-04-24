/*
 * Player.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: alex
 */

#include "Player.h"
#include "InputMgr.h"

Player::Player (
	Ogre::SceneManager* manager,
	EntityMgr* entityMgr,
	int entityId,
	std::string entityName,
	std::string meshFileName,
	Ogre::Vector3 position,
	Ogre::Quaternion orientation)
: Entity381 (manager,entityMgr,entityId,entityName,meshFileName,position,
	orientation)
{
	stationaryPosition = Ogre::Vector3::ZERO;
	moving = false;
}

Player::~Player ()
{
	mSceneMgr = nullptr;
	delete mAspects;
	mAspects = nullptr;
}

void Player::Tick(float dt)
{
	HandleInput();

	for (int i = 0; i < (int) mAspects->size(); i++)
	{
		mAspects->at(i)->Tick(dt);

	}

	return;

}

void Player::HandleInput()
{
	float positionBounds = 1000.0f;
	float angleBounds = 45.0f;

	if (inputMgr->isWDown)
	{
		targetPosition.y = positionBounds;
		targetPitch = angleBounds;

		moving = true;
	}

	if (inputMgr->isSDown)
	{
		targetPosition.y = -positionBounds;
		targetPitch = -angleBounds;

		moving = true;
	}

	if (!inputMgr->isWDown && !inputMgr->isSDown)
	{
		if (moving)
		{
			moving = false;
			stationaryPosition = mPosition;
		}

		targetPosition.y = stationaryPosition.y;
		targetPitch = 0.0f;
	}

	if (inputMgr->isADown)
	{
		targetPosition.x = -positionBounds;
		targetRoll = angleBounds;

		moving = true;
	}

	if (inputMgr->isDDown)
	{
		targetPosition.x = positionBounds;
		targetRoll = -angleBounds;

		moving = true;
	}

	if (!inputMgr->isADown && !inputMgr->isDDown)
	{
		if (moving)
		{
			moving = false;
			stationaryPosition = mPosition;
		}

		targetPosition.x = stationaryPosition.x;
		targetRoll = 0.0f;
	}
}


