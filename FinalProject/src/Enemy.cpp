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
	mPlayer = nullptr;
	mShooting = nullptr;
	shootInterval = 1.0f;
	shootTimer = 0.0f;
	mAI = nullptr;
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
	mAI = new EnemyAI(this);

	// add the aspects
	this->AddAspect(renderable);
	this->AddAspect(physics);
	this->AddAspect(shooting);
	this->AddAspect(mAI);

	// get the player
	std::map<int, Entity381*>* entities = mEntityMgr->GetEntities();
	std::map<int, Entity381*>::iterator it;
	for (it = entities->begin(); it != entities->end(); it++)
	{
		if (it->second->mEntityName == "Player")
			mPlayer = (Player*) it->second;
	}
	std::cout << "Enemy position from enemy entity: " << mPosition << std::endl;
	std::cout << "Player position from enemy entity: " << mPlayer->mPosition << std::endl;


	// set the player in the ai aspect
	mAI->SetPlayer(mPlayer);
	std::cout << "Enemy position from enemy physics aspect: " << physics->mEntity381->mPosition << std::endl;
	std::cout << "Enemy position from enemy ai aspect: " << mAI->mEntity381->mPosition << std::endl;
	std::cout << "Player position from enemy ai aspect: " << mAI->mPlayer->mPosition << std::endl;
}

void DynamicEnemy::Tick(float dt)
{
	std::cout << "pitch before render: " << pitchDegree << std::endl;

	for (int i = 0; i < (int) mAspects->size(); i++)
	{
		mAspects->at(i)->Tick(dt);
	}

	std::cout << "pitch after render: " << pitchDegree << std::endl;
}

void DynamicEnemy::SetPlayer(Player* player)
{
	mPlayer = player;
	mAI->SetPlayer(player);
}