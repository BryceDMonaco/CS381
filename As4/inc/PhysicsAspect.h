#ifndef INC_PHYSICSASPECT_H_
#define INC_PHYSICSASPECT_H_

#include <cmath>
#include <math.h>

#include "Aspect.h"

#include <OgreVector3.h>

class PhysicsAspect : public Aspect {
public:
	PhysicsAspect (Entity381* ent, Ogre::Vector3* pos);
	~PhysicsAspect ();

	void SetSpeed (float sentSpeed);
	void SetVelocity (float x, float y, float z);
	void SetVelocity (Ogre::Vector3* vel);
	void Accelerate (Ogre::Vector3* vec);
	void Rotate (float dt);
	Ogre::Vector3* GetVelocity ();

	virtual void Tick (float dt);

private:
	float ClampRotation (float rotation);

	Ogre::Vector3* mPosition;  // Pointer passed from Entity381
	Ogre::Vector3* mVelocity;  // Pointer passed from Entity381

};



#endif /* INC_PHYSICSASPECT_H_ */
