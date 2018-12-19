#include "MKZ/MKZ.h"
#include "definitions.h"

#include <stdio.h>
#include <stdlib.h>


void event_callback(int event_id , void * event_info){

	if (event_id == MKZ_CALLBACK_KEYBOARD){

		MKZ_kb_event * kb = (MKZ_kb_event *) event_info;

		unsigned char key = kb->key;

		switch (key){

			case 'f':
		    case 'F':
		    	char* fname = malloc(sizeof (char)*128);
		    	printf("%s", KG_MSSG_SELECT_FILE);
		    	scanf("%s", fname);

		    	MKZ_mesh * mesh = MKZ_GEOMETRY_load_mesh(fname);

		    	if (mesh == 0){
		    		printf("%s", KG_MSSG_INVALIDFILE);
		    	}
		    	else{
		    		printf("%s", KG_MSSG_FILEREAD);
		    	}
		}


	}
	else if (event_id == MKZ_CALLBACK_SPECIAL_KEYBOARD){
		MKZ_kb_special_event * kb = (MKZ_kb_special_event *) event_info;

		int key = kb->key;


	}
}
