#include <stdio.h>
#include <math.h>
#include <time.h>
//#include <sys/time.h>

// Bus Addresses:
#define   CTRL_ADDRESS    	    	10001010
#define   GAS_PEDAL_SSR_ADDRESS		10000001
#define   BRAKE_PEDAL_SSR_ADDRESS	10000010
#define   STEERING_SSR_ADDRESS    	10000011
#define   WHEEL_SSR_ADDRESS         10000100
#define   DIR_ACT_ADDRESS			10000101
#define   FUEL_ACT_ADDRESS			10000110
#define   BRAKE_ACT_ADDRESS			10000111

#ifndef PI 
#define PI 3.14159265358979323846
#endif

struct VEHICLE_STATUS {
    double vehicle_wheel_angle;
    double vehicle_wheel_rotation;
    double vehicle_position_X;
    double vehicle_position_Y;
    double vehicle_angle;
    double vehicle_speed;
    double gas_pedal_pos;
    double brake_pedal_pos;
    double steering_wheel_pos;
    double direction_actuator_pos;
    double fuel_actuator_pos;
    double brake_actuator_pos;
    double range_sensor_val;
    double vision_system_val;

	int Comm_bus_address;
    float Comm_bus_message;
};