/**
* This function acts as an actuator of the vehicle, 
* If the address in the bus match it own address it takes the value from the
* bus message and act on the vehicle status;
* Returns 1 as confirmation to the controller, with controller address in the bus.
* @param[in] vehicle_status structure containing the comm-bus
* @param[out] vehicle_status structure containing the comm-bus; 
*/

#include "header.h"

void fuel_actuator(struct VEHICLE_STATUS *vehicle_status){
	if(vehicle_status->Comm_bus_address == FUEL_ACT_ADDRESS){
		vehicle_status->fuel_actuator_pos = vehicle_status->Comm_bus_message;
		vehicle_status->Comm_bus_message = 1.0;
		vehicle_status->Comm_bus_address = CTRL_ADDRESS;
	}
}