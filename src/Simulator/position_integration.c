/** 
* The function integrates the velocity into position.
* @param[in]: time_sampling differential time for integrating the position 
* @param[in]: *vehicle vehicle angle and velocity
* @param[out]: *vehicle position in (x,y).
*/

#include "header.h"
#include <math.h>

void position_integration(double time_sampling, struct VEHICLE_STATUS* vehicle){	
	
	double del_X;
	double del_Y;
	double angle;
	double velocity;

	angle = vehicle->vehicle_angle;
	velocity = vehicle->vehicle_speed;

	del_X = velocity*cos(angle)*time_sampling;
	del_Y = velocity*sin(angle)*time_sampling;
	vehicle->vehicle_position_X += del_X;
	vehicle->vehicle_position_Y += del_Y;
}