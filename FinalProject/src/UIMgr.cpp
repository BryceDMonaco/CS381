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
	mOverlaySystem = new Ogre::OverlaySystem();
	engine->gfxMgr->addQListener(mOverlaySystem);
}

UIMgr::~UIMgr() {

}

void UIMgr::Init() {
	mInputContext.mKeyboard = engine->inputMgr->mKeyboard;
	mInputContext.mMouse = engine->inputMgr->mMouse;
	mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->mWindow, mInputContext, this);
}

void UIMgr::Stop() {

}

void UIMgr::LoadLevel() {
	OgreBites::ProgressBar *pbar;
	pbar = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOMLEFT, "HealthBar", "Health", 300, 200);
	pbar->setProgress(100);
}

void UIMgr::Tick(float dt) {
	mTrayMgr->refreshCursor();
}

void UIMgr::windowResized(Ogre::RenderWindow* rw){

}

void UIMgr::windowClosed(Ogre::RenderWindow* rw){

}
