#include "GameMgr.h"
#include "Engine.h"

#include "EntityMgr.h"

GameMgr::GameMgr (Engine* engine) : Mgr (engine)
{
	srand (time(NULL));

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

	//For main menu
	playGame = false;

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

}

void GameMgr::Tick (float dt)
{


}

void GameMgr::Stop ()
{


}

void GameMgr::changeGameState(bool state) {
	playGame = state;

	if (playGame) {
		LoadLevel1();

		engine->entityMgr->CreateEntityOfType(
				EntityType::PLAYER,
				"Player");
	}
}

void GameMgr::LoadLevel1 ()
{
	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

	// Wall, left
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_OBSTACLE, "obstacle1", "cube.mesh", Ogre::Vector3(-150, 0, -1000), Ogre::Vector3(3, 5, 1), Ogre::Quaternion::IDENTITY, false);

	// Wall, right
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_OBSTACLE, "obstacle2", "cube.mesh", Ogre::Vector3(150, 0, -2000), Ogre::Vector3(3, 5, 1), Ogre::Quaternion::IDENTITY, false);

	// Wall, up
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_OBSTACLE, "obstacle3", "cube.mesh", Ogre::Vector3(0, 150, -3000), Ogre::Vector3(5, 3, 1), Ogre::Quaternion::IDENTITY, false);

	// Wall, down
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_OBSTACLE, "obstacle4", "cube.mesh", Ogre::Vector3(0, -150, -4000), Ogre::Vector3(5, 3, 1), Ogre::Quaternion::IDENTITY, false);

	// Wall, destructible grid
		// Middle row
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_DESTRUCTIBLE, "obstacle5", "cube.mesh", Ogre::Vector3(0, 0, -5000), Ogre::Vector3(2, 2, 0.3f), Ogre::Quaternion::IDENTITY, false);
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_DESTRUCTIBLE, "obstacle6", "cube.mesh", Ogre::Vector3(-225, 0, -5000), Ogre::Vector3(2, 2, 0.3f), Ogre::Quaternion::IDENTITY, false);
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_DESTRUCTIBLE, "obstacle7", "cube.mesh", Ogre::Vector3(225, 0, -5000), Ogre::Vector3(2, 2, 0.3f), Ogre::Quaternion::IDENTITY, false);
		// Top row
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_DESTRUCTIBLE, "obstacle8", "cube.mesh", Ogre::Vector3(0, 225, -5000), Ogre::Vector3(2, 2, 0.3f), Ogre::Quaternion::IDENTITY, false);
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_DESTRUCTIBLE, "obstacle9", "cube.mesh", Ogre::Vector3(-225, 225, -5000), Ogre::Vector3(2, 2, 0.3f), Ogre::Quaternion::IDENTITY, false);
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_DESTRUCTIBLE, "obstacle10", "cube.mesh", Ogre::Vector3(225, 225, -5000), Ogre::Vector3(2, 2, 0.3f), Ogre::Quaternion::IDENTITY, false);
		// Bottom row
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_DESTRUCTIBLE, "obstacle11", "cube.mesh", Ogre::Vector3(0, -225, -5000), Ogre::Vector3(2, 2, 0.3f), Ogre::Quaternion::IDENTITY, false);
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_DESTRUCTIBLE, "obstacle12", "cube.mesh", Ogre::Vector3(-225, -225, -5000), Ogre::Vector3(2, 2, 0.3f), Ogre::Quaternion::IDENTITY, false);
	engine->entityMgr->CreateEntityOfType (EntityType::ENTITY_DESTRUCTIBLE, "obstacle13", "cube.mesh", Ogre::Vector3(225, -225, -5000), Ogre::Vector3(2, 2, 0.3f), Ogre::Quaternion::IDENTITY, false);

	return;

}
