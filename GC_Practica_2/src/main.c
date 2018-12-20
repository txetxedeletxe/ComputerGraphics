#include <stdio.h>
#include <stdlib.h>

#include "KG.h"
#include "io.h"



/** GENERAL INITIALIZATION **/
void initialization (){


	print_help();
	KG_load_object("resources/abioia.obj");


}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {


	KG_init();

	KG_set_callback(event_callback);

    initialization();

    KG_enter_loop();


    return 0;
}
