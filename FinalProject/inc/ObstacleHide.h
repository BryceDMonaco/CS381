#ifndef INC_ObstacleHide_H_
#define INC_ObstacleHide_H_

#include "Aspect.h"

#include <OgreVector3.h>
#include <OgreSceneNode.h>

class ObstacleHide : public Aspect {
public:
	ObstacleHide (Entity381* ent, float val);
	~ObstacleHide ();

	virtual void Tick (float dt);

private:
	float zValue = -10;

};



#endif /* INC_ObstacleHide_H_ */
