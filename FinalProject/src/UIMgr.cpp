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
	// Initialize the OverlaySystem (changed for Ogre 1.9)
	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);
	mTrayMgr = 0;

	//Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
}

UIMgr::~UIMgr() {

}

void UIMgr::Init() {
	//init sdktrays

	mInputContext.mKeyboard = engine->inputMgr->getKeyboard();
    mInputContext.mMouse = engine->inputMgr->getMouse();
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->getWindow(), mInputContext, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //mTrayMgr->hideCursor();
}

void UIMgr::Stop() {

}

void UIMgr::LoadLevel() {
	OgreBites::ProgressBar * pbar;
	pbar = mTrayMgr->createProgressBar(OgreBites::TL_TOP, "HealthBar", "Health", 300, 200);
	pbar->setProgress(100);
}

void UIMgr::Tick(float dt) {
	mTrayMgr->refreshCursor();
}

void UIMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputMgr->getMouse()->getMouseState();
	// const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UIMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UIMgr::keyPressed(const OIS::KeyEvent &arg) {
	std::cout << "Key Pressed: " << arg.key << std::endl;
	return true;
}
bool UIMgr::keyReleased(const OIS::KeyEvent &arg){
	return true;
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
