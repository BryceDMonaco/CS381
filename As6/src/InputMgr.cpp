#include "Engine.h"
#include "InputMgr.h"
#include "GfxMgr.h"
#include "EntityMgr.h"
#include <OgreCamera.h>
#include "RenderableAspect.h"

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

	#if defined OIS_WIN32_PLATFORM
    	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
    	pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
    	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
    	pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
    #elif defined OIS_LINUX_PLATFORM
    	pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
    	pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
    	pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
    	pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
    #endif

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

	//Set initial mouse clipping size
	windowResized(mWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mRoot->addFrameListener(this);

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

}

void InputMgr::Tick (float dt)
{
	mKeyboard->capture();
	mMouse->capture();

	Ogre::SceneNode* camNode = mSceneMgr->getSceneNode("MainCamera");

	// Offset Camera
	camNode->translate((*cameraOffset) * dt * 100, Ogre::Node::TS_LOCAL);
	if (camNode->getPosition().y <= 5)
		camNode->setPosition(camNode->getPosition().x, 5, camNode->getPosition().z);
	camNode->pitch (Ogre::Degree(cameraRot->x * 45 * dt));
	camNode->yaw (Ogre::Degree(cameraRot->y * 45 * dt));

	if (!entityStopped)
	{
		// Accelerate selected entity
		engine->entityMgr->AccelerateEntity(engine->entityMgr->GetSelectedEntityIndex(), accVec);
		engine->entityMgr->IncreaseEntityHeight(engine->entityMgr->GetSelectedEntityIndex(), height);
	} else
	{
		(*accVec) = Ogre::Vector3::ZERO;

		engine->entityMgr->SetEntitySpeed(engine->entityMgr->GetSelectedEntityIndex(), 0);

		entityStopped = false;


	}


	// Turn selected entity
	engine->entityMgr->ChangeEntityDesiredHeading(engine->entityMgr->GetSelectedEntityIndex(), turn);

	turn = 0;
	height = 0;
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
	if (ke.key == OIS::KC_ESCAPE)
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
			cameraOffset->z = -3;

		} else
		{
			cameraOffset->z = -1;

		}

	} else if (ke.key == OIS::KC_S)
	{
		if (shiftDown)
		{
			cameraOffset->z = 3;

		} else
		{
			cameraOffset->z = 1;

		}

	} else if (ke.key == OIS::KC_A)
	{
		if (shiftDown)
		{
			cameraOffset->x += -3;

		} else
		{
			cameraOffset->x += -1;

		}
	} else if (ke.key == OIS::KC_D)
	{
		if (shiftDown)
		{
			cameraOffset->x += 3;

		} else
		{
			cameraOffset->x += 1;

		}

	}else if (ke.key == OIS::KC_R)
	{
		if (shiftDown)
			cameraOffset->y = 3;
		else
			cameraOffset->y = 1;

	} else if (ke.key == OIS::KC_F)
	{
		if (shiftDown)
			cameraOffset->y = -3;
		else
			cameraOffset->y = -1;
	} else if (ke.key == OIS::KC_Z)
	{
		if (shiftDown)
			cameraRot->x = 3;
		else
			cameraRot->x = 1;
	} else if (ke.key == OIS::KC_X)
	{
		if (shiftDown)
			cameraRot->x = -3;
		else
			cameraRot->x = -1;
	}
	else if (ke.key == OIS::KC_Q)
	{
		if (shiftDown)
			cameraRot->y = 3;
		else
			cameraRot->y = 1;
	} else if (ke.key == OIS::KC_E)
	{
		if (shiftDown)
			cameraRot->y = -3;
		else
			cameraRot->y = -1;
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

	} else if (ke.key == OIS::KC_PGDOWN)  // Go Down
	{
		height = -50;

	} else if (ke.key == OIS::KC_PGUP)  // Go Up
	{
		height = 50;

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

	} else if (ke.key == OIS::KC_S)
	{
		cameraOffset->z = 0;

	}

	if (ke.key == OIS::KC_A)
	{
		cameraOffset->x = 0;

	} else if (ke.key == OIS::KC_D)
	{
		cameraOffset->x = 0;

	}

	if (ke.key == OIS::KC_R)
	{
		cameraOffset->y = 0;

	} else if (ke.key == OIS::KC_F)
	{
		cameraOffset->y = 0;

	}

	if (ke.key == OIS::KC_Z)
	{
		cameraRot->x = 0;
	}
	else if (ke.key == OIS::KC_X)
	{
		cameraRot->x = 0;
	}

	if (ke.key == OIS::KC_Q)
	{
		cameraRot->y = 0;
	}
	else if (ke.key == OIS::KC_E)
	{
		cameraRot->y = 0;
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

bool InputMgr::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	const OIS::MouseState &ms = mMouse->getMouseState();

	if (id == OIS::MB_Left)
	{
		std::vector<Entity381 *>* entities = engine->entityMgr->GetEntities();

		Ogre::Ray ray = engine->gfxMgr->mCamera->getCameraToViewportRay(ms.X.abs / (float) ms.width, ms.Y.abs/ (float) ms.height);

		for (unsigned int i = 0; i < entities->size(); i++)
		{
			RenderableAspect* renderer = (RenderableAspect*) entities->at(i)->GetAspect(0);

			std::pair<bool, float> test = ray.intersects(renderer->mSceneNode->_getWorldAABB());

			if (test.first) //Ray hit the entity's AABB
			{
				engine->entityMgr->SetSelectedIndex(i);

			}

		}

	}

	if (id == OIS::MB_Right)
	{
		Ogre::Vector3 targetPos;

		std::vector<Entity381 *>* entities = engine->entityMgr->GetEntities();

		UnitAI* ai = (UnitAI*) engine->entityMgr->GetSelectedEntity()->GetAspect(2);

		Ogre::Ray ray = engine->gfxMgr->mCamera->getCameraToViewportRay(ms.X.abs / (float) ms.width, ms.Y.abs/ (float) ms.height);

		std::pair<bool, float> planeTest = ray.intersects(Ogre::Plane(Ogre::Vector3::UNIT_Y, 0));

		bool clickedOnEntity = false;
		int entityIndex;
		for (unsigned int i = 0; i < entities->size(); i++)
		{
			RenderableAspect* renderer = (RenderableAspect*) entities->at(i)->GetAspect(0);

			std::pair<bool, float> entityTest = ray.intersects(renderer->mSceneNode->_getWorldAABB());

			if (entityTest.first) //Ray hit the entity's AABB
			{
				clickedOnEntity = true;
				entityIndex = i;
				break;
			}
		}

		if (clickedOnEntity)
		{
			Intercept* cmd = new Intercept(engine->entityMgr->GetSelectedEntity(), entities->at(entityIndex));
			cmd->init();
			if (shiftDown)
				ai->AddCommand(cmd);
			else
				ai->SetCommand(cmd);
		}
		else if (planeTest.first)
		{
			targetPos = ray.getPoint(planeTest.second);

			MoveTo* cmd = new MoveTo(engine->entityMgr->GetSelectedEntity(), targetPos);
			cmd->init();
			if (shiftDown)
				ai->AddCommand(cmd);
			else
				ai->SetCommand(cmd);
		}
	}

	return true;
}

bool InputMgr::mouseMoved(const OIS::MouseEvent& me)
{
	return true;
}

bool InputMgr::mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID mid)
{
	return true;
}

