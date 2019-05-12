#include "ShootingAspect.h"

ShootingAspect::ShootingAspect(Entity381* entity) : Aspect(entity)
{
	mBulletCount = 0;
	mBulletIndex = 0;
	mLocalShotDirection = Ogre::Vector3::NEGATIVE_UNIT_Z;
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
		currentBullet->targetPosition =
			(mEntity381->mSceneNode->getOrientation() * mLocalShotDirection * 5000) + mEntity381->mSceneNode->getPosition();
		currentBullet->isFired = true;

		// set next bullet
		mBulletIndex = (mBulletIndex + 1) % mBulletCount;
	}
}
