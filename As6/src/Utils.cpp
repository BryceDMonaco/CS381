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
