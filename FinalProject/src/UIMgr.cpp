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
	Ogre::SceneManager* help = engine->gfxMgr->getSceneMgr();
}

UIMgr::~UIMgr() {

}

void UIMgr::Init() {

}

void UIMgr::Stop() {

}

void UIMgr::LoadLevel() {

}

void UIMgr::Tick(float dt) {

}

void UIMgr::windowResized(Ogre::RenderWindow* rw){

}

void UIMgr::windowClosed(Ogre::RenderWindow* rw){

}

//bool UIMgr::keyPressed(const OIS::KeyEvent &arg) {
//	std::cout << "Key Pressed: " << arg.key << std::endl;
//	return true;
//}
//bool UIMgr::keyReleased(const OIS::KeyEvent &arg){
//	return true;
//}
//bool UIMgr::mouseMoved(const OIS::MouseEvent &arg){
//    if (mTrayMgr->injectMouseMove(arg)) return true;
//	return false;
//}
//bool UIMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
//	std::cout << "mouse clicked" << std::endl;
//	if (mTrayMgr->injectMouseDown(me, mid)) return true;
//	return false;
//}
//bool UIMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
//    if (mTrayMgr->injectMouseUp(arg, id)) return true;
//    /* normal mouse processing here... */
//	return false;
//}
