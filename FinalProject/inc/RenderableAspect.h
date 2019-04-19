#ifndef INC_RENDERABLEASPECT_H_
#define INC_RENDERABLEASPECT_H_

#include "Aspect.h"

#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreQuaternion.h>

#include <string>

class RenderableAspect : public Aspect
{
public:
	RenderableAspect (Entity381* ent);
	~RenderableAspect ();

	void SetMaterial (std::string material);

	virtual void Tick (float dt);
};

#endif /* INC_RENDERABLEASPECT_H_ */
