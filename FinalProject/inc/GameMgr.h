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
#include <stdlib.h>
#include <time.h>

class GameMgr : public Mgr
{
public:
	GameMgr (Engine* engine);
	~GameMgr ();

	void LoadLevel ();
	void Tick (float dt);
	void Stop ();

	void changeGameState(bool state);
	void LoadLevel1 ();

	void GenerateLevelPiece (float zPos);

	Ogre::SceneManager* mSceneMgr = nullptr;
	bool playGame;

};



#endif /* INC_GAMEMGR_H_ */
