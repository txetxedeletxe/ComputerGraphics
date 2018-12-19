#include <stdio.h>
#include <stdlib.h>

#include "definitions.h"
#include "MKZ/MKZ.h"
#include "io.h"



/** GENERAL INITIALIZATION **/
void initialization (){

    /*Initialization of all the variables with the default values*/
	MKZ_camera * cam = MKZ_SCENE_get_camera();
	cam->polygon_mode = MKZ_POLYGONMODE_WIREFRAME;
	cam->skybox.r = KG_COL_BACK_R;
	cam->skybox.g = KG_COL_BACK_G;
	cam->skybox.b = KG_COL_BACK_B;
	cam->projection_mode = MKZ_PROJECTIONMODE_PERSPECTIVE;

	MKZ_vector3 * v3 = MKZ_GEOMETRY_create_vector3();
	v3->x = 1.0f/(KG_ORTHO_X_MAX_INIT-KG_ORTHO_X_MIN_INIT);
	v3->y = 1.0f/(KG_ORTHO_Y_MAX_INIT-KG_ORTHO_Y_MIN_INIT);
	v3->z = 1.0f/(KG_ORTHO_Z_MAX_INIT-KG_ORTHO_Z_MIN_INIT);

	MKZ_TRANSFORM_set_absolute_scale(cam->obj.transform,v3);

	MKZ_meshedObject * mo1 = MKZ_OBJECT_create_meshedObject();
	MKZ_meshedObject * mo2 = MKZ_OBJECT_create_meshedObject();
	MKZ_mesh * mesh = MKZ_GEOMETRY_load_mesh("resources/abioia.obj");
	mo1->mesh = mesh;
	mo2->mesh = mesh;

	v3->x = 5;
	v3->y = 0;
	v3->z = 0;

	MKZ_TRANSFORM_translate_local(mo1->obj.transform,v3);
	v3->x = -5;
	MKZ_TRANSFORM_translate_local(mo2->obj.transform,v3);

	MKZ_SCENE_add_mesh(mo1);
	MKZ_SCENE_add_mesh(mo2);

	free(v3);

}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {


    MKZ_init();
    MKZ_WM_set_window_size(KG_WINDOW_WIDTH, KG_WINDOW_WIDTH);
    MKZ_WM_set_window_title(KG_WINDOW_TITLE);
    MKZ_create_window();

    MKZ_WM_set_callBack(event_callback);

    initialization();

    MKZ_WM_enter_mainLoop();


    return 0;
}
