#ifndef _COLLISION_APSECT_H_
#define _COLLISION_APSECT_H_

#include <vector>
#include <map>
#include "Aspect.h"

class CollisionAspect : public Aspect
{
public:
	CollisionAspect(Entity381* entity);
	~CollisionAspect();

	virtual void Tick(float dt);

protected:
	bool CheckCollisions();

	std::vector<Entity381*> mCollisions;
	float mCollisionRadius;
	float mCollisionTimer;
};

#endif /* _COLLISION_APSECT_H_ */
