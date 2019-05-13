#ifndef INC_GAMEMGR_H_
#define INC_GAMEMGR_H_

#include "Mgr.h"

#include <vector>
#include <string>

#include "Entity381.h"
#include "Player.h"
#include "WinTrigger.h"
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
	LEVEL_THREE,
	RANDOM
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
	void NextLevel();
	void LoadLevel1 ();
	void LoadRandomLevel (int size, float distanceBetweenPieces);

	void SpawnEnemy (float zPos, std::string name, int choice, float offset);
	void GenerateLevelPiece (float zPos, std::string name, int choice);

	Ogre::SceneManager* mSceneMgr = nullptr;
	GameState currentState;
	bool playGame;
	int obstacleIndex = 0;
	int enemyIndex = 0;

	Player* player;
	WinTrigger* winTrigger = nullptr;
	int winTriggerID = 0;
	bool exists = false;

	int maxDistanceBetweenPieces = 1000;
	int minDistanceBetweenPieces = 500;
	int currentDistanceBetweenPieces = maxDistanceBetweenPieces;

};



#endif /* INC_GAMEMGR_H_ */
