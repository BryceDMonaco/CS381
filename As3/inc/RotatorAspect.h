#ifndef INC_ROTATORASPECT_H_
#define INC_ROTATORASPECT_H_

#include "Aspect.h"

#include <OgreVector3.h>
#include <OgreSceneNode.h>

class RotatorAspect : public Aspect {
public:
	RotatorAspect (Entity381* ent, Ogre::SceneNode* myNode);
	~RotatorAspect ();

	void SetRotationalVelocity (float x, float y, float z);
	void SetRotationalVelocity (Ogre::Vector3 vel);

	virtual void Tick (float dt);

private:
	Ogre::Vector3 mVelocity = Ogre::Vector3::ZERO;
	Ogre::SceneNode* mSceneNode = nullptr;

};



#endif /* INC_ROTATORASPECT_H_ */
