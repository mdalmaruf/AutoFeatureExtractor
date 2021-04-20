/**
* This function acts as a sensor of the vehicle, 
* If the address in the bus match it own address it takes the value from the 
* vehicle status and it pass to the bus message, addressing the controller 
* in the bus address.
* @param[in] vehicle_status structure containing the comm-bus
* @param[out] vehicle_status structure containing the comm-bus. 
*/

#include "header.h"

void brake_pedal_sensor(struct VEHICLE_STATUS *vehicle_status){
	if(vehicle_status->Comm_bus_address == BRAKE_PEDAL_SSR_ADDRESS){
		vehicle_status->Comm_bus_message = vehicle_status->brake_pedal_pos;
		vehicle_status->Comm_bus_address = CTRL_ADDRESS;
	}
}