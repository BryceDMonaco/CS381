#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity381.h"

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

	void Tick(float dt);

protected:
	void HandleInput();
	void OnCollision(Entity381* collider);

private:

	Ogre::Vector3 stationaryPosition;
	bool movingVertical, movingHorizontal;

};

#endif /* _PLAYER_H_ */
