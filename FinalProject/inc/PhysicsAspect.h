#ifndef INC_PHYSICSASPECT_H_
#define INC_PHYSICSASPECT_H_

#include <cmath>
#include <math.h>
#include <iostream>

#include "Aspect.h"
#include "Utils.h"

#include <OgreVector3.h>

class PhysicsAspect : public Aspect {
public:
	PhysicsAspect (Entity381* ent);
	~PhysicsAspect ();

	virtual void Tick (float dt);

};



#endif /* INC_PHYSICSASPECT_H_ */
