/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#include "TutorialApplication.h"
#include "EntityMgr.h"
#include "RenderableAspect.h"

#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

TutorialApplication::TutorialApplication()
{
}

TutorialApplication::~TutorialApplication()
{
}

float surfaceHeight = 0;
int sphereIndex = 0;

EntityMgr* entityMgr = new EntityMgr(nullptr);

void TutorialApplication::createScene()
{
	entityMgr->SetSceneMgr(mSceneMgr);
	entityMgr->CreateAs2Scene();

	mSceneMgr->setSkyBox(true, "Examples/StormySkyBox");

	mCamera->getParentSceneNode()->setPosition(0, 50, 1000); // Just so that the camera does not spawn inside of the sphere
	//mCamera->lookAt(0, 50, 1000);

	//Create the plane
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 10000, 10000, 200, 200, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	Ogre::SceneNode* groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("GroundNode");
	groundNode->attachObject(groundEntity);
	groundNode->setPosition(0, surfaceHeight, 0);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Ocean2_Cg");


	mSceneMgr->setAmbientLight(Ogre::ColourValue(.25, .25, .25));
	//mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

	Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
	pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setPosition(250, 400, 250);
	pointLight->setDiffuseColour(Ogre::ColourValue::White);
	pointLight->setSpecularColour(Ogre::ColourValue::White);

}

bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
  bool ret = BaseApplication::frameRenderingQueued(fe);

  if(!processUnbufferedInput(fe))
    return false;

  entityMgr->Tick(fe.timeSinceLastFrame);

  if (mKeyboard->isKeyDown(OIS::KC_Q)) // Quit nicely
{
	return false;

}

  return ret;
}

bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
	Ogre::Vector3* accVec = new Ogre::Vector3(Ogre::Vector3::ZERO);

	static bool mouseDownLastFrame = false;
	static Ogre::Real toggleTimer = 0.0;
	static Ogre::Real turnTimerL = 0.0;
	static Ogre::Real turnTimerR = 0.0;
	static Ogre::Real speedTimer = 0.0;
	static Ogre::Real rotate = .13;
	static Ogre::Real move = 1;
	static Ogre::Real turnRate = 5;  // Life is much easier when this equals Entity381's turnRate
	float turn = 0;


	toggleTimer -= fe.timeSinceLastFrame;
	turnTimerL -= fe.timeSinceLastFrame;
	turnTimerR -= fe.timeSinceLastFrame;
	speedTimer -= fe.timeSinceLastFrame;


	bool leftMouseDown = mMouse->getMouseState().buttonDown(OIS::MB_Left);

	if (leftMouseDown && !mouseDownLastFrame)
	{
	  Ogre::Light* light = mSceneMgr->getLight("PointLight");
	  light->setVisible(!light->isVisible());

	}

	mouseDownLastFrame = leftMouseDown;

	if ((speedTimer < 0) && mKeyboard->isKeyDown(OIS::KC_UP)) // Forward
	{
		speedTimer = 0.25;

		accVec->x -= move;

	}

	if ((speedTimer < 0) && mKeyboard->isKeyDown(OIS::KC_DOWN)) // Backward
	{
		speedTimer = 0.25;

		accVec->x += move;

	}

	if (mKeyboard->isKeyDown(OIS::KC_PGUP)) // Up
	{
		accVec->y += move;

	}

	if (mKeyboard->isKeyDown(OIS::KC_PGDOWN)) // Down
	{
		accVec->y -= move;

	}

	if ((turnTimerL < 0) && mKeyboard->isKeyDown(OIS::KC_LEFT)) // Left
	{
		turnTimerL = 0.25;

		//accVec->x -= move; Rotate left
		turn += turnRate;


	}

	if ((turnTimerR < 0) && mKeyboard->isKeyDown(OIS::KC_RIGHT)) // Right
	{
		turnTimerR = 0.25;

		//accVec->x += move; Rotate Right
		turn -= turnRate;

	}

	// Set the new desired rotation
	entityMgr->ChangeEntityDesiredHeading(entityMgr->GetSelectedEntityIndex(), turn);


	if (mKeyboard->isKeyDown(OIS::KC_SPACE)) // Stop the motion
	{
		//(*accVec) = Ogre::Vector3::ZERO;
		entityMgr->SetEntityVelocity(entityMgr->GetSelectedEntityIndex(), new Ogre::Vector3(Ogre::Vector3::ZERO));

	} else
	{
		// Apply the velocity vector to the selected sphere
		//mSceneMgr->getSceneNode(SSTR("SphereNode" << sphereIndex))->translate(velocityVec * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
		entityMgr->AccelerateEntity(entityMgr->GetSelectedEntityIndex(), accVec);

	}

	// if tab pressed, switch to the next sphere, switches limited to once every 0.25 seconds
	if ((toggleTimer < 0) && mKeyboard->isKeyDown(OIS::KC_TAB))
	{
		toggleTimer  = 0.25;

		(*accVec) = Ogre::Vector3::ZERO;
		entityMgr->IncrementSeclectedIndex();
		//(*accVec) = *(entityMgr->GetEntityVelocity(entityMgr->GetSelectedEntityIndex()));

	}

	//Ground plane movement
	if (mKeyboard->isKeyDown(OIS::KC_MINUS)) // Down
	{
		surfaceHeight -= 1;

	}

	if (mKeyboard->isKeyDown(OIS::KC_EQUALS)) // Up
	{
		surfaceHeight += 1;

	}

	mSceneMgr->getSceneNode("GroundNode")->setPosition(0, surfaceHeight, 0);

	// Camera Position
	Ogre::Vector3 cameraOffset = Ogre::Vector3::ZERO;
	float cameraSpeed = 250;
	if (mKeyboard->isKeyDown(OIS::KC_W)) // Forward
	{
		if(mKeyboard->isKeyDown(OIS::KC_LSHIFT)) //Rotate up
			mCamera->getParentSceneNode()->pitch(Ogre::Degree(5 * rotate));
		else
			cameraOffset.z -= cameraSpeed;

	}

	if (mKeyboard->isKeyDown(OIS::KC_S)) // Backward
	{
		if(mKeyboard->isKeyDown(OIS::KC_LSHIFT)) //Rotate up
			mCamera->getParentSceneNode()->pitch(Ogre::Degree(-5 * rotate));
		else
			cameraOffset.z += cameraSpeed;

	}

	if (mKeyboard->isKeyDown(OIS::KC_A)) // Left
	{
		if(mKeyboard->isKeyDown(OIS::KC_LSHIFT)) //Rotate CC-wise
			mCamera->getParentSceneNode()->yaw(Ogre::Degree(5 * rotate));
		else
			cameraOffset.x -= cameraSpeed;

	}

	if (mKeyboard->isKeyDown(OIS::KC_D)) // Right
	{
		if(mKeyboard->isKeyDown(OIS::KC_LSHIFT)) //Rotate C-wise
			mCamera->getParentSceneNode()->yaw(Ogre::Degree(-5 * rotate));
		else
			cameraOffset.x += cameraSpeed;

	}

	if (mKeyboard->isKeyDown(OIS::KC_E)) // Up
	{
		cameraOffset.y += cameraSpeed;

	}

	if (mKeyboard->isKeyDown(OIS::KC_F)) // Down
	{
		cameraOffset.y -= cameraSpeed;

	}

	mCamera->getParentSceneNode()->translate(cameraOffset * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	return true;
}

void TutorialApplication::createCamera()
{
	mCamera = mSceneMgr->createCamera("PlayerCam");
	mCamera->setNearClipDistance(5);
	Ogre::SceneNode* camNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MainCamera");
	camNode->attachObject(mCamera);

 }

 void TutorialApplication::createViewports()
{
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	mCamera->setAspectRatio(
	  Ogre::Real(vp->getActualWidth()) /
	  Ogre::Real(vp->getActualHeight()));


 }
//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
