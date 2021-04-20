/**!
* Function responsible for showing the parameters on the screen.
* @param[in] time time passed since the beggining of the program
* @param[in] vehicle structurer containing all vehicle information
* @param[out] fp file to store all vehicle information.
*/ 

#include "header.h"
#include <stdio.h>

void information_display(double time, struct VEHICLE_STATUS* vehicle, FILE* fp){
	fseek(stdout, 0 , SEEK_SET);
	printf("\e[1;1H\e[2J");

	printf("--------Vehicle Simulator-------\n");
	printf("________________________________\n");
	printf("Time: %0.4f\n", time);
	printf("                                \n");
	printf("--------Vehicle Position--------\n");
	printf("________________________________\n");
	printf("Position in X: %0.2f\n", vehicle->vehicle_position_X);
	printf("Position in Y: %0.2f\n", vehicle->vehicle_position_Y);
	printf("                                \n");	
	printf("--------Vehicle Status----------\n");
	printf("________________________________\n");
	printf("Vehicle Angle: 	    	    %0.2f\n", vehicle->vehicle_angle);
	printf("Vehicle Speed: 	    	    %0.2f\n", vehicle->vehicle_speed);
	printf("Gas Pedal Position: 	    %0.2f\n", vehicle->gas_pedal_pos);
	printf("Fuel Actuator Pos: 	    %0.2f\n", vehicle->fuel_actuator_pos);
	printf("Brake Pedal Position: 	    %0.2f\n", vehicle->brake_pedal_pos);
	printf("Brake Actuator Pos: 	    %0.2f\n", vehicle->brake_actuator_pos);
	printf("Steering Wheel Position:    %0.2f\n", vehicle->steering_wheel_pos);
	printf("Direction Actuator Pos:     %0.2f\n", vehicle->direction_actuator_pos);
	printf("Wheel Angle: 	            %0.2f\n", vehicle->vehicle_wheel_angle);
	printf("                                \n");
	
	/* Save Data in .csv */
	fprintf(fp,"%f,", time);
	fprintf(fp,"%f,", vehicle->vehicle_position_X);
	fprintf(fp,"%f,", vehicle->vehicle_position_Y);
	fprintf(fp,"%f,", vehicle->vehicle_angle);
	fprintf(fp,"%f,", vehicle->vehicle_speed);
	fprintf(fp,"%f,", vehicle->gas_pedal_pos);
	fprintf(fp,"%f,", vehicle->fuel_actuator_pos);
	fprintf(fp,"%f,", vehicle->brake_pedal_pos);
	fprintf(fp,"%f,", vehicle->brake_actuator_pos);
	fprintf(fp,"%f,", vehicle->steering_wheel_pos);
	fprintf(fp,"%f,", vehicle->direction_actuator_pos);
	fprintf(fp,"%f\n", vehicle->vehicle_wheel_angle);
}