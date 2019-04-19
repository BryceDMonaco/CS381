#include "GameMgr.h"
#include "Engine.h"

#include "EntityMgr.h"

GameMgr::GameMgr (Engine* engine) : Mgr (engine)
{


}

GameMgr::~GameMgr ()
{
	engine = nullptr;

}

void GameMgr::LoadLevel ()
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(.5, .5, .5));

	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20, 80, 50);

	Ogre::SceneNode* camNode = mSceneMgr->getSceneNode("MainCamera");

	// Offset Camera
	//camNode->translate((*cameraOffset) * dt * 100, Ogre::Node::TS_LOCAL);
	//if (camNode->getPosition().y <= 5)
	//	camNode->setPosition(camNode->getPosition().x, 5, camNode->getPosition().z);
	//camNode->pitch (Ogre::Degree(cameraRot->x * 45 * dt));
	//camNode->yaw (Ogre::Degree(cameraRot->y * 45 * dt));

	/*
	for (int i = 0; i < 6; i ++)
	{
		engine->entityMgr->CreateEntityOfTypeAtPositionAndHeading (i, std::to_string(i), new Ogre::Vector3(500 * i, 0, 0), 45 * i);

	}

	mSceneMgr->setSkyBox(true, "Examples/StormySkyBox");

	//Create the plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 10000, 10000, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	Ogre::SceneNode* groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GroundNode");
	groundNode->attachObject(groundEntity);
	groundNode->setPosition(0, 0, 0);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Ocean2_Cg");
	*/

	engine->entityMgr->CreateEntityOfType(
		EntityType::ENTITY_DEFAULT,
		"Player");


}

void GameMgr::Tick (float dt)
{


}

void GameMgr::Stop ()
{


}
