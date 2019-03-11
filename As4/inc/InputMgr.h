/*
 * InputMgr.h
 *
 *  Created on: Mar 8, 2019
 *      Author: brycbuntu
 */

#ifndef INC_INPUTMGR_H_
#define INC_INPUTMGR_H_

#include "Mgr.h"

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreWindowEventUtilities.h>
#include "OgreRenderWindow.h"
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreVector3.h>

class InputMgr : public Mgr, public Ogre::WindowEventListener, public Ogre::FrameListener, public OIS::KeyListener
{
public:
	InputMgr (Engine* engine);
	~InputMgr ();

	void Init ();
	void Tick (float dt);
	void Stop ();

	Ogre::RenderWindow* mWindow;  // Passed by GfxMgr
	Ogre::Root* mRoot;  // Passed by GfxMgr
	Ogre::SceneManager* mSceneMgr;  // Passed by GfxMgr

private:
	OIS::InputManager* mInputManager;
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;

	Ogre::Vector3* cameraOffset;
	Ogre::Vector3* cameraRot;
	Ogre::Vector3* accVec;
	float turn = 0;

	bool shiftDown = false;
	bool entityStopped = false;

protected:
	// Ogre::WindowEventListener
	virtual void windowResized(Ogre::RenderWindow* rw);
	virtual void windowClosed(Ogre::RenderWindow* rw);

	// Ogre::FrameListener
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	// Buffered Input
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);

};
#endif /* INC_INPUTMGR_H_ */
