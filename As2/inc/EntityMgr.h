#ifndef INC_ENTITYMGR_H_
#define INC_ENTITYMGR_H_

#include <vector>
#include "Entity381.h"
#include <OgreSceneManager.h>
#include <OgreVector3.h>

class EntityMgr
{
public:
	EntityMgr (Ogre::SceneManager* mgr);
	~EntityMgr ();

	void Tick (float dt); // Update all entities in the manager

	void CreateAs2Scene (); // Creates the scene as required for As2, see implementation for more info

	void CreateEntity(RenderableAspect::Types type, std::string name, Ogre::Vector3* pos);
	void DestroyEntity ();

	bool SetSceneMgr (Ogre::SceneManager* mgr); //Should only be called once

private:
	std::vector<Entity381 *>* entities = nullptr;
	Ogre::SceneManager* mSceneMgr = nullptr;

};



#endif /* INC_ENTITYMGR_H_ */
