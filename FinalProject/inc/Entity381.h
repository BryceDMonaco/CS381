#ifndef INC_ENTITY381_H_
#define INC_ENTITY381_H_

#include <vector>
#include <string>

#include "Aspect.h"
#include "RenderableAspect.h"
#include "PhysicsAspect.h"
#include "RotatorAspect.h"
#include "UnitAI.h"
#include "ObstacleHide.h"

#include <OgreVector3.h>
#include <OgreSceneManager.h>

class EntityMgr;

class InputMgr;

class Entity381
{
public:
	Entity381 (
		Ogre::SceneManager* manager,
		EntityMgr* entityMgr,
		int entityId,
		std::string entityName,
		std::string meshFileName = "cube.mesh",
		Ogre::Vector3 position = Ogre::Vector3::ZERO,
		Ogre::Quaternion orientation = Ogre::Quaternion::IDENTITY);
	virtual ~Entity381 ();

	void Initialize ();
	virtual void Tick (float dt); // The update function

	void ShowAABB (bool state);

	void AddAspect (Aspect* aspect);

	Aspect* GetAspect (int index);

	//void TranslatePosition (Ogre::Vector3* trans);
	//Ogre::Vector3 HeaderToDirection();

	Ogre::Entity* mEntity = nullptr;
	Ogre::SceneNode* mSceneNode = nullptr;
	Ogre::Vector3 mPosition;
	Ogre::Vector3 mVelocity;
	Ogre::Quaternion mOrientation;
	Ogre::SceneManager* mSceneMgr = nullptr;

	EntityMgr* mEntityMgr;
	int mEntityID;
	std::string mEntityName;
	std::string mMeshFileName;

	Ogre::Vector3 targetPosition = Ogre::Vector3::ZERO;

	Ogre::Vector3 rotation = Ogre::Vector3::ZERO;
	float targetPitch, targetYaw, targetRoll;
	float pitchDegree, yawDegree, rollDegree;

	float mSpeed = 80.0f;
	float mTurnRate = 80.0f;

	int auioId = 1;
	bool didSelectSoundPlay = false;
	std::string soundFile = "";

	InputMgr* inputMgr = nullptr;

protected:
	virtual void HandleInput();

	std::vector<Aspect*>* mAspects;

};

#endif /* INC_ENTITY381_H_ */
