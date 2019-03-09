#ifndef INC_GFXMGR_H_
#define INC_GFXMGR_H_

#include "Mgr.h"

// Included in Tutorial 6
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreWindowEventUtilities.h>

class GfxMgr : public Mgr
{
public:
	GfxMgr (Engine* engine);
	~GfxMgr ();

	void Init ();
	void Tick (float dt);
	void Stop ();

	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;
	Ogre::RenderWindow* mWindow;

private:
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

};



#endif /* INC_GFXMGR_H_ */
