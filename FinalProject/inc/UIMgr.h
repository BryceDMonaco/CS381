/*
 * UIMgr.h
 *
 *  Created on: Apr 22, 2019
 *      Author: kevin
 */

#ifndef INC_UIMGR_H_
#define INC_UIMGR_H_

#include <OgreOverlaySystem.h>
#include <OgreWindowEventUtilities.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <Mgr.h>
#include <string>

#include <SdkTrays.h>

class UIMgr : public Mgr, public OgreBites::SdkTrayListener
{
private:

protected:
	virtual void windowResized(Ogre::RenderWindow *rw);
	virtual void windowClosed(Ogre::RenderWindow *rw);


public:
	UIMgr(Engine* engine);
	~UIMgr();
	virtual void Init();
	virtual void Tick(float dt);
	virtual void LoadLevel();
	void LoadMainMenu();
	void cleanMenu();
	void showMenu();
	void hideGameUI();
	void LoadPauseScreen();
	void ClosePauseScreen();
	void deadUI();
	virtual void Stop();

    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    void buttonHit(OgreBites::Button *b);

	OgreBites::InputContext mInputContext;
	OgreBites::SdkTrayManager* mTrayMgr;
	OgreBites::SdkTrayManager* mTipsMgr;
	OgreBites::SdkTrayManager* mGameUIMgr;
	OgreBites::SdkTrayManager* mPauseMgr;
	OgreBites::SdkTrayManager* mNextLevelMgr;
	OgreBites::SdkTrayManager* mDeadMgr;
	Ogre::OverlaySystem* mOverlaySystem;

	//Game UI
	OgreBites::ProgressBar *mProgressBar;
	int currentScore = 0;
	OgreBites::Label *mScore;
	OgreBites::Label *mNextLevel;
	//Pause Screen
	bool 	pauseOpen = false,
			pauseCreated = false,
			gameOpen = false,
			advance = false;
	float	timer;
	OgreBites::Button *mResume;
	OgreBites::Separator *mPauseSeparator1;
	OgreBites::Button *mReturnToMenu;

	//Death screen
	OgreBites::Button *mDeathRestart;
	OgreBites::Separator *mDeathSeparator1;
	OgreBites::Button *mDeathReturnToMenu;

	//Main Menu
	OgreBites::Button *mNewGame;
	OgreBites::Button *mHowToPlay;
	OgreBites::Button *mExitTips;
	bool exitLoaded = false;
	OgreBites::Button *mQuitGame;
	OgreBites::Separator *mMenuSeparator;
	OgreBites::Separator *mMenuSeparator2;
};



#endif /* INC_UIMGR_H_ */
