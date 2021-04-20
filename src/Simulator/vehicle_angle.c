/** 
* The function computes the angle of a vehicle in relation to a reference 
* frame.
* @param[in]: time_sampling differential time for computing the integral
* @param[in]: *vehicle vehicle wheel angle and speed from the vehicle information
* @param[out]: *vehicle vehicle wheel angle updated
*/

#include "header.h"

#ifndef BODY_FACTOR
#define BODY_FACTOR 2.0
#endif

void vehicle_angle(double time_sampling, struct VEHICLE_STATUS* vehicle){
	vehicle->vehicle_wheel_angle = vehicle->direction_actuator_pos*(PI/200);
	vehicle->vehicle_angle += vehicle->vehicle_wheel_angle*vehicle->vehicle_speed*
														BODY_FACTOR*time_sampling;
	/* limits -PI to PI */
	if(vehicle->vehicle_angle>PI){
		vehicle->vehicle_angle -= 2*PI;
	} 	
	if(vehicle->vehicle_angle<(-PI)){
		vehicle->vehicle_angle += 2*PI;
	}
}
	