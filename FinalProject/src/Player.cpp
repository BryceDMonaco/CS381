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

}


