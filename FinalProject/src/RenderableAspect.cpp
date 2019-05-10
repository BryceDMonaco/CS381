#include "RenderableAspect.h"
#include "Entity381.h"

RenderableAspect::RenderableAspect (Entity381* ent) : Aspect (ent)
{

}

RenderableAspect::~RenderableAspect()
{

}

void RenderableAspect::SetMaterial(std::string material)
{
	mEntity381->mEntity->setMaterialName(material);

	return;

}

void RenderableAspect::Tick (float dt)
{
	if (mEntity381->mEntityName == "Player")
			std::cout << "Rendered Position: " << mEntity381->mPosition << std::endl;

	mEntity381->mSceneNode->setPosition(mEntity381->mPosition);
	//mEntity381->mSceneNode->setOrientation(mEntity381->mOrientation);
	//mEntity381->mSceneNode->setOrientation(Ogre::Quaternion(Ogre::Degree(mEntity381->pitchDegree), Ogre::Vector3(1,0,0)));
	//mEntity381->mSceneNode->setOrientation(Ogre::Quaternion(Ogre::Degree(mEntity381->rollDegree), Ogre::Vector3(0,0,1)));

	mEntity381->mSceneNode->setOrientation(EulerToQuaternion(
		mEntity381->pitchDegree,
		mEntity381->yawDegree,
		mEntity381->rollDegree));

}
