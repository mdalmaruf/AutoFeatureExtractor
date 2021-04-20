/** 
* The function computes the time differential between the last run and the end
 of call of function.
* This function cannot handle times equal or higher than 1.0 second.
* @param[out]: differential_time time passed from the last call
*/

#include "header.h"
#include <time.h>
																	
double differential_time(void){
	
	static struct timespec last_time_call;
	struct timespec current;
	double differential_time;
	
	clock_gettime( CLOCK_REALTIME, &current);
	if (current.tv_nsec < last_time_call.tv_nsec) {
        last_time_call.tv_nsec = current.tv_nsec;
    }
    if(last_time_call.tv_nsec == 0){
    	last_time_call.tv_nsec = current.tv_nsec;
    }
    differential_time = (current.tv_nsec - last_time_call.tv_nsec)/1000000000.0;
    last_time_call.tv_nsec = current.tv_nsec;

	return differential_time;	
}	