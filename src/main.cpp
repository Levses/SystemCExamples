#include <systemc.h>
#include "helper_fct.h"

int sc_main(int argc, char* argv[]) {

	/* Elaboration step */
	DISPLAY("ELABORATION");

	/* Simulation step */
	DISPLAY("START SIMULATION");

	sc_start(); 

	/* End of Simulation */
	DISPLAY("END OF SIMULATION");
				
	return 0;
}
