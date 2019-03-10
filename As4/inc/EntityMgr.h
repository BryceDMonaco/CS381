#ifndef INC_ENTITYMGR_H_
#define INC_ENTITYMGR_H_

#include "Mgr.h"

#include <vector>
#include "Entity381.h"
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreVector3.h>
#include <stdio.h>

#include "RenderableAspect.h" //Used to toggle bounding box

class EntityMgr : public Mgr
{
public:
	EntityMgr (Engine* engine);
	EntityMgr (Ogre::SceneManager* mgr, Engine* engine);
	~EntityMgr ();

	void Tick (float dt); // Update all entities in the manager

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

	Ogre::SceneManager* mSceneMgr = nullptr;

private:
	std::vector<Entity381 *>* entities = nullptr;
	int selectedEntityIndex = 0;

};



#endif /* INC_ENTITYMGR_H_ */
