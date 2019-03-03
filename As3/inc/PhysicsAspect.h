#ifndef INC_PHYSICSASPECT_H_
#define INC_PHYSICSASPECT_H_

#include "Aspect.h"

#include <OgreVector3.h>

class PhysicsAspect : public Aspect {
public:
	PhysicsAspect (Entity381* ent, Ogre::Vector3* pos);
	~PhysicsAspect ();

	void SetVelocity (float x, float y, float z);
	void SetVelocity (Ogre::Vector3* vel);
	Ogre::Vector3* GetVelocity ();

	virtual void Tick (float dt);

private:
	Ogre::Vector3* mPosition;  // Pointer passed from Entity381
	Ogre::Vector3* mVelocity;  // Pointer passed from Entity381

};



#endif /* INC_PHYSICSASPECT_H_ */
