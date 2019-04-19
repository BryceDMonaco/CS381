/*
 * Engine.h
 *
 *  Created on: Mar 8, 2019
 *      Author: brycbuntu
 */

#ifndef INC_ENGINE_H_
#define INC_ENGINE_H_

class EntityMgr;
class GameMgr;
class GfxMgr;
class InputMgr;

class Engine {
public:
	Engine();
	virtual ~Engine();

	EntityMgr *entityMgr;
	GameMgr   *gameMgr;
	GfxMgr    *gfxMgr;
	InputMgr  *inputMgr;

	void Init();
	void Run();
	void TickAll(float dt);
	void Cleanup();

	bool keepRunning;
};

#endif /* INC_ENGINE_H_ */
