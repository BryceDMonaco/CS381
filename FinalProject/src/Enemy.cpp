#include "Enemy.h"
#include "Engine.h"
#include "EntityMgr.h"

Enemy::Enemy (
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
	mTag = "Enemy";
}

Enemy::~Enemy ()
{
	mSceneMgr = nullptr;
	delete mAspects;
	mAspects = nullptr;
}

void Enemy::Initialize()
{
	// create and attach entity and scene node
	mEntity = mSceneMgr->createEntity(mMeshFileName);
	mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mEntityName + "Node");
	mSceneNode->attachObject(mEntity);

	// create the aspects
	RenderableAspect* renderable = new RenderableAspect(this);
	PhysicsAspect* physics = new PhysicsAspect(this);

	// add the aspects
	this->AddAspect(renderable);
	this->AddAspect(physics);
}

void Enemy::Tick(float dt)
{
	for (int i = 0; i < (int) mAspects->size(); i++)
	{
		mAspects->at(i)->Tick(dt);
	}
}

StaticEnemy::StaticEnemy (
	Ogre::SceneManager* manager,
	EntityMgr* entityMgr,
	int entityId,
	std::string entityName,
	std::string meshFileName,
	Ogre::Vector3 position,
	Ogre::Quaternion orientation)
: Enemy (manager,entityMgr,entityId,entityName,meshFileName,position,
	orientation)
{
	targetPosition = mPosition + Ogre::Vector3::UNIT_Z * 200000;
}

StaticEnemy::~StaticEnemy ()
{
	mSceneMgr = nullptr;
	delete mAspects;
	mAspects = nullptr;
}

void StaticEnemy::Initialize()
{
	// create and attach entity and scene node
	mEntity = mSceneMgr->createEntity(mMeshFileName);
	mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mEntityName + "Node");
	mSceneNode->attachObject(mEntity);

	// create the aspects
	RenderableAspect* renderable = new RenderableAspect(this);
	PhysicsAspect* physics = new PhysicsAspect(this);

	// add the aspects
	this->AddAspect(renderable);
	this->AddAspect(physics);
}

void StaticEnemy::Tick(float dt)
{
	for (int i = 0; i < (int) mAspects->size(); i++)
	{
		mAspects->at(i)->Tick(dt);
	}
}

DynamicEnemy::DynamicEnemy (
	Ogre::SceneManager* manager,
	EntityMgr* entityMgr,
	int entityId,
	std::string entityName,
	std::string meshFileName,
	Ogre::Vector3 position,
	Ogre::Quaternion orientation)
: Enemy (manager,entityMgr,entityId,entityName,meshFileName,position,
	orientation)
{
	mShooting = nullptr;
	shootInterval = 1.0f;
	shootTimer = 0.0f;
}

DynamicEnemy::~DynamicEnemy ()
{
	mSceneMgr = nullptr;
	delete mAspects;
	mAspects = nullptr;
}

void DynamicEnemy::Initialize()
{
	// create and attach entity and scene node
	mEntity = mSceneMgr->createEntity(mMeshFileName);
	mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mEntityName + "Node");
	mSceneNode->attachObject(mEntity);

	// create the aspects
	RenderableAspect* renderable = new RenderableAspect(this);
	PhysicsAspect* physics = new PhysicsAspect(this);
	ShootingAspect* shooting = new ShootingAspect(this);

	// add the aspects
	this->AddAspect(renderable);
	this->AddAspect(physics);
	this->AddAspect(shooting);
}

void DynamicEnemy::Tick(float dt)
{
	for (int i = 0; i < (int) mAspects->size(); i++)
	{
		mAspects->at(i)->Tick(dt);
	}
}
