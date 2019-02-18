#ifndef INC_ENTITYMGR_H_
#define INC_ENTITYMGR_H_

#include <vector>
#include "Entity381.h"
#include <OgreSceneManager.h>

class EntityMgr
{
public:
	EntityMgr (Ogre::SceneManager* mgr);
	~EntityMgr ();

	void Tick (float dt); // Update all entities in the manager

	void CreateEntity ();
	void DestroyEntity ();

private:
	std::vector<Entity381 *>* entities;
	Ogre::SceneManager* mSceneMgr;

};



#endif /* INC_ENTITYMGR_H_ */
