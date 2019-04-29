/*
 * UIMgr.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: kevin
 */

#include <UIMgr.h>
#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>

UIMgr::UIMgr(Engine* eng) : Mgr(eng) {
	//mOverlaySystem = new Ogre::OverlaySystem();
	//engine->gfxMgr->addQListener(mOverlaySystem);
}

UIMgr::~UIMgr() {

}

void UIMgr::Init() {
	mOverlaySystem = engine->gfxMgr->mOverlaySystem;
	engine->gfxMgr->addQListener(mOverlaySystem);

	mInputContext.mKeyboard = engine->inputMgr->mKeyboard;
	mInputContext.mMouse = engine->inputMgr->mMouse;
	mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->mWindow, mInputContext, this);
}

void UIMgr::Stop() {

}

void UIMgr::LoadMainMenu() {
	mTrayMgr->showCursor();
	mTrayMgr->createButton(OgreBites::TL_CENTER, "NewGame", "New Game", 100);
	mTrayMgr->showBackdrop("menu");

	mTrayMgr->showAll();
}

void UIMgr::LoadLevel() {
	mProgressBar = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOMLEFT, "HealthBar", "Health", 300, 200);
	mProgressBar->setProgress(100);
	std::cout << "Break.\n";
}

void UIMgr::Tick(float dt) {
	mTrayMgr->refreshCursor();
}

void UIMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UIMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UIMgr::mouseMoved(const OIS::MouseEvent &arg){
    if (mTrayMgr->injectMouseMove(arg)) return true;
	return false;
}

bool UIMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	std::cout << "mouse clicked" << std::endl;
	if (mTrayMgr->injectMouseDown(me, mid)) return true;
	return false;
}

bool UIMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    /* normal mouse processing here... */
	return false;
}

void UIMgr::buttonHit(OgreBites::Button *b){
	std::cout << "Buttons..\n";
	if (b->getName() == "NewGame") {
		std::cout << "Hitting button...\n";
		engine->gameMgr->changeGameState(true);
		LoadLevel();
	}
}



