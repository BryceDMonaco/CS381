#include "ShootingAspect.h"

ShootingAspect::ShootingAspect(Entity381* entity)
{
	mBulletCount = 0;
	mBulletIndex = 0;
}

ShootingAspect::~ShootingAspect()
{
	mBullets.clear();
}

void ShootingAspect::Tick (float dt)
{

}

void ShootingAspect::Fire()
{
	if (mBulletCount > 0)
	{
		// get current bullet
		Bullet* currentBullet = mBullets[mBulletIndex];

		// reset bullet position and fire
		currentBullet->mPosition = mEntity381->mPosition;
		currentBullet->targetPosition = mEntity381->mSceneNode->getOrientation().zAxis() * 50000;

		// set next bullet
		mBulletIndex = mBulletIndex + 1 % mBulletCount;
	}
}
