#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity381.h"
#include "EntityMgr.h"
#include "Bullet.h"
#include "CollisionAspect.h"
#include "ShootingAspect.h"

#include <vector>

class Player : public Entity381
{
public:
	Player (
		Ogre::SceneManager* manager,
		EntityMgr* entityMgr,
		int entityId,
		std::string entityName,
		std::string meshFileName = "cube.mesh",
		Ogre::Vector3 position = Ogre::Vector3::ZERO,
		Ogre::Quaternion orientation = Ogre::Quaternion::IDENTITY);
	~Player ();

	void Initialize();
	void Tick(float dt);

	int winTriggerID = 0;

protected:
	void HandleInput();
	void OnCollision(Entity381* collider, float timeSinceLastCollision);

private:
	bool CheckVictory();

	Ogre::Vector3 stationaryPosition;
	bool movingVertical, movingHorizontal;

	ShootingAspect* mShooting;
	float shootInterval;
	float shootTimer;

	float obstacleHitInterval;
	float obstacleHitTimer;

	float mMaxSpeed = 300.0f;

};

#endif /* _PLAYER_H_ */
