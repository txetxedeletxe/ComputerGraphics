#include <stdio.h>
#include "definitions.h"
#include "MKZ/MKZ.h"


/** GENERAL INITIALIZATION **/
void initialization (){

    /*Initialization of all the variables with the default values*/
	MKZ_DRAW_set_renderVolume(KG_ORTHO_X_MIN_INIT, KG_ORTHO_X_MAX_INIT,
			KG_ORTHO_Y_MIN_INIT, KG_ORTHO_Y_MAX_INIT,
			KG_ORTHO_Z_MIN_INIT, KG_ORTHO_Z_MAX_INIT);


	/*
    _frust_x_min = KG_FRUS_X_MIN_INIT;
    _frust_x_max = KG_FRUS_X_MAX_INIT;
    _frust_y_min = KG_FRUS_Y_MIN_INIT;
    _frust_y_max = KG_FRUS_Y_MAX_INIT;
    _frust_z_min = KG_FRUS_Z_MIN_INIT;
    _frust_z_max = KG_FRUS_Z_MAX_INIT;

    _window_ratio = (GLdouble) KG_WINDOW_WIDTH / (GLdouble) KG_WINDOW_HEIGHT;

	 */

    /*Definition of the background color*/
	MKZ_color3 * c3 = MKZ_GEOMETRY_create_color3();
	c3->r = KG_COL_BACK_R;
	c3->g = KG_COL_BACK_G;
	c3->b = KG_COL_BACK_B;

	MKZ_SCENE_set_bg_color(c3);


//    object * cam = create_object();
//    transform_component * trans = (transform_component * ) get_component(cam,COMPONENT_TRANSFORM);
//
//    trans->undoStack->mat[14] = 10;
//
//    cam->next = _first_camera;
//    _first_camera = cam;
//    _selected_camera = cam;
//    _actual_camera = cam;
//
//
//    changeState(KG_TRANSFORM_CAMERA,0);
//    changeState(KG_PROJECT_ORTHO,0);
//    changeState(KG_TRANSFORMATIONS,0);
//    changeState(KG_TRANSFORMATIONS_TRANSLATE,1);
//
//    char def_load[] = "resources/abioia.obj";
//
//    object * obj1 = create_object();
//    object * obj2 = create_object();
//
//
//    obj1->next = _first_object;
//    _first_object = obj1;
//
//    obj2->next = _first_object;
//    _first_object = obj2;
//
//    _selected_object = _first_object;
//
//    updateTransformObject();
//
//    transform_component * tc  = get_component(obj1,COMPONENT_TRANSFORM);
//    tc->undoStack->mat[12] = 2;
//
//    tc = get_component(obj2,COMPONENT_TRANSFORM);
//    tc->undoStack->mat[12] = -2;


}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {


    MKZ_init();
    MKZ_WM_set_window_size(KG_WINDOW_WIDTH, KG_WINDOW_WIDTH);
    MKZ_WM_set_window_title("MKZ window");
    MKZ_create_window();
    MKZ_WM_enter_mainLoop();
    //MKZsetCallback();
    /* this initialization has to be AFTER the creation of the window */
    initialization();


    /* start the main loop */

    return 0;
}
