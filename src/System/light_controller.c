#include "header.h"

int sidelight(){
return 0;
}

void low_beam_headlamp(){

}

void high_beam_headlamp(){

}
void auto_setlight(){

}


void light_controller(struct VEHICLE_STATUS *vehicle_status){

	sidelight();
	low_beam_headlamp();
        high_beam_headlamp();
        auto_setlight();


}
