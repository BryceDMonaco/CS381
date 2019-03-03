#include "RenderableAspect.h"
#include "Entity381.h"

RenderableAspect::RenderableAspect (Entity381* ent, Ogre::Vector3* posVec, Ogre::SceneManager* mgr, Types type, std::string entityName) : Aspect (ent)
{
	mPosition = posVec;
	mName = entityName;
	mSceneMgr = mgr;

	if (type == SPHERE)
	{
		mEntity = mSceneMgr->createEntity(mEntity381->meshFileName);


	} else if (type == CUBE)
	{
		mEntity = mSceneMgr->createEntity("cube.mesh");

	}

	mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName + "Node");
	mSceneNode->attachObject(mEntity);

}

RenderableAspect::~RenderableAspect()
{
	mPosition = nullptr;
	mSceneMgr = nullptr;
	mEntity = nullptr;
	mSceneNode = nullptr;

}

void RenderableAspect::SetMaterial(std::string material)
{
	mEntity->setMaterialName(material);

	return;

}

void RenderableAspect::Tick (float dt)
{
	mSceneNode->setPosition(*mPosition);

}

Ogre::SceneNode* RenderableAspect::GetSceneNode ()
{
	return mSceneNode;

}

void RenderableAspect::ShowAABB (bool state)
{
	mSceneNode->showBoundingBox(state);

}
