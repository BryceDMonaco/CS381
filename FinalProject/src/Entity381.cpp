#include "Entity381.h"
#include "Engine.h"
#include "EntityMgr.h"
#include "InputMgr.h"

Entity381::Entity381 (
		Ogre::SceneManager* manager,
		EntityMgr* entityMgr,
		int entityId,
		std::string name,
		std::string meshFileName,
		Ogre::Vector3 position,
		Ogre::Quaternion orientation)
{
	mAspects = new std::vector<Aspect*>;

	mSceneMgr = manager;
	mEntityMgr = entityMgr;
	mEntityID = entityId;
	mEntityName = name;
	mMeshFileName = meshFileName;
	mPosition = position;
	mOrientation = orientation;

	targetPitch = 0.0f;
	targetYaw = 0.0f;
	targetRoll = 0.0f;

	inputMgr = nullptr;
}

Entity381::~Entity381 ()
{
	mSceneMgr = nullptr;
	delete mAspects;
	mAspects = nullptr;
}

void Entity381::Initialize ()
{
	// create and attach entity and scene node
	mEntity = mSceneMgr->createEntity(mMeshFileName);
	mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mEntityName + "Node");
	mSceneNode->attachObject(mEntity);

	// create the aspects
	RenderableAspect* renderable = new RenderableAspect(this);
	PhysicsAspect* physics = new PhysicsAspect(this);
	UnitAI* ai = new UnitAI(this);

	// add the aspects
	this->AddAspect(renderable);
	this->AddAspect(physics);
	this->AddAspect(ai);
}

void Entity381::Tick (float dt)
{
	for (int i = 0; i < (int) mAspects->size(); i++)
	{
		mAspects->at(i)->Tick(dt);

	}

	return;

}

void Entity381::ShowAABB (bool state)
{
	mSceneNode->showBoundingBox(state);
}

void Entity381::AddAspect (Aspect* aspect)
{
	mAspects->push_back(aspect);

}

Aspect* Entity381::GetAspect (int index)
{
	return mAspects->at(index);

}

/*
void Entity381::TranslatePosition (Ogre::Vector3* trans)
{
	mPosition->x = mPosition->x + trans->x;
	mPosition->y = mPosition->y + trans->y;
	mPosition->z = mPosition->z + trans->z;

	return;

}
*/

/*
Ogre::Vector3 Entity381::HeaderToDirection()
{
	Ogre::Vector3 direction;

	direction.x = Ogre::Math::Cos(Ogre::Radian(Ogre::Degree(heading)));
	direction.y = 0;
	direction.z = Ogre::Math::Sin(Ogre::Radian(Ogre::Degree(heading)));

	return direction;
}
*/


