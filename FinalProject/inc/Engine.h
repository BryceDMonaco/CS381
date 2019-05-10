/*
 * engine.h
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <SoundMgr.h>
#include <UIMgr.h>

class Engine {
private:
public:
	Engine();
	~Engine();

	enum EngineState {
		RUNNING,
		PAUSED,
	};

	EntityMgr*      	entityMgr;
	GfxMgr*         	gfxMgr;
	InputMgr*       	inputMgr;
	GameMgr*        	gameMgr;
	OgreSND::SoundMgr*	soundMgr;
	UIMgr* 				uiMgr;
	//SelectionMgr* selectionMgr;
	//ControlMgr*   controlMgr;

	void Init();
	void Run();
	void TickAll(float dt);
	void Stop();
	void Shutdown();
	void Cleanup();

	//
	bool keepRunning;
	int state = EngineState::RUNNING;
};



#endif /* ENGINE_H_ */
