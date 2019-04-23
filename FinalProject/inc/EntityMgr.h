#ifndef INC_ENTITYMGR_H_
#define INC_ENTITYMGR_H_

#include "Mgr.h"

#include <deque>
#include "Entity381.h"
#include "Command.h"
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreVector3.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum EntityType
{
	ENTITY_DEFAULT, ENTITY_OBSTACLE, ENTITY_DESTRUCTIBLE
};

class EntityMgr : public Mgr
{
public:
	EntityMgr (Engine* engine);
	EntityMgr (Ogre::SceneManager* mgr, Engine* engine);
	~EntityMgr ();

	void Tick (float dt); // Update all entities in the manager

	void CreateEntityOfType(
		EntityType type,
		std::string name,
		std::string meshFileName = "cube.mesh",
		Ogre::Vector3 position = Ogre::Vector3::ZERO,
		Ogre::Vector3 scale = Ogre::Vector3::UNIT_SCALE,
		Ogre::Quaternion orientation = Ogre::Quaternion::IDENTITY,
		bool showAabb = false);
	void DestroyEntity (int entityIndex);

	void IncrementSelectedID (); //Index will loop back to 0

	Entity381* GetSelectedEntity ();
	std::map<int, Entity381*>* GetEntities ();
	int GetSelectedEntityID ();

	bool SetSceneMgr (Ogre::SceneManager* mgr); //Should only be called once
	void SetSelectedEntityID (int id);

	/*
	void ChangeEntityDesiredHeading (int index, float deltaDH);
	void SetEntitySpeed (int index, float sentSpeed);
	void SetEntityVelocity (int index, Ogre::Vector3* vel);
	void AccelerateEntity (int index, Ogre::Vector3* vec);
	void IncreaseEntityHeight (int index, float amount);
	Ogre::Vector3* GetEntityVelocity (int index);
	*/

	Ogre::SceneManager* mSceneMgr = nullptr;

private:
	std::map<int, Entity381*>* mEntities;
	int mSelectedEntityID;
	int mNextEntityID;

};



#endif /* INC_ENTITYMGR_H_ */
