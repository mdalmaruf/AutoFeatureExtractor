#include "header.h"
#include "main.h"
#include <string.h>
#include <stdio.h>

void simulator(FILE *trjc, struct VEHICLE_STATUS *vehicle_status, FILE *fp){

    static double total_time = 0;
    double time_sampling;
    time_sampling = differential_time();
    total_time += time_sampling;

    vehicle_velocity(time_sampling, vehicle_status);
    vehicle_angle(time_sampling, vehicle_status);
    position_integration(time_sampling, vehicle_status);

    /* Input time sampling = 0.01;
    To match the input sampling time with the current time, 
    the new input should be called only
    once per time sampling = 0.01.
    */
    static int k = 0;
    if (total_time >= 0.01*((double)k)){
        driver_attitude(0.01, total_time, trjc, vehicle_status);
        if (k%100 == 0){
            information_display(total_time, vehicle_status, fp); 
        }
        k++;
    }
}

void system(struct VEHICLE_STATUS *vehicle_status) {
    controller(vehicle_status);
    gas_pedal_sensor(vehicle_status);
    brake_pedal_sensor(vehicle_status);
    steering_wheel_sensor(vehicle_status);
    wheel_sensor(vehicle_status);
    direction_actuator(vehicle_status);
    fuel_actuator(vehicle_status);
    brake_actuator(vehicle_status);
    //range_sensor(vehicle_status); release 3
    //vision_sensor(vehicle_status); release 3
}
    
int main(void)
{
    VEHICLE_STATUS *vehicle;
    vehicle = (struct VEHICLE_STATUS*) malloc(sizeof(struct VEHICLE_STATUS));
   
    // Open Trajectory
    FILE *trjc;
    trjc = fopen("data/Trajectory.csv","r");
    if (trjc == NULL){
        printf("Could not open file %s","data/Trajectory.csv");
        return 1;
    }

    // Open Log file
    FILE *fp;
    fp = fopen("data/log.csv", "w");
    if (fp == NULL){
        printf("Could not open file %s","log.csv");
        return 1;
    }

    /* Printing the header of the result in .csv*/
    fprintf(fp,"Time,X,Y,V_angle,V_speed,Gas_pedal,Fuel_act,Brake_pedal,Brake_act,Steering_wheel,Direction_act,Wheel_angle\n");

    char line[60];
    fgets(line,60,trjc); // Remove header from csv

    do{
        system(vehicle);
        simulator(trjc, vehicle, fp);
    }while(!feof(trjc));
    
    fclose(fp);
    fclose(trjc);
    free(vehicle);
    printf("End of Simulation\nPress any key to finish\n");
    getchar();
}