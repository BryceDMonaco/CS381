/**
 * Class name: Bullet
 * Made by: Alex Kastanek
 * Date: May 5, 2019
 * Description: This aspect is used for shooting bullets in the direction
 * 	this entity is facing. It keeps track of how many bullets are left
 * 	and if none are left begins resetting the longest existing bullets.
 */

#ifndef _SHOOTING_ASPECT_H_
#define _SHOOTING_ASPECT_H_

#include "Aspect.h"
#include "Bullet.h"
#include <vector>

class ShootingAspect : public Aspect
{
public:
	ShootingAspect(Entity381* entity);
	~ShootingAspect();

	void Tick (float dt);

	void Fire();

	std::vector<Bullet*> mBullets;
	int mBulletCount;
	int mBulletIndex;
};


#endif /* _SHOOTING_ASPECT_H_ */
