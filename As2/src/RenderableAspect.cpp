#include "RenderableAspect.h"

RenderableAspect::RenderableAspect (Ogre::Vector3* posVec, Ogre::SceneManager* mgr, Types type, std::string entityName)
{
	mPosition = posVec;
	mName = entityName;
	mSceneMgr = mgr;

	if (type == SPHERE)
	{
		mEntity = mSceneMgr->createEntity("sphere.mesh");


	} else if (type == CUBE)
	{
		mEntity = mSceneMgr->createEntity("cube.mesh");

	}

	mSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName + "Node");
	mSceneNode->attachObject(mEntity);

}

RenderableAspect::RenderableAspect (std::string meshName, Ogre::Vector3* posVector, std::string entityName, Ogre::SceneManager* mgr)
{
	mPosition = posVector;
	mName = entityName;
	mSceneMgr = mgr;

	mEntity = mSceneMgr->createEntity(meshName);

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
