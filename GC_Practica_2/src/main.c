#include <stdio.h>
#include <GL/gl.h>
#include "display.h"
#include "io.h"
#include "definitions.h"
#include "load_obj.h"
#include "MKZEngine.h"
#include "WindowManager.h"

/** GENERAL INITIALIZATION **/
void initialization (){

    /*Initialization of all the variables with the default values*/
    _ortho_x_min = KG_ORTHO_X_MIN_INIT;
    _ortho_x_max = KG_ORTHO_X_MAX_INIT;
    _ortho_y_min = KG_ORTHO_Y_MIN_INIT;
    _ortho_y_max = KG_ORTHO_Y_MAX_INIT;
    _ortho_z_min = KG_ORTHO_Z_MIN_INIT;
    _ortho_z_max = KG_ORTHO_Z_MAX_INIT;

    _frust_x_min = KG_FRUS_X_MIN_INIT;
    _frust_x_max = KG_FRUS_X_MAX_INIT;
    _frust_y_min = KG_FRUS_Y_MIN_INIT;
    _frust_y_max = KG_FRUS_Y_MAX_INIT;
    _frust_z_min = KG_FRUS_Z_MIN_INIT;
    _frust_z_max = KG_FRUS_Z_MAX_INIT;

    _window_ratio = (GLdouble) KG_WINDOW_WIDTH / (GLdouble) KG_WINDOW_HEIGHT;

    /*Definition of the background color*/
    glClearColor(KG_COL_BACK_R, KG_COL_BACK_G, KG_COL_BACK_B, KG_COL_BACK_A);

    /*Definition of the method to draw the objects*/
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    object * cam = create_object();
    transform_component * trans = (transform_component * ) get_component(cam,COMPONENT_TRANSFORM);

    trans->undoStack->mat[14] = 10;

    cam->next = _first_camera;
    _first_camera = cam;
    _selected_camera = cam;
    _actual_camera = cam;


    changeState(KG_TRANSFORM_CAMERA,0);
    changeState(KG_PROJECT_ORTHO,0);
    changeState(KG_TRANSFORMATIONS,0);
    changeState(KG_TRANSFORMATIONS_TRANSLATE,1);

    char def_load[] = "resources/abioia.obj";

    object * obj1 = create_object();
    object * obj2 = create_object();

    object3d * mesh = (object3d*) malloc(sizeof(object3d));

    read_wavefront(def_load,mesh);

    component * c1 = create_component(COMPONENT_MESH,mesh);
    component * c2 = create_component(COMPONENT_MESH,mesh);

    add_component(obj1,c1);
    add_component(obj2,c2);

    obj1->next = _first_object;
    _first_object = obj1;

    obj2->next = _first_object;
    _first_object = obj2;

    _selected_object = _first_object;

    updateTransformObject();

    transform_component * tc  = get_component(obj1,COMPONENT_TRANSFORM);
    tc->undoStack->mat[12] = 2;

    tc = get_component(obj2,COMPONENT_TRANSFORM);
    tc->undoStack->mat[12] = -2;


}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {

    /*First of all, print the help information*/
    print_help();

    MKZinit();
    WMsetWindowTitle(KG_WINDOW_TITLE);
    MKZcreateWindow(KG_WINDOW_WIDTH,KG_WINDOW_HEIGHT);

    //MKZsetCallback();
    /* this initialization has to be AFTER the creation of the window */
    initialization();


    /* start the main loop */
    MKZenterMainLoop();
    return 0;
}
