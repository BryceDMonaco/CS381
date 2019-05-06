#include "Bullet.h"
#include "Engine.h"
#include "EntityMgr.h"
#include "InputMgr.h"

Bullet::Bullet (
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
	mTag = "Bullet";

	mSpeed = 200.0f;

	initialPos = position;

	hitInterval = 0.5f;
	hitTimer = hitInterval;
}

Bullet::~Bullet()
{

}

void Bullet::Initialize()
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
}

void Bullet::Tick(float dt)
{
	hitTimer += dt;

	for (int i = 0; i < (int) mAspects->size(); i++)
	{
		mAspects->at(i)->Tick(dt);
	}
}

void Bullet::Reset()
{
	mPosition = initialPos;
	targetPosition = mPosition;
}

void Bullet::OnCollision(Entity381* collider, float timeSinceLastCollision)
{

}

PlayerBullet::PlayerBullet (
	Ogre::SceneManager* manager,
	EntityMgr* entityMgr,
	int entityId,
	std::string entityName,
	std::string meshFileName,
	Ogre::Vector3 position,
	Ogre::Quaternion orientation)
: Bullet (manager,entityMgr,entityId,entityName,meshFileName,position,
	orientation)
{
	mTag = "PlayerBullet";
}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::OnCollision(Entity381* collider, float timeSinceLastCollision)
{
	// TODO: handle player bullet collision
	//if (timeSinceLastCollision > 0.5f)
	//{
		if (collider->mTag == "Destructible" /*&& hitTimer >= hitInterval*/)
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("destructible hit");
			collider->mHealth -= 25;
			if (collider->mHealth <= 0)
			{
				mEntityMgr->DestroyEntity(collider->mEntityID);
			}

			hitTimer = 0.0f;
			Reset();
		}
		else if (collider->mTag == "Obstacle")
		{
			Ogre::LogManager::getSingletonPtr()->logMessage("obstacle hit");
			Reset();
		}
	//}
}

EnemyBullet::EnemyBullet (
	Ogre::SceneManager* manager,
	EntityMgr* entityMgr,
	int entityId,
	std::string entityName,
	std::string meshFileName,
	Ogre::Vector3 position,
	Ogre::Quaternion orientation)
: Bullet (manager,entityMgr,entityId,entityName,meshFileName,position,
	orientation)
{
	mTag = "EnemyBullet";
}

EnemyBullet::~EnemyBullet()
{

}

void EnemyBullet::OnCollision(Entity381* collider, float timeSinceLastCollision)
{
	// TODO: handle enemy bullet collision
}
