#ifndef INC_GAMEMGR_H_
#define INC_GAMEMGR_H_

#include "Mgr.h"

#include <vector>
#include <string>

#include "Entity381.h"
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreVector3.h>
#include <OgreCamera.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum GameState
{
	GAME_START = 0,
	LEVEL_ONE,
	LEVEL_TWO,
	LEVEL_THREE
};

class GameMgr : public Mgr
{
public:
	GameMgr (Engine* engine);
	~GameMgr ();

	void LoadLevel ();
	void Tick (float dt);
	void Stop ();

	void changeGameState(GameState state);
	void LoadLevel1 ();
	void LoadRandomLevel (int size, float distanceBetweenPieces);

	void GenerateLevelPiece (float zPos, std::string name, int choice);

	Ogre::SceneManager* mSceneMgr = nullptr;
	bool playGame;

};



#endif /* INC_GAMEMGR_H_ */
