/*
 * Player.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: alex
 */

#include "Player.h"
#include "Engine.h"
#include "EntityMgr.h"
#include "InputMgr.h"
#include "UIMgr.h"

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
	mTag = "Player";

	mSpeed = 200.0f;

	stationaryPosition = Ogre::Vector3::ZERO;
	movingVertical = false;
	movingHorizontal = false;
}

Player::~Player ()
{
	mSceneMgr = nullptr;
	delete mAspects;
	mAspects = nullptr;
}

void Player::Initialize()
{
	// create and attach entity and scene node
	mEntity = mSceneMgr->createEntity(mMeshFileName);
	mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mEntityName + "Node");
	mSceneNode->attachObject(mEntity);

	// create the aspects
	RenderableAspect* renderable = new RenderableAspect(this);
	PhysicsAspect* physics = new PhysicsAspect(this);
	CollisionAspect* collisions = new CollisionAspect(this);

	// add the aspects
	this->AddAspect(renderable);
	this->AddAspect(physics);
	this->AddAspect(collisions);

	//this->AddAspect(ai);

	inputMgr = mEntityMgr->engine->inputMgr;
}

void Player::Tick(float dt)
{
	HandleInput();

	for (int i = 0; i < (int) mAspects->size(); i++)
	{
		mAspects->at(i)->Tick(dt);

	}

	mEntityMgr->engine->uiMgr->mProgressBar->setProgress(((float)mHealth)/100.0f);

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

		movingVertical = true;
	}

	if (inputMgr->isSDown)
	{
		targetPosition.y = -positionBounds;
		targetPitch = -angleBounds;

		movingVertical = true;
	}

	if (!inputMgr->isWDown && !inputMgr->isSDown)
	{
		if (movingVertical)
		{
			movingVertical = false;
			stationaryPosition.y = mPosition.y;
		}

		targetPosition.y = stationaryPosition.y;
		targetPitch = 0.0f;
	}

	if (inputMgr->isADown)
	{
		targetPosition.x = -positionBounds;
		targetRoll = angleBounds;

		movingHorizontal = true;
	}

	if (inputMgr->isDDown)
	{
		targetPosition.x = positionBounds;
		targetRoll = -angleBounds;

		movingHorizontal = true;
	}

	if (!inputMgr->isADown && !inputMgr->isDDown)
	{
		if (movingHorizontal)
		{
			movingHorizontal = false;
			stationaryPosition.x = mPosition.x;
		}

		targetPosition.x = stationaryPosition.x;
		targetRoll = 0.0f;
	}
}

void Player::OnCollision(Entity381* collider, float timeSinceLastCollision)
{
	if (timeSinceLastCollision >= 0.5f
		&& (collider->mTag == "Obstacle"
			|| collider->mTag == "Destructible"
			|| collider->mTag == "Enemy"))
	{
		mHealth -= 25;
		Ogre::LogManager::getSingletonPtr()->logMessage("Player took damage");
		if (mHealth <= 0)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("Player is destroyed");
			// kill player
		}
	}
}

