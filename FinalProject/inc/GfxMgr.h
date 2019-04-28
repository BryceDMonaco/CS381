#ifndef INC_GFXMGR_H_
#define INC_GFXMGR_H_

#include "Mgr.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include "OgreRenderWindow.h"
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include "OgreViewport.h"
#include <OgreWindowEventUtilities.h>



class GfxMgr : public Mgr
{
public:
	GfxMgr (Engine* engine);
	~GfxMgr ();

	void Init ();
	void Tick (float dt);
	void Stop ();

	Ogre::SceneManager* getSceneMgr();

	Ogre::RenderWindow* getWindow();
	void addQListener(Ogre::OverlaySystem* mOS);

	Ogre::Camera* mCamera;

private:
	Ogre::Root* mRoot;
	Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;

	Ogre::RenderWindow* mWindow;

	Ogre::SceneManager* mSceneMgr;


};



#endif /* INC_GFXMGR_H_ */
