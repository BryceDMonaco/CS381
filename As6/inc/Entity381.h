#ifndef INC_ENTITY381_H_
#define INC_ENTITY381_H_

#include <vector>
#include <string>

#include "Aspect.h"
#include "RenderableAspect.h"
#include "PhysicsAspect.h"
#include "RotatorAspect.h"
#include "UnitAI.h"

#include <OgreVector3.h>
#include <OgreSceneManager.h>

class Entity381
{
public:
	Entity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head, bool isSubClass);
	~Entity381 ();

	void Tick (float dt); // The update function
	void SetPosition (Ogre::Vector3* pos);
	void TranslatePosition (Ogre::Vector3* trans);
	void Initialize (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name);  // Call this after a subclass is constructed

	Ogre::Vector3 HeaderToDirection();

	Ogre::Entity* mEntity = nullptr;
	Ogre::SceneNode* mSceneNode = nullptr;
	Ogre::Vector3* mPosition = nullptr;
	Ogre::Vector3* mVelocity = nullptr;
	Ogre::SceneManager* mSceneMgr = nullptr;

	// As3
	int entityID = -1;
	std::string entityName;

	float minSpeed = 0;
	float maxSpeed = 200;
	float speed = 0;  // The current speed, [minSpeed, maxSpeed]
	float desiredSpeed = 0; // The speed to accelerate to
	float acceleration = 5;
	float climbRate = 0;
	float desiredAltitude = 0;
	float altitude = 0;

	float heading = 0;  // [0, 360)
	float desiredHeading = 0;  // The heading to rotate to
	float turnRate = 5;

	std::string meshFileName;

	void AddAspect (Aspect* aspect);

	Aspect* GetAspect (int index);

private:
	std::vector<Aspect*>* aspects;

};

// Kept as an example of a subclass
class SphereEntity381 : public Entity381
{
public:
	SphereEntity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head);
};

class CVN68Entity381 : public Entity381
{
public:
	CVN68Entity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head);
};

class CigBoatEntity381 : public Entity381
{
public:
	CigBoatEntity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head);
};

class DDG51Entity381 : public Entity381
{
public:
	DDG51Entity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head);
};

class SleekEntity381 : public Entity381
{
public:
	SleekEntity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head);
};

class AShipEntity381 : public Entity381
{
public:
	AShipEntity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head);
};

class BansheeEntity381 : public Entity381
{
public:
	BansheeEntity381 (Ogre::SceneManager* manager, RenderableAspect::Types type, std::string name, float head);
};

#endif /* INC_ENTITY381_H_ */
