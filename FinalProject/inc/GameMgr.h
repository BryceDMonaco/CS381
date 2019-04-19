#ifndef INC_GAMEMGR_H_
#define INC_GAMEMGR_H_

#include "Mgr.h"

#include <vector>
#include "Entity381.h"
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreVector3.h>
#include <OgreCamera.h>
#include <stdio.h>

class GameMgr : public Mgr
{
public:
	GameMgr (Engine* engine);
	~GameMgr ();

	void LoadLevel ();
	void Tick (float dt);
	void Stop ();

	Ogre::SceneManager* mSceneMgr = nullptr;

};



#endif /* INC_GAMEMGR_H_ */
