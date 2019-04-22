#include "Engine.h"
#include "GfxMgr.h"
#include "InputMgr.h"
#include "EntityMgr.h"
#include "GameMgr.h"

GfxMgr::GfxMgr (Engine* engine) : Mgr (engine),
mRoot(0),
mResourcesCfg(Ogre::StringUtil::BLANK),
mPluginsCfg(Ogre::StringUtil::BLANK)
{


}

GfxMgr::~GfxMgr ()
{
	delete mRoot;

}

void GfxMgr::Init ()
{
	mResourcesCfg = "resources.cfg";
	mPluginsCfg = "plugins.cfg";

	mRoot = new Ogre::Root(mPluginsCfg);

	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	Ogre::String name, locType;

	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

	while (secIt.hasMoreElements())
	{
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;

		for (it = settings->begin(); it != settings->end(); ++it)
		{
			locType = it->first;
			name = it->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);

		}


	}

	if(!(mRoot->restoreConfig() || mRoot->showConfigDialog()))
	{
		engine->keepRunning = false;

	}

	mWindow = mRoot->initialise(true, "TutorialApplication Render Window");

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Ogre::LogManager::getSingletonPtr()->logMessage("*** All Resource Groups Init'd ***");

	mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

	mCamera = mSceneMgr->createCamera("MainCam");
	Ogre::SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MainCamera");
	camNode->attachObject(mCamera);

	camNode->setPosition(0, 50, 1000);
	mCamera->lookAt(0, 0, -300);
	mCamera->setNearClipDistance(5);

	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

	mCamera->setAspectRatio(
	  Ogre::Real(vp->getActualWidth()) /
	  Ogre::Real(vp->getActualHeight()));

	Ogre::LogManager::getSingletonPtr()->logMessage("*** Camera Set ***");

	engine->entityMgr->mSceneMgr = mSceneMgr;
	engine->inputMgr->mWindow = mWindow;
	engine->inputMgr->mRoot = mRoot;
	engine->inputMgr->mSceneMgr = mSceneMgr;
	engine->gameMgr->mSceneMgr = mSceneMgr;

	Ogre::LogManager::getSingletonPtr()->logMessage("*** GfxMgr Init Done! ***");


}

void GfxMgr::Tick (float dt)
{
	Ogre::WindowEventUtilities::messagePump();

	if(mWindow->isClosed())
	{
		engine->keepRunning = false;

	}

	if(!mRoot->renderOneFrame())
	{
		engine->keepRunning = false;

	}

}

void GfxMgr::Stop ()
{


}
