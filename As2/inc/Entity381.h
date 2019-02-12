#ifndef INC_ENTITY381_H_
#define INC_ENTITY381_H_

#include <vector>
#include "Aspect.h"

class Entity381
{
public:
	Entity381 ();
	~Entity381 ();

	void Tick (float dt); // The update function

private:
	std::vector<Aspect*> aspects;

};



#endif /* INC_ENTITY381_H_ */
