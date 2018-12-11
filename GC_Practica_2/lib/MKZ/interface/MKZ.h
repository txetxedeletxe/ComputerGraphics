#include "MKZ_Objects.h"
#include "MKZ_Definitions.h"

/**				FUNCTIONS 				**/
/* INITIALIZATION */
void MKZ_init();
void MKZ_create_window();

/** WINDOW **/
void MKZ_WM_set_window_size(int width, int height);
void MKZ_WM_set_window_title(char * title);
void MKZ_WM_set_callBack(void (*func)(int event,void * state));
void MKZ_WM_enter_mainLoop();
void MKZ_WM_draw();

/** SCENE **/
void MKZ_SCENE_add_mesh(MKZ_meshedObject * mo);
void MKZ_SCENE_add_light(MKZ_lightObject * lo);
void MKZ_SCENE_set_camera(MKZ_camera * ca);

MKZ_meshedObject *  MKZ_SCENE_get_mesh(int id);
MKZ_lightObject * MKZ_SCENE_get_light(int id);
MKZ_camera * MKZ_SCENE_get_camera();

void MKZ_SCENE_remove_mesh(int id);
void MKZ_SCENE_remove_light(int id);
void MKZ_SCENE_restore_camera();

void MKZ_SCENE_set_bg_color(MKZ_color3 * c3);
void MKZ_SCENE_set_projectionMode(int PROJECTION_MODE);
void MKZ_SCENE_set_poligonMode(int PoligonMode);

MKZ_color3 * MKZ_SCENE_get_bg_color();
int MKZ_SCENE_get_projectionMode();
int MKZ_SCENE_get_poligonMode();

void MKZ_SCENE_restore_bg_color();

/** DRAW CONTROL**/
void MKZ_DRAW_enable_drawMask(unsigned int d_mask);
void MKZ_DRAW_disable_drawMask(unsigned int d_mask);
/** TOOLS **/

/** Transforms **/
/* matrices */
float * MKZ_matrix_identity();
float * MKZ_matrix_null();
float * MKZ_matrix_translate(MKZ_vector3 * v3);
float * MKZ_matrix_rotate(MKZ_line * axis, float rads);
float * MKZ_matrix_rotateX( float rads);
float * MKZ_matrix_rotateY( float rads);
float * MKZ_matrix_rotateZ( float rads);
float * MKZ_matrix_scale(MKZ_vector3 * along, float scalar);
float * MKZ_matrix_scaleX(float scalar);
float * MKZ_matrix_scaleY(float scalar);
float * MKZ_matrix_scaleZ(float scalar);
float * MKZ_matrix_scaleUniform(float scalar);

/* local transform */
void MKZ_transform_matrix_global(float * modMat, float * transformMat);
void MKZ_transform_translate_global(float * tramat, MKZ_vector3 * v3);
void MKZ_transform_rotate_global(float * tramat, MKZ_line * axis,  float rads);
void MKZ_transform_rotateX_global(float * tramat, float rads);
void MKZ_transform_rotateY_global(float * tramat, float rads);
void MKZ_transform_rotateZ_global(float * tramat, float rads);
void MKZ_transform_scale_global(float * tramat, MKZ_vector3 * along, float scalar);
void MKZ_transform_scaleX_global(float * tramat, float scalar);
void MKZ_transform_scaleY_global(float * tramat, float scalar);
void MKZ_transform_scaleZ_global(float * tramat, float scalar);
void MKZ_transform_scaleUniform_global(float * tramat, float scalar);

/* global transform */
void MKZ_transform_matrix_local(float * modMat, float * transformMat);
void MKZ_transform_translate_local(float * tramat, MKZ_vector3 * v3);
void MKZ_transform_rotate_local(float * tramat, MKZ_line * axis, float rads);
void MKZ_transform_rotateX_local(float * tramat, float rads);
void MKZ_transform_rotateY_local(float * tramat, float rads);
void MKZ_transform_rotateZ_local(float * tramat, float rads);
void MKZ_transform_scale_local(float * tramat, MKZ_vector3 * along, float scalar);
void MKZ_transform_scaleX_local(float * tramat, float scalar);
void MKZ_transform_scaleY_local(float * tramat, float scalar);
void MKZ_transform_scaleZ_local(float * tramat, float scalar);
void MKZ_transform_scaleUniform_local(float * tramat, float scalar);

/** Arithmetic **/
float * MKZ_matrix_multiply(float * mat_left, float * mat_right);
