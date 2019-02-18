#ifndef INC_ENTITY381_H_
#define INC_ENTITY381_H_

#include <vector>
#include "Aspect.h"
#include "RenderableAspect.h"
#include "PhysicsAspect.h"
#include <OgreVector3.h>
#include <OgreSceneManager.h>

class Entity381
{
public:
	Entity381 (Ogre::SceneManager* manager);
	~Entity381 ();

	void Tick (float dt); // The update function

	Ogre::Vector3 mPosition = Ogre::Vector3::ZERO;
	Ogre::SceneManager* mSceneMgr = nullptr;

	void AddAspect (Aspect* aspect);

private:
	std::vector<Aspect*>* aspects;

};



#endif /* INC_ENTITY381_H_ */
