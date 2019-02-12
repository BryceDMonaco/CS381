#ifndef INC_ENTITYMGR_H_
#define INC_ENTITYMGR_H_

#include <vector>
#include "Entity381.h"

class EntityMgr
{
public:
	void Tick (float dt); // Update all entities in the manager

	void CreateEntity ();
	void DestroyEntity ();

private:
	std::vector<Entity381 *> entities;

};



#endif /* INC_ENTITYMGR_H_ */
