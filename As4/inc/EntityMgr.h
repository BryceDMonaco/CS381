#ifndef INC_ENTITYMGR_H_
#define INC_ENTITYMGR_H_

#include <vector>
#include "Entity381.h"
#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <stdio.h>

#include "RenderableAspect.h" //Used to toggle bounding box

class EntityMgr
{
public:
	EntityMgr (Ogre::SceneManager* mgr);
	~EntityMgr ();

	void Tick (float dt); // Update all entities in the manager

	void CreateAs2Scene (); // Creates the scene as required for As2, see implementation for more info

	void CreateEntityOfTypeAtPositionAndHeading(int entity381Type, std::string name, Ogre::Vector3* pos, float heading);
	void DestroyEntity ();

	bool SetSceneMgr (Ogre::SceneManager* mgr); //Should only be called once

	Entity381* GetSelectedEntity ();
	void IncrementSeclectedIndex (); //Index will loop back to 0

	void ChangeEntityDesiredHeading (int index, float deltaDH);
	void SetEntityVelocity (int index, Ogre::Vector3* vel);
	void AccelerateEntity (int index, Ogre::Vector3* vec);
	Ogre::Vector3* GetEntityVelocity (int index);

	int GetSelectedEntityIndex ();

private:
	std::vector<Entity381 *>* entities = nullptr;
	Ogre::SceneManager* mSceneMgr = nullptr;
	int selectedEntityIndex = 0;

};



#endif /* INC_ENTITYMGR_H_ */
