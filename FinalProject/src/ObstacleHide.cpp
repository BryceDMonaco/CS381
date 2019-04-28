#include "ObstacleHide.h"
#include "Entity381.h"

ObstacleHide::ObstacleHide (Entity381* ent, float val) : Aspect (ent)
{
	zValue = val;

}

ObstacleHide::~ObstacleHide ()
{
	mEntity381 = nullptr;

}

void ObstacleHide::Tick (float dt)
{
	if (mEntity381->mPosition.z >= zValue)
	{
		mEntity381->mSceneNode->setScale(0, 0, 0);

	}

	return;

}
