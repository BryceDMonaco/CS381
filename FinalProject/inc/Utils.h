/*
 * Utils.h
 *
 *  Created on: Apr 8, 2019
 *      Author: alex
 */

#ifndef INC_UTILS_H_
#define INC_UTILS_H_

#include <OgreQuaternion.h>
#include <cmath>

float FixAngle(float angle);
float Clamp(float min, float max, float val);

Ogre::Quaternion EulerToQuaternion(float pitch, float yaw, float roll);

double PercentDiff (double v1, double v2);

#endif /* INC_UTILS_H_ */
