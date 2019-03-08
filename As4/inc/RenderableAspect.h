#ifndef INC_RENDERABLEASPECT_H_
#define INC_RENDERABLEASPECT_H_

#include "Aspect.h"

#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreQuaternion.h>

#include <string>

class RenderableAspect : public Aspect
{
public:
	enum Types {SPHERE, CUBE, OTHER};

	RenderableAspect (Entity381* ent, Ogre::Vector3* posVec, Ogre::SceneManager* mgr, Types type, std::string entityName);
	//RenderableAspect (std::string meshName, Ogre::Vector3* posVec, std::string entityName, Ogre::SceneManager* mgr); //Used for setting a CUSTOM object mesh
	~RenderableAspect ();

	void SetMaterial (std::string material);

	virtual void Tick (float dt);

	Ogre::SceneNode* GetSceneNode ();

	void ShowAABB (bool state);

private:
	Ogre::Entity* mEntity = nullptr;
	Ogre::SceneNode* mSceneNode = nullptr;
	Ogre::Vector3* mPosition = nullptr;
	Ogre::SceneManager* mSceneMgr = nullptr;
	std::string mName;

};

#endif /* INC_RENDERABLEASPECT_H_ */
