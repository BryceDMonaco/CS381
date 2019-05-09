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
	mTrayMgr = new OgreBites::SdkTrayManager("MenuInterface", engine->gfxMgr->mWindow, mInputContext, this);
	mTipsMgr = new OgreBites::SdkTrayManager("TooltipsInterface", engine->gfxMgr->mWindow, mInputContext, this);
	mGameUIMgr = new OgreBites::SdkTrayManager("GameInterface", engine->gfxMgr->mWindow, mInputContext, this);
	mPauseMgr = new OgreBites::SdkTrayManager("PauseInterface", engine->gfxMgr->mWindow, mInputContext, this);
	mNextLevelMgr = new OgreBites::SdkTrayManager("NextLevelLabel", engine->gfxMgr->mWindow, mInputContext, this);
	mNextLevelMgr->hideCursor();
	mNextLevel = mNextLevelMgr->createLabel(OgreBites::TL_CENTER, "NextLevel", "Next Level!", 200);

}

void UIMgr::Stop() {

}

//This creates and initializes the main menu
void UIMgr::LoadMainMenu() {
	mTrayMgr->showCursor();
	mTipsMgr->showCursor();
	mPauseMgr->showCursor();
	mGameUIMgr->showCursor();

	mTrayMgr->showBackdrop("menu");
	mNewGame = mTrayMgr->createButton(OgreBites::TL_CENTER, "NewGame", "New Game", 200);
	mMenuSeparator = mTrayMgr->createSeparator(OgreBites::TL_CENTER, "menu1separator", 200);
	mHowToPlay = mTrayMgr->createButton(OgreBites::TL_CENTER, "HowToPlay", "How to Play", 200);
	mMenuSeparator2 = mTrayMgr->createSeparator(OgreBites::TL_CENTER, "menu2separator", 200);
	mQuitGame = mTrayMgr->createButton(OgreBites::TL_CENTER, "QuitGame", "Quit", 200);

	mExitTips = mTipsMgr->createButton(OgreBites::TL_BOTTOMRIGHT, "ExitTips", "Return to Main Menu", 200);
	mExitTips->hide();
	mTipsMgr->hideTrays();

	mTrayMgr->showAll();
}

void UIMgr::cleanMenu() {
	mTrayMgr->hideBackdrop();
	mNewGame->hide();
	mHowToPlay->hide();
	mQuitGame->hide();
	mMenuSeparator->hide();
	mMenuSeparator2->hide();
	mTrayMgr->hideTrays();
}

void UIMgr::showMenu() {
	mTrayMgr->showTrays();
	mNewGame->show();
	mMenuSeparator->show();
	mHowToPlay->show();
	mMenuSeparator2->show();
	mQuitGame->show();
	mTrayMgr->showBackdrop("menu");

	mTrayMgr->showCursor();
	mTipsMgr->showCursor();
	mGameUIMgr->showCursor();
	mPauseMgr->showCursor();
}

void UIMgr::LoadPauseScreen() {
	mPauseMgr->showTrays();
	mPauseMgr->showCursor();

	engine->state = engine->EngineState::PAUSED;

	if (!pauseCreated) {
		mResume = mPauseMgr->createButton(OgreBites::TL_CENTER, "ResumePlaying", "Resume Game", 200);
		mPauseSeparator1 = mPauseMgr->createSeparator(OgreBites::TL_CENTER, "pause1separator", 200);
		mReturnToMenu = mPauseMgr->createButton(OgreBites::TL_CENTER, "ReturnToMenu", "Return to Main Menu", 200);
	} else if (pauseCreated) {
		mResume->show();
		mPauseSeparator1->show();
		mReturnToMenu->show();
	}
	pauseCreated = true;
	pauseOpen = true;
}

void UIMgr::ClosePauseScreen() {
	mPauseMgr->hideTrays();
	mResume->hide();
	mPauseSeparator1->hide();
	mReturnToMenu->hide();
	pauseOpen = false;
	mPauseMgr->hideCursor();

	engine->state = engine->EngineState::RUNNING;
}

void UIMgr::LoadLevel() {

	cleanMenu();

	mTrayMgr->hideCursor();
	mTipsMgr->hideCursor();
	mGameUIMgr->hideCursor();
	mPauseMgr->hideCursor();

	gameOpen = true;

	//Now load the UI for the game
	//This creates and initializes, ill have another
	mProgressBar = mGameUIMgr->createProgressBar(OgreBites::TL_BOTTOMLEFT, "HealthBar", "Health", 300, 200);
	mProgressBar->setProgress(100);
	std::cout << "Buttons..\n";
	mScore = mGameUIMgr->createLabel(OgreBites::TL_TOPRIGHT, "Score", "0", 50);
	std::cout << "Break.\n";
}

void UIMgr::hideGameUI() {
	mGameUIMgr->destroyWidget(mProgressBar);
	mGameUIMgr->destroyWidget(mScore);
	gameOpen = false;
}


void UIMgr::Tick(float dt) {
	mTrayMgr->refreshCursor();
	mTipsMgr->refreshCursor();
	mPauseMgr->refreshCursor();
	mGameUIMgr->refreshCursor();

	if (advance) {
		timer += dt;

		mNextLevelMgr->showTrays();
		mNextLevel->show();

		if (timer >= 1)
			advance = false;

	} else {
		timer = 0;
		mNextLevelMgr->hideTrays();
		mNextLevel->hide();
	}
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
    if (mTipsMgr->injectMouseMove(arg)) return true;
    if (mPauseMgr->injectMouseMove(arg)) return true;
    if (mGameUIMgr->injectMouseMove(arg)) return true;
	return false;
}

bool UIMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	std::cout << "mouse clicked" << std::endl;
	if (mTrayMgr->injectMouseDown(me, mid)) return true;
	if (mTipsMgr->injectMouseDown(me, mid)) return true;
	if (mPauseMgr->injectMouseDown(me, mid)) return true;
	if (mGameUIMgr->injectMouseDown(me, mid)) return true;
	return false;
}

bool UIMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    if (mTipsMgr->injectMouseUp(arg, id)) return true;
    if (mPauseMgr->injectMouseUp(arg, id)) return true;
    if (mGameUIMgr->injectMouseUp(arg, id)) return true;
    /* normal mouse processing here... */
	return false;
}

void UIMgr::buttonHit(OgreBites::Button *b){

	//Main Menu stuff
	if (b->getName() == "NewGame") {
		std::cout << "Hitting button...\n";
		engine->gameMgr->changeGameState(GameState::LEVEL_ONE);

		//Clean Menu
		cleanMenu();

		LoadLevel();
	}

	if (b->getName() == "HowToPlay") {
		cleanMenu();

		//Load Tips screen
		mTipsMgr->showBackdrop("tips");
		mTipsMgr->showTrays();
		mExitTips->show();
	}

	if (b->getName() == "ExitTips") {
		mExitTips->hide();
		mTipsMgr->hideBackdrop();
		mTipsMgr->hideTrays();

		showMenu();
	}

	if (b->getName() == "QuitGame") {
		engine->keepRunning = false;
	}

	//Pause Screen Stuff
	if (b->getName() == "ResumePlaying") {
		ClosePauseScreen();
	}

	if (b->getName() == "ReturnToMenu") {
		ClosePauseScreen();
		engine->gameMgr->changeGameState(GameState::GAME_START);
	}

}



