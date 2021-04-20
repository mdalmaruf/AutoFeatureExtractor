/**
* The function acts as the controller of the vehicle;
* The controller does not have access to the vehicle's variables, 
* only to the bus; So it should ask actuators and sensors to perform reads and 
* writes in the vehicle_status.
* The main task is to ensure that all the devices can communicate to each other; 
* Other tasks are to check the real-time concerns of the system;
* such as the execution time and health check.
* @param[in] brake_pedal_pos Command to brake actuator with the desired position
* @param[out] vehicle_status structure containing the comm-bus.
*/

#include "header.h"

int bus_controller(double steering_wheel_pos, 
                    double gas_pedal_pos, 
                    double brake_pedal_pos, 
                    struct VEHICLE_STATUS *vehicle_status);

void controller(struct VEHICLE_STATUS *vehicle_status) {
    /* List of system variables that the controller should
    keep track of. These information are provided by the devices.
    */
    static double vehicle_wheel_rotation;
    static double gas_pedal_pos;
    static double brake_pedal_pos;
    static double steering_wheel_pos;
    static double direction_actuator_pos;
    static double fuel_actuator_pos;
    static double brake_actuator_pos;
    //double range_sensor_val;
    //double vision_system_val;

    /* Variables for system controlling */
    static int last_bus_address;
    static int activity;
 
    /* Variable for bus reading/writing */
    float Comm_bus_message;
    Comm_bus_message = vehicle_status->Comm_bus_message;
    
    /* Treat information and store in the controller's memory */
    if (vehicle_status->Comm_bus_address == CTRL_ADDRESS) {
        switch (last_bus_address) {
        case GAS_PEDAL_SSR_ADDRESS:
            gas_pedal_pos = Comm_bus_message;
            break;
        case BRAKE_PEDAL_SSR_ADDRESS:
            brake_pedal_pos = Comm_bus_message;
            break;
        case STEERING_SSR_ADDRESS:
            steering_wheel_pos = Comm_bus_message;
            break;
        case WHEEL_SSR_ADDRESS:
            vehicle_wheel_rotation = Comm_bus_message;
            break;
        case DIR_ACT_ADDRESS:
            direction_actuator_pos = steering_wheel_pos;
            break;
        case FUEL_ACT_ADDRESS:
            fuel_actuator_pos = gas_pedal_pos;
            break;
        case BRAKE_ACT_ADDRESS:
            brake_actuator_pos = brake_pedal_pos;
            break;
        }
    }

    /* Send Commands to devices */
    
    last_bus_address = bus_controller(steering_wheel_pos,
                                      gas_pedal_pos,
                                      brake_pedal_pos, 
                                      vehicle_status);
	
    //watchdog_checker(); - release 2
    //health_checker(); - release 2
       
}