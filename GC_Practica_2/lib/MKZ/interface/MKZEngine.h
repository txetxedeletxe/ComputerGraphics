#include "Definitions.h"

/* Initialization */
void MKZ_init();
void MKZ_set_callBack(void (*func)(int event,void * state));
void MKZ_enter_mainLoop();

/** window **/
void MKZ_create_window();
void MKZ_set_window_size(int width, int height);
void MKZ_set_window_title(char * title);

/** Scene **/
void MKZ_add_mesh(MKZ_meshedObject * mo);
void MKZ_add_light(MKZ_lightObject * lo);
void MKZ_set_camera(MKZ_camera * ca);

void MKZ_get_mesh(int id);
void MKZ_get_light(int id);
void MKZ_get_camera();

void MKZ_remove_mesh(int id);
void MKZ_remove_light(int id);
void MKZ_restore_camera();

/** draw **/
void MKZ_set_bg_color(MKZ_color3 c3);
void MKZ_set_projectionMode(int PROJECTION_MODE);
void MKZ_set_poligonMode(int PoligonMode);
void MKZ_set_drawMask(unsigned int mask);
void MKZ_draw();

/** Tools **/

/** Objects **/
/** mesh **/
MKZ_meshedObject * MKZ_create_meshedObject(MKZ_mesh * mesh, MKZ_material * mat);
void MKZ_free_meshedObject(MKZ_meshedObject * mo);
/** light **/
MKZ_lightObject * MKZ_create_lightObject(int light_type, float intensity, MKZ_color3 c3);
void MKZ_free_lightObject(MKZ_lightObject * lo);
/** camera **/
MKZ_camera * MKZ_create_camera();
void MKZ_free_camera(MKZ_camera * ca);

/** Geometry **/
MKZ_point3 * MKZ_create_point3(float x, float y, float z);
/** MESH **/
MKZ_mesh * MKZ_create_mesh(MKZ_point3 * vertices, MKZ_face * faces);
MKZ_mesh * MKZ_load_mesh(char * filename);


/** Transforms **/

