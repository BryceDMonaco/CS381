#ifndef INC_ENTITY381_H_
#define INC_ENTITY381_H_

#include <vector>

#include "Aspect.h"
#include "RenderableAspect.h"
#include "PhysicsAspect.h"
#include "RotatorAspect.h"

#include <OgreVector3.h>
#include <OgreSceneManager.h>

class Entity381
{
public:
	Entity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name);
	~Entity381 ();

	void Tick (float dt); // The update function
	void SetPosition (Ogre::Vector3* pos);
	void TranslatePosition (Ogre::Vector3* trans);

	Ogre::SceneNode* mSceneNode = nullptr;
	Ogre::Vector3* mPosition = nullptr;
	Ogre::SceneManager* mSceneMgr = nullptr;

	void AddAspect (Aspect* aspect);

	Aspect* GetAspect (int index);

private:
	std::vector<Aspect*>* aspects;

};



#endif /* INC_ENTITY381_H_ */
