#include "MKZ_Scene.h"
#include "MKZ_WindowManager.h"

/** Initialization **/
void MKZ_init(){
	MKZ_WM_init();
	MKZ_SCENE_init();
}

/** Window **/
void MKZ_create_window(){
	MKZ_WM_create_window();
	MKZ_WM_set_display_function(MKZ_SCENE_draw);
	MKZ_WM_bind_callback();
}

