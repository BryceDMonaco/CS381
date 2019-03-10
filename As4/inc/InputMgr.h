/*
 * InputMgr.h
 *
 *  Created on: Mar 8, 2019
 *      Author: brycbuntu
 */

#ifndef INC_INPUTMGR_H_
#define INC_INPUTMGR_H_

#include "Mgr.h"

class InputMgr : public Mgr
{
public:
	InputMgr (Engine* engine);
	~InputMgr ();

	void Init ();
	void Tick (float dt);
	void Stop ();

private:

protected:

};
#endif /* INC_INPUTMGR_H_ */
