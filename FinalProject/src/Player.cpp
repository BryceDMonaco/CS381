/*
 * Player.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: alex
 */

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
	}

	if (inputMgr->isSDown)
	{
		targetPosition.y = -positionBounds;
		targetPitch = -angleBounds;
	}

	if (!inputMgr->isWDown && !inputMgr->isSDown)
	{
		targetPosition.y = mPosition.y;
		targetPitch = 0.0f;
	}

	if (inputMgr->isADown)
	{
		targetPosition.x = -positionBounds;
		targetRoll = angleBounds;
	}

	if (inputMgr->isDDown)
	{
		targetPosition.x = positionBounds;
		targetRoll = -angleBounds;
	}

	if (!inputMgr->isADown && !inputMgr->isDDown)
	{
		targetPosition.x = mPosition.x;
		targetRoll = 0.0f;
	}
}


