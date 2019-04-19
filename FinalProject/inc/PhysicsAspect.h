#ifndef INC_PHYSICSASPECT_H_
#define INC_PHYSICSASPECT_H_

#include <cmath>
#include <math.h>

#include "Aspect.h"

#include <OgreVector3.h>

class PhysicsAspect : public Aspect {
public:
	PhysicsAspect (Entity381* ent);
	~PhysicsAspect ();

	//void Accelerate (Ogre::Vector3 vec);
	//void Rotate (float dt);

	virtual void Tick (float dt);

};



#endif /* INC_PHYSICSASPECT_H_ */
