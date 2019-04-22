/*
 * engine.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 */

#include <Engine.h>
#include <OgreTimer.h>

Engine::Engine(){
	gfxMgr = 0;
	inputMgr = 0;
	entityMgr = 0;
	gameMgr = 0;
	keepRunning = true;

}

Engine::~Engine(){

}

void Engine::Stop(){
	keepRunning = false;
}

void Engine::Init(){
// construct
	gfxMgr    = new GfxMgr(this);
	std::cout << "Constructed GfxMgr" << std::endl;
	inputMgr = new InputMgr(this);
	entityMgr = new EntityMgr(this);
	gameMgr = new GameMgr(this);
	soundMgr = new OgreSND::SoundMgr(this);
// initialize
	gfxMgr->Init();
	inputMgr->Init();
	entityMgr->Init();
	gameMgr->Init();
	soundMgr->Init();
// load level to play
	gfxMgr->LoadLevel();
	inputMgr->LoadLevel();
	entityMgr->LoadLevel();
	gameMgr->LoadLevel();
	soundMgr->LoadLevel();
}

void Engine::TickAll(float dt){
	gfxMgr->Tick(dt);
	inputMgr->Tick(dt);
	entityMgr->Tick(dt);
	gameMgr->Tick(dt);
	soundMgr->Tick(dt);
}

void Engine::Shutdown(){
	inputMgr->Stop();
	gfxMgr->Stop();
	entityMgr->Stop();
	gameMgr->Stop();
}
void Engine::Run(){
	Ogre::Timer* timer = new Ogre::Timer();
	std::cout << "Got ogre timer" << std::endl;
	float oldTime = timer->getMilliseconds()/1000.0f;
	std::cout << "Time: " << oldTime << std::endl;
	float newTime;
	float dt = 0.001f;
	std::cout << "Entering while loop" << std::endl;
	while(keepRunning){
		newTime = timer->getMilliseconds()/1000.0f;
		dt = newTime - oldTime;
		oldTime = newTime;
//		std::cout << "dt: " << dt << std::endl;
		TickAll(dt);
	}
	Shutdown();

	return;
}

void Engine::Cleanup(){
	inputMgr->Stop();
	gfxMgr->Stop();
	entityMgr->Stop();
	gameMgr->Stop();
}