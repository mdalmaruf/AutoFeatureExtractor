/**
* The function handles the messaging task for the controller;
* In each time is called, it sends a message for a different device;
* The purpose of this task is to ensure that all devices 
* are accessed by the controller. Moreover, this function sends 
* the message for the controller.  
* @param[in] steering_wheel_pos Command to direction actuator with the desired
* position
* @param[in] gas_pedal_pos Command to fuel actuator with the desired position
* @param[in] brake_pedal_pos Command to brake actuator with the desired position
* @param[out] vehicle_status structure containing the comm-bus.
*/
#include "header.h"

int bus_controller(double steering_wheel_pos,
                    double gas_pedal_pos,
                    double brake_pedal_pos, 
                    struct VEHICLE_STATUS *vehicle_status) {
    
    // Variables for bus controlling
    static int device = 0; //Controls which device should be accessed by controller
    device++;
    if (device >= 8) {
        device = 1;
    }
    // Choose device to be accessed
    switch (device) {
        case 1:             
            vehicle_status->Comm_bus_address = GAS_PEDAL_SSR_ADDRESS;
            vehicle_status->Comm_bus_message = 1;
            return GAS_PEDAL_SSR_ADDRESS;
        case 2:
            vehicle_status->Comm_bus_address = BRAKE_PEDAL_SSR_ADDRESS;
            vehicle_status->Comm_bus_message = 1.0;
            return BRAKE_PEDAL_SSR_ADDRESS;
        case 3:            
            vehicle_status->Comm_bus_address = STEERING_SSR_ADDRESS;
            vehicle_status->Comm_bus_message = 1.0;
            return STEERING_SSR_ADDRESS;
        case 4:
            vehicle_status->Comm_bus_address = WHEEL_SSR_ADDRESS;
            vehicle_status->Comm_bus_message = 1.0;
            return WHEEL_SSR_ADDRESS;
        case 5:
            vehicle_status->Comm_bus_address = DIR_ACT_ADDRESS;
            vehicle_status->Comm_bus_message = steering_wheel_pos;
            return DIR_ACT_ADDRESS;
        case 6:
            vehicle_status->Comm_bus_address = FUEL_ACT_ADDRESS;
            vehicle_status->Comm_bus_message = gas_pedal_pos;
            return FUEL_ACT_ADDRESS;
        case 7:
            vehicle_status->Comm_bus_address = BRAKE_ACT_ADDRESS;
            vehicle_status->Comm_bus_message = brake_pedal_pos;
            return BRAKE_ACT_ADDRESS;
    }
    return 1;
}