#include "MKZ_Scene.h"
#include "MKZ_WindowManager.h"
#include "MKZ_Definitions.h"
#include "MKZ_Shading.h"

#include <string.h>
#include <stdlib.h>
/** Initialization **/
void MKZ_init(char * resource_dir){

	shader_directory = (char*) malloc(sizeof(char)*200);
	strcpy(shader_directory,resource_dir);
	strcat(shader_directory,"/shaders");

	MKZ_WM_init();
	MKZ_SCENE_init();

}

/** Window **/
void MKZ_create_window(){
	MKZ_WM_create_window();
	MKZ_WM_set_display_function(MKZ_SCENE_draw);
	MKZ_WM_bind_callback();
	//MKZ_SHADING_init();
}

