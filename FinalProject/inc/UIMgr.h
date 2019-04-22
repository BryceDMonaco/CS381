/*
 * UIMgr.h
 *
 *  Created on: Apr 22, 2019
 *      Author: kevin
 */

#ifndef INC_UIMGR_H_
#define INC_UIMGR_H_

#include <OgreWindowEventUtilities.h>
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <Mgr.h>
#include <string>

#include <SdkTrays.h>

class UIMgr : public Mgr, public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener, public Ogre::WindowEventListener, public OgreBites::SdkTrayListener
{
private:

protected:
	virtual void windowResized(Ogre::RenderWindow *rw);
	virtual void windowClosed(Ogre::RenderWindow *rw);

	virtual bool keyPressed(const OIS::KeyEvent &arg);
	virtual bool keyReleased(const OIS::KeyEvent &arg);
	virtual bool mouseMoved(const OIS::MouseEvent &arg);
	virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

public:
	UIMgr(Engine* engine);
	~UIMgr();
	virtual void Init();
	virtual void Tick(float dt);
	virtual void LoadLevel();
	virtual void Stop();

	OgreBites::InputContext mInputContext;
	OgreBites::SdkTrayManager* mTrayMgr;
	Ogre::OverlaySystem* mOverlaySystem;
	Ogre::SceneManager* mSceneMgr = nullptr;
//	OgreBites::Label *mLabel;
//	OgreBites::Label *infoLabel;
//	OgreBites::Label *infoLabel2;
//	OgreBites::Label *infoLabel3;
};



#endif /* INC_UIMGR_H_ */
