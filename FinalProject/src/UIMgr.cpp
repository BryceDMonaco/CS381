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
	mNewGame = mTrayMgr->createButton(OgreBites::TL_CENTER, "NewGame", "New Game", 200);
	mTrayMgr->createSeparator(OgreBites::TL_CENTER, "menu1Separator", 200);
	mHowTo = mTrayMgr->createButton(OgreBites::TL_CENTER, "Tips", "How to Play", 200);
	mTrayMgr->createSeparator(OgreBites::TL_CENTER, "menu2Separator", 200);
	mQuit = mTrayMgr->createButton(OgreBites::TL_CENTER, "QuitGame", "Quit", 200);
	mTrayMgr->showBackdrop("menu");

	mTrayMgr->showAll();
}

void UIMgr::cleanMenu() {
  mTrayMgr->hideBackdrop();
  
  mTrayMgr->clearTray(OgreBites::TL_CENTER);
}

void UIMgr::ReloadMainMenu()
{
	mTrayMgr->destroyWidget(mProgressBar);
	LoadMainMenu();
}

void UIMgr::LoadLevel() {
	//Hide the MainMenu
	mTrayMgr->hideBackdrop();
	//Destroy the buttons
	mTrayMgr->clearTray(OgreBites::TL_CENTER);

	//These break the program WHYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY
//	mTrayMgr->destroyWidget(mNewGame);
//	mTrayMgr->destroyWidget(mHowTo);
//	mTrayMgr->destroyWidget(mQuit);
}

void UIMgr::LoadLevel() {
//	loaded = true; //Testing purposes

 	mProgressBar = mTrayMgr->createProgressBar(OgreBites::TL_BOTTOMLEFT, "HealthBar", "Health", 300, 200);
	mProgressBar->setProgress(100);

	//Initialize the score label
	mScoreLabel = mTrayMgr->createLabel(OgreBites::TL_TOPRIGHT, "Score", "0", 50);

	std::cout << "Break.\n";
}

void UIMgr::LoadKillScreen() {
	mRestartGame = mTrayMgr->createButton(OgreBites::TL_CENTER, "RestartGame", "Restart", 200);
	mTrayMgr->createSeparator(OgreBites::TL_CENTER, "deadSeparator", 200);
	mMainMenu = mTrayMgr->createButton(OgreBites::TL_CENTER, "ReturnToMenu", "Main Menu", 200);
}

void UIMgr::cleanGame() {
	mTrayMgr->clearAllTrays();
}

void UIMgr::openPauseScreen() {
	mTrayMgr->showBackdrop();
	isPauseScreenOpen = true;
}

void UIMgr::closePauseScreen() {
	mTrayMgr->hideBackdrop();
	isPauseScreenOpen = false;
}

void UIMgr::Tick(float dt) {
	mTrayMgr->refreshCursor();

	//Testing purposes
//	if (loaded) {
//		mScoreLabel->setCaption(std::to_string(score));
//	}
}

void UIMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UIMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UIMgr::mouseMoved(const OIS::MouseEvent &arg){
	std::cout << "moving mouse";
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

bool UIMgr::keyPressed(const OIS::KeyEvent &arg) {

	return true;
}

void UIMgr::buttonHit(OgreBites::Button *b){
	if (b->getName() == "NewGame") {
		std::cout << "Hitting button...\n";
		engine->gameMgr->changeGameState(true);

		//Perform cleanup
		cleanMenu();

		//Load the level
		engine->gameMgr->changeGameState(GameState::LEVEL_ONE);
    
		LoadLevel();
	}

	if (b->getName() == "QuitGame") {
		std::cout << "Exiting game...\n";
		engine->keepRunning = false;
	}

	if (b->getName() == "ReturnToMenu") {
		//Cleanup killscreen UI and game UI
		cleanGame();

		//Load main menu
		LoadMainMenu();
	}

	if (b->getName() == "Tips") {
		//mTrayMgr->hideBackdrop();
		std::cout << "Heres how to play!\n";
		mTrayMgr->showBackdrop("how");

		//Exit tips button
		mExitTips = mTrayMgr->createButton(OgreBites::TL_BOTTOMRIGHT, "exitTips", "Exit", 200);
	}

	if (b->getName() == "exitTips") {
		std::cout << "Exit tips\n";
		mTrayMgr->hideBackdrop();
		mTrayMgr->clearTray(OgreBites::TL_BOTTOMRIGHT);
		mTrayMgr->showBackdrop("menu");
	}
}



