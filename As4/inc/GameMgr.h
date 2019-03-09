#ifndef INC_GAMEMGR_H_
#define INC_GAMEMGR_H_

#include "Mgr.h"

class GameMgr : public Mgr
{
public:
	GameMgr (Engine* engine);
	~GameMgr ();

	void Init ();
	void Tick (float dt);
	void Stop ();

};



#endif /* INC_GAMEMGR_H_ */
