#include "KG.h"
#include "MKZ/MKZ.h"

#include <stdio.h>


void print_info(){
	printf("\n############################Info#########################\n\n");

	printf("-----------------------Transforamciones------------------\n");

	printf("Modo de transformacion: ");
	int target = KG_get_transformation_target();

	MKZ_object * tra_obj;

	switch (target) {
		case KG_TRANSFORM_TARGET_OBJECT:
			printf("Objeto\n");
			tra_obj = (MKZ_object*)((KG_get_selected_object() != 0) ? &(KG_get_selected_object()->obj) : 0);
			break;

		case KG_TRANSFORM_TARGET_CAMERA:
			printf("Camara\n");
			tra_obj = (MKZ_object*)((KG_get_selected_camera() != 0) ? &(KG_get_selected_camera()->obj) : 0);
			break;

		case KG_TRANSFORM_TARGET_LIGHT:
			printf("Light\n");
			tra_obj = (MKZ_object*)((KG_get_selected_light() != 0) ? &(KG_get_selected_light()->obj) : 0);
			break;
	}

	printf("Matriz de transformacion:\n");

	if (tra_obj == 0){
		printf("Objeto vacio.\n");
	}
	else{
		MKZ_ARITHMETIC_print_matrix(tra_obj->transform);
	}


	printf("Tipo de transformacion: ");

	switch (KG_get_transformation_type()){

	case KG_TRANSFORM_TYPE_TRANSLATE:
		printf("Translate");
		break;

	case KG_TRANSFORM_TYPE_ROTATE:
		printf("Rotate");
		break;

	case KG_TRANSFORM_TYPE_SCALE:
		printf("Scale");
		break;


	}

	printf("\n");

	printf("Alcance de transformacion: ");

	if (KG_get_transformation_scope() == KG_TRANSFORM_SCOPE_GLOBAL){
		printf("Global\n");
	}else{
		printf("Local\n");
	}

	printf("---------------------------Camara-----------------------\n");
	printf("Modo de visualizacion:\n");

	/*
	if (checkState(KG_CAMERA_OBJECT)){
		printf("Objeto\n");
	}
	else{
		printf("Camara\n");
	}
	 */


	printf("Matriz de transformacion de la camara:\n");
	MKZ_camera * cam = KG_get_selected_camera();
	MKZ_ARITHMETIC_print_matrix(cam->obj.transform);

	printf("Modo de proyeccion: ");

	if (cam->projection_mode == KG_CAMERA_PROJECTION_PARALLEL){
		printf("Ortho\n");
	}
	else{
		printf("Perspective\n");
	}
	//printf("State value: %d\n",stateField);

}

void print_help(){
    printf("KbG Irakasgaiaren Praktika. Programa honek 3D objektuak \n");
    printf("aldatzen eta bistaratzen ditu.  \n\n");
    printf("\n\n");
    printf("FUNTZIO NAGUSIAK \n");
    printf("<?>\t\t Laguntza hau bistaratu \n");
    printf("<ESC>\t\t Programatik irten \n");
    printf("<F>\t\t Objektua bat kargatu\n");
    printf("<TAB>\t\t Kargaturiko objektuen artean bat hautatu\n");
    printf("<DEL>\t\t Hautatutako objektua ezabatu\n");
    printf("<CTRL + ->\t Bistaratze-eremua handitu\n");
    printf("<CTRL + +>\t Bistaratze-eremua txikitu\n");
    printf("\n\n");
}

void event_callback(int event_id , void * event_info){

	if (event_id == MKZ_CALLBACK_KEYBOARD){

		MKZ_kb_event * kb = (MKZ_kb_event *) event_info;

		char key = kb->key;
		char fname[128];
		//fprintf(stdout,"%d",key);
		switch (key){

			case 'f':
		    case 'F':

		    	printf("%s", "Enter archive path: ");
		    	scanf("%s", fname);
		    	int error = KG_load_object(fname);
		    	if (error != 0){
		    		printf("%s", "Could not read from file\n");
		    	}
		    	else{
		    		printf("%s", "Object successfully read\n");
		    	}

		    	break;


		    case 9: /* TAB*/
		    	KG_select_next_object();
		    	break;

		    case 127: /* SUPR */
		    	KG_delete_selected_object();
		    	break;

		    case 27: /* <ESC> */
				exit(0);
				break;

		    case 26: /* Undo */
		    	KG_undo_transformation();
		    	break;

		    case 25:/* Redo */
		    	KG_redo_transformation();
		    	break;

		    case '?':
		    	print_help();
		        break;

		    case 'H':
		    case 'h':
		    	print_info();
		    	break;

		    /* TRANSFORM TYPE */
		    case 'M':
		    case 'm':
		    	KG_transform_type_set(KG_TRANSFORM_TYPE_TRANSLATE);
		    	break;

		    case 'B':
		    case 'b':
		    	KG_transform_type_set(KG_TRANSFORM_TYPE_ROTATE);
		    	break;

		    case 'T':
			case 't':
				KG_transform_type_set(KG_TRANSFORM_TYPE_SCALE);
				break;

			/* TRANSFORM TARGET */
			case 'O':
			case 'o':
				KG_transform_target_set(KG_TRANSFORM_TARGET_OBJECT);
				break;

			case 'K':
			case 'k':
				KG_transform_target_set(KG_TRANSFORM_TARGET_CAMERA);
				break;

			case 'A':
			case 'a':
				KG_transform_target_set(KG_TRANSFORM_TARGET_LIGHT);
				break;

			/* TRANSFORM SCOPE */
			case 'G':
			case 'g':
				KG_transform_scope_set(KG_TRANSFORM_SCOPE_GLOBAL);
				break;

			case 'L':
			case 'l':
				KG_transform_scope_set(KG_TRANSFORM_SCOPE_LOCAL);
				break;

			case '+':
				KG_uniform_scale(1);
				break;

			case '-':
				KG_uniform_scale(-1);
				break;

			/* SELECT LIGHT */

			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
				KG_light_select(key - '1');
				break;

			case '0':
				KG_switch_light_type();
				break;

			case 'P':
			case 'p':
				KG_switch_camera_projection();
				break;

			case 'C':
		        KG_object_camera();
		        break;

			case 'c':
				KG_next_camera();
				break;

			case 'n':
				KG_create_camera();
				break;

		    case 'Q':
		        KG_camera_camera();
		        break;
		}


	}
	else if (event_id == MKZ_CALLBACK_SPECIAL_KEYBOARD){
		MKZ_kb_special_event * kb = (MKZ_kb_special_event *) event_info;

		int key = kb->key;
		//fprintf(stdout,"%d",key);
		switch (key){

			case MKZ_KEY_RIGHT:
				KG_transform(KG_TRANSFORM_AXIS_X);
				break;

			case MKZ_KEY_LEFT:
				KG_transform(-KG_TRANSFORM_AXIS_X);
				break;

			/* Y - AXIS */
			case MKZ_KEY_UP:
				KG_transform(KG_TRANSFORM_AXIS_Y);
				break;

			case MKZ_KEY_DOWN:
				KG_transform(-KG_TRANSFORM_AXIS_Y);
				break;

			/* Z - AXIS */
			case MKZ_KEY_PAGE_UP:
				KG_transform(KG_TRANSFORM_AXIS_Z);
				break;

			case MKZ_KEY_PAGE_DOWN:
				KG_transform(-KG_TRANSFORM_AXIS_Z);
				break;

			case MKZ_KEY_F9:
				KG_lighting_switch();
				break;

			case MKZ_KEY_F11:
				KG_switch_lighting_mode();
				break;

			case MKZ_KEY_F1:
				KG_lights_switch(0);
				break;

			case MKZ_KEY_F2:
				KG_lights_switch(1);
				break;

			case MKZ_KEY_F3:
				KG_lights_switch(2);
				break;

			case MKZ_KEY_F4:
				KG_lights_switch(3);
				break;

			case MKZ_KEY_F5:
				KG_lights_switch(4);
				break;

			case MKZ_KEY_F6:
				KG_lights_switch(5);
				break;

			case MKZ_KEY_F7:
				KG_lights_switch(6);
				break;

			case MKZ_KEY_F8:
				KG_lights_switch(7);
				break;


		}
	}

	MKZ_WM_draw();
}
