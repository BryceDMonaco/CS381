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

	mShooting = nullptr;
	shootInterval = 0.25f;
	shootTimer = shootInterval;

	obstacleHitInterval = 0.5f;
	obstacleHitTimer = obstacleHitInterval;
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
	ShootingAspect* shooting = new ShootingAspect(this);

	// add the aspects
	this->AddAspect(renderable);
	this->AddAspect(physics);
	this->AddAspect(collisions);
	this->AddAspect(shooting);

	mShooting = shooting;
	mShooting->mBullets.clear();
	mShooting->mBulletCount = 20;

	// create all the bullets
	for (int i = 0; i < mShooting->mBulletCount; i++)
	{
		mShooting->mBullets.push_back((PlayerBullet*)mEntityMgr->CreateEntityOfType(
			EntityType::PLAYER_BULLET,			// type
			"Bullet" + std::to_string(i),		// name
			"sphere.mesh",						// mesh file
			Ogre::Vector3(4000, 4000, 4000),	// position
			Ogre::Vector3(0.15f,0.15f,0.15f)));	// scale
	}

	inputMgr = mEntityMgr->engine->inputMgr;
}

void Player::Tick(float dt)
{
	shootTimer += dt;
	obstacleHitTimer += dt;

	HandleInput();

	for (int i = 0; i < (int) mAspects->size(); i++)
	{
		mAspects->at(i)->Tick(dt);
	}

	mEntityMgr->engine->uiMgr->mProgressBar->setProgress(((float)mHealth)/100.0f);

	bool nextLevel = CheckVictory();
	if (nextLevel)
	{
		mEntityMgr->engine->gameMgr->NextLevel();
	}

	if (mHealth <= 0)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("Player is destroyed");
		// kill player
		mEntityMgr->engine->gameMgr->changeGameState(GameState::GAME_START);
	}

}

void Player::HandleInput()
{
	float positionBounds = 250.0f;
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

	if (inputMgr->isSpaceDown && shootTimer >= shootInterval)
	{
		mShooting->Fire();
		shootTimer = 0.0f;
	}
}

void Player::OnCollision(Entity381* collider, float timeSinceLastCollision)
{
	//Ogre::LogManager::getSingletonPtr()->logMessage("Player hit " + collider->mEntityName);

	if (obstacleHitTimer >= obstacleHitInterval
		&& (collider->mTag == "Obstacle"
			|| collider->mTag == "Destructible"
			|| collider->mTag == "Enemy"))
	{
		mHealth -= 25;
		Ogre::LogManager::getSingletonPtr()->logMessage("Player took damage");

		obstacleHitTimer = 0.0f;
	}
}

bool Player::CheckVictory()
{
	std::map<int, Entity381*>::iterator it = mEntityMgr->GetEntities()->find(winTriggerID);
	if (it != mEntityMgr->GetEntities()->end())
	{
		if (it->second->mPosition.z > 0)
		{
			//Victory points
			//mEntityMgr->engine->uiMgr->currentScore += 100;

			return true;
		}
	}

	return false;
}

