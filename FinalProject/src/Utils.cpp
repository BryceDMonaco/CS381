/*
 * Utils.cpp
 *
 *  Created on: Apr 8, 2019
 *      Author: alex
 */

#include <Utils.h>

float FixAngle(float angle){
	if(angle < 0)
		return angle + 360;
	else if (angle > 360)
		return angle - 360;
	return angle;
}

float Clamp(float min, float max, float val){
	if(val < min){
		return min;
	} else if (val > max){
		return max;
	}
	return val;
}

Ogre::Quaternion EulerToQuaternion(float pitch, float yaw, float roll)
{
	Ogre::Quaternion output = Ogre::Quaternion::IDENTITY;

	Ogre::Degree pitchDegree = Ogre::Degree(pitch);
	Ogre::Degree yawDegree = Ogre::Degree(yaw);
	Ogre::Degree rollDegree = Ogre::Degree(roll);

	float cosine1 = Ogre::Math::Cos(yawDegree.valueRadians() / 2);
	float cosine2 = Ogre::Math::Cos(rollDegree.valueRadians() / 2);
	float cosine3 = Ogre::Math::Cos(pitchDegree.valueRadians() / 2);
	float sine1 = Ogre::Math::Sin(yawDegree.valueRadians() / 2);
	float sine2 = Ogre::Math::Sin(rollDegree.valueRadians() / 2);
	float sine3 = Ogre::Math::Sin(pitchDegree.valueRadians() / 2);

	output.w = cosine1 * cosine2 * cosine3 - sine1 * sine2 * sine3;
	output.x = sine1 * sine2 * cosine3 + cosine1 * cosine2 * sine3;
	output.y = sine1 * cosine2 * cosine3 + cosine1 * sine2 * sine3;
	output.z = cosine1 * sine2 * cosine3 - sine1 * cosine2 * sine3;

	return output;
}

double PercentDiff (double v1, double v2)
{
	double diff = v1 - v2;
	(diff < 0) ? diff *= -1 : diff *= 1; //cmath.abs was returning an int, using this instead

	return 100.0 * (diff) / ((v1 + v2) / 2);

}
