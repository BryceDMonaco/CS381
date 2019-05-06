/**
 * Class name: WinTrigger
 * Made by: Alex Kastanek
 * Date: May 5, 2019
 * Description: This is a trigger that checks if the player has won or not
 * 	by approaching the player behind all of the level entities. If this object's
 * 	z position is ever > the player's, the player advances to the next level
 */

#ifndef _WIN_TRIGGER_H_
#define _WIN_TRIGGER_H_

#include "Entity381.h"

class WinTrigger : public Entity381
{
public:
	WinTrigger (
		Ogre::SceneManager* manager,
		EntityMgr* entityMgr,
		int entityId,
		std::string entityName,
		std::string meshFileName = "cube.mesh",
		Ogre::Vector3 position = Ogre::Vector3::ZERO,
		Ogre::Quaternion orientation = Ogre::Quaternion::IDENTITY);
	~WinTrigger ();

	void Initialize();
	void Tick(float dt);

};

#endif /* _WIN_TRIGGER_H_ */
