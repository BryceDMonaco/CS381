/*
 * InputMgr.h
 *
 *  Created on: Mar 8, 2019
 *      Author: brycbuntu
 */

#ifndef INC_INPUTMGR_H_
#define INC_INPUTMGR_H_

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

class InputMgr : public Mgr
{
public:
	InputMgr (Engine* engine);
	~InputMgr ();

	void Init ();
	void Tick (float dt);
	void Stop ();

	OIS::InputManager* mInputManager;
	OIS::Mouse* mMouse;
	OIS::Keyboard* mKeyboard;

private:

};
#endif /* INC_INPUTMGR_H_ */
