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
	mEntity381->mSceneNode->setPosition(mEntity381->mPosition);
	mEntity381->mSceneNode->setOrientation(mEntity381->mOrientation);
}
