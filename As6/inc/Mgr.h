/*
 * Mgr.h
 *
 *  Created on: Mar 8, 2019
 *      Author: brycbuntu
 */

#ifndef INC_MGR_H_
#define INC_MGR_H_

class Engine;

class Mgr {
public:
	Mgr(Engine *engine);
	virtual ~Mgr();

	Engine *engine;

	virtual void Init();
	virtual void LoadLevel();
	virtual void Tick(float dt);
	virtual void Stop();

};

#endif /* INC_MGR_H_ */
