#include "Engine.h"
#include "InputMgr.h"
#include "EntityMgr.h"

InputMgr::InputMgr (Engine* engine) : Mgr (engine)
{
	cameraOffset = new Ogre::Vector3(Ogre::Vector3::ZERO);
	cameraRot = new Ogre::Vector3(Ogre::Vector3::ZERO);
	accVec = new Ogre::Vector3(Ogre::Vector3::ZERO);

}

InputMgr::~InputMgr ()
{
	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);

}

void InputMgr::Init ()
{
	entityStopped = false;

	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	//mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

}

void InputMgr::Tick (float dt)
{
	mKeyboard->capture();
	mMouse->capture();

	Ogre::SceneNode* camNode = mSceneMgr->getSceneNode("MainCamera");

	// Offset Camera
	camNode->translate((*cameraOffset) * dt * 100, Ogre::Node::TS_LOCAL);
	camNode->pitch (Ogre::Degree(cameraRot->x * 45 * dt));
	camNode->yaw (Ogre::Degree(cameraRot->y * 45 * dt));

	if (!entityStopped)
	{
		// Accelerate selected entity
		engine->entityMgr->AccelerateEntity(engine->entityMgr->GetSelectedEntityIndex(), accVec);

	} else
	{
		(*accVec) = Ogre::Vector3::ZERO;

		engine->entityMgr->SetEntitySpeed(engine->entityMgr->GetSelectedEntityIndex(), 0);

		entityStopped = false;


	}


	// Turn selected entity
	engine->entityMgr->ChangeEntityDesiredHeading(engine->entityMgr->GetSelectedEntityIndex(), turn);

	turn = 0;
	(*accVec) = Ogre::Vector3(Ogre::Vector3::ZERO);

	//(*cameraOffset) = Ogre::Vector3(Ogre::Vector3::ZERO);

}

void InputMgr::Stop ()
{


}

//Adjust mouse clipping area
void InputMgr::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void InputMgr::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if(rw == mWindow)
    {
        if(mInputManager)
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

bool InputMgr::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    return true;
}

bool InputMgr::keyPressed(const OIS::KeyEvent& ke)
{
	// Quit
	if (ke.key == OIS::KC_Q || ke.key == OIS::KC_ESCAPE)
	{
		engine->keepRunning = false;

	}

	// Change the selected entity
	if (ke.key == OIS::KC_TAB)
	{
		(*accVec) = Ogre::Vector3::ZERO;

		engine->entityMgr->IncrementSeclectedIndex();

	}

	if (ke.key == OIS::KC_SPACE)
	{
		(*accVec) = Ogre::Vector3::ZERO;

		engine->entityMgr->SetEntitySpeed(engine->entityMgr->GetSelectedEntityIndex(), 0);

	}

	if (ke.key == OIS::KC_LSHIFT)
	{
		shiftDown = true;

	}

	// Camera Movement
	if (ke.key == OIS::KC_W)
	{
		if (shiftDown)
		{
			cameraRot->x = 1;

		} else
		{
			cameraOffset->z = -1;

		}

	} else if (ke.key == OIS::KC_S)
	{
		if (shiftDown)
		{
			cameraRot->x = -1;

		} else
		{
			cameraOffset->z = 1;

		}

	} else if (ke.key == OIS::KC_A)
	{
		if (shiftDown)
		{
			cameraRot->y = 1;

		} else
		{
			cameraOffset->x += -1;

		}
	} else if (ke.key == OIS::KC_D)
	{
		if (shiftDown)
		{
			cameraRot->y = -1;

		} else
		{
			cameraOffset->x += 1;

		}

	}else if (ke.key == OIS::KC_PGUP)
	{
		cameraOffset->y += 1;

	} else if (ke.key == OIS::KC_PGDOWN)
	{
		cameraOffset->y += -1;

	}

	// Selected Entity Movement
	if (ke.key == OIS::KC_UP)  // Forward
	{
		accVec->x += -1;

	} else if (ke.key == OIS::KC_DOWN)  // Backward
	{
		accVec->x += 1;

	} else if (ke.key == OIS::KC_LEFT)  // Rotate Left
	{
		turn = 5;

	} else if (ke.key == OIS::KC_RIGHT)  // Rotate Right
	{
		turn = -5;

	}

	return true;
}

bool InputMgr::keyReleased(const OIS::KeyEvent& ke)
{
	if (ke.key == OIS::KC_LSHIFT)
	{
		shiftDown = false;

	}

	if (ke.key == OIS::KC_W)
	{
		cameraOffset->z = 0;
		cameraRot->x = 0;

	} else if (ke.key == OIS::KC_S)
	{
		cameraOffset->z = 0;
		cameraRot->x = 0;

	}

	if (ke.key == OIS::KC_A)
	{
		cameraOffset->x += 1;
		cameraRot->y = 0;

	} else if (ke.key == OIS::KC_D)
	{
		cameraOffset->x += -1;
		cameraRot->y = 0;

	}

	if (ke.key == OIS::KC_PGUP)
	{
		cameraOffset->y += -1;

	} else if (ke.key == OIS::KC_PGDOWN)
	{
		cameraOffset->y += 1;

	}

	if (ke.key == OIS::KC_UP)  // Forward
	{
		//accVec->z += 100;

	} else if (ke.key == OIS::KC_DOWN)  // Backward
	{
		//accVec->z += -100;

	} else if (ke.key == OIS::KC_LEFT)  // Rotate Left
	{
		//turn += -1;

	} else if (ke.key == OIS::KC_RIGHT)  // Rotate Right
	{
		//turn += 1;

	}

	return true;
}
