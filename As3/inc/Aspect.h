#ifndef INC_ASPECT_H_
#define INC_ASPECT_H_

#include <OgreVector3.h> //Included here since most children of Aspect use it in some way
//#include "Entity381.h"

class Aspect
{
public:
	Aspect ();
	virtual ~Aspect ();

	virtual void Tick (float dt);

private:
	//Entity381* mEntity381 = nullptr;

};




#endif /* INC_ASPECT_H_ */
