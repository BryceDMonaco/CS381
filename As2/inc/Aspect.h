#ifndef INC_ASPECT_H_
#define INC_ASPECT_H_

#include <OgreVector3.h> //Included here since most children of Aspect use it in some way

class Aspect
{
public:
	Aspect ();
	virtual ~Aspect ();

	virtual void Tick (float dt);

private:


};




#endif /* INC_ASPECT_H_ */
