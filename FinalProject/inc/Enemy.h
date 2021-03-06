/**
 * Class name: Enemy
 * Made by: Alex Kastanek
 * Date: May 9, 2019
 * Description: This is the base enemy class. Two types of
 * 	enemies will inherit from this class. These enemies'
 * 	objectives and capabilities will be different, but they
 * 	will both do damage to the player. One enemy is the
 * 	static enemy which behaves like an obstacle such that
 * 	it simply moves forwards. The other is the
 * 	dynamic enemy which moves towards the player and shoots
 * 	in the direction it faces every shootInterval seconds.
 */

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Entity381.h"
#include "Player.h"
#include "Bullet.h"
#include "ShootingAspect.h"
#include "EnemyAI.h"

class Enemy : public Entity381
{
public:
	Enemy (
		Ogre::SceneManager* manager,
		EntityMgr* entityMgr,
		int entityId,
		std::string entityName,
		std::string meshFileName = "cube.mesh",
		Ogre::Vector3 position = Ogre::Vector3::ZERO,
		Ogre::Quaternion orientation = Ogre::Quaternion::IDENTITY);
	virtual ~Enemy ();

	virtual void Initialize();
	virtual void Tick(float dt);

};

class StaticEnemy : public Enemy
{
public:
	StaticEnemy (
		Ogre::SceneManager* manager,
		EntityMgr* entityMgr,
		int entityId,
		std::string entityName,
		std::string meshFileName = "cube.mesh",
		Ogre::Vector3 position = Ogre::Vector3::ZERO,
		Ogre::Quaternion orientation = Ogre::Quaternion::IDENTITY);
	~StaticEnemy ();

	void Initialize();
	void Tick(float dt);

};

class DynamicEnemy : public Enemy
{
public:
	DynamicEnemy (
		Ogre::SceneManager* manager,
		EntityMgr* entityMgr,
		int entityId,
		std::string entityName,
		std::string meshFileName = "cube.mesh",
		Ogre::Vector3 position = Ogre::Vector3::ZERO,
		Ogre::Quaternion orientation = Ogre::Quaternion::IDENTITY);
	~DynamicEnemy ();

	void Initialize();
	void Tick(float dt);

	void SetPlayer(Player* player);

private:
	Player* mPlayer;

	ShootingAspect* mShooting;
	float shootInterval;
	float shootTimer;

	EnemyAI* mAI;

};

#endif /* _ENEMY_H_ */
