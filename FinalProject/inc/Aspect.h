#ifndef INC_ASPECT_H_
#define INC_ASPECT_H_

#include "Utils.h"
#include <OgreVector3.h> //Included here since most children of Aspect use it in some way
//#include "Entity381.h"

class Entity381;  // Forward reference

class Aspect
{
public:
	Aspect (Entity381* ent);
	virtual ~Aspect ();

	virtual void Tick (float dt);

	Entity381* mEntity381 = nullptr;

private:

};




#endif /* INC_ASPECT_H_ */
