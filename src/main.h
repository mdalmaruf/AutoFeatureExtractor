//#include <cstdio>
void controller(struct VEHICLE_STATUS *vehicle_status);
void gas_pedal_sensor(struct VEHICLE_STATUS *vehicle_status);
void brake_pedal_sensor(struct VEHICLE_STATUS *vehicle_status);
void steering_wheel_sensor(struct VEHICLE_STATUS *vehicle_status);
void wheel_sensor(struct VEHICLE_STATUS *vehicle_status);
void direction_actuator(struct VEHICLE_STATUS *vehicle_status);
void fuel_actuator(struct VEHICLE_STATUS *vehicle_status);
void brake_actuator(struct VEHICLE_STATUS *vehicle_status);
    //range_sensor(vehicle_status); release 3
    //vision_sensor(vehicle_status); release 3

double differential_time(void);
void vehicle_angle(double time_sampling, struct VEHICLE_STATUS* vehicle);
void vehicle_velocity(double time_sampling, struct VEHICLE_STATUS* vehicle);
void position_integration(double time_sampling, struct VEHICLE_STATUS* vehicle);
void driver_attitude(double time_sampling,
					double total_time,
                    FILE *trjc,
                    struct VEHICLE_STATUS *vehicle_status);
    // environment_status(vehicle_status); release 3
void information_display(double time, struct VEHICLE_STATUS* vehicle, FILE* fp);

