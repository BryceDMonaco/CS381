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
	virtual void Stop();

	OgreBites::InputContext mInputContext;
	OgreBites::SdkTrayManager* mTrayMgr;
	Ogre::OverlaySystem* mOverlaySystem;

};



#endif /* INC_UIMGR_H_ */