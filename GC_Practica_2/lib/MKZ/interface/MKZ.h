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
/* global transform */
void MKZ_TRANSFORM_matrix_global(float * modMat, float * transformMat);
void MKZ_TRANSFORM_translate_global(float * tramat, MKZ_vector3 * v3);
void MKZ_TRANSFORM_rotate_global(float * tramat, MKZ_line * axis,  float rads);
void MKZ_TRANSFORM_rotateX_global(float * tramat, float rads);
void MKZ_TRANSFORM_rotateY_global(float * tramat, float rads);
void MKZ_TRANSFORM_rotateZ_global(float * tramat, float rads);
void MKZ_TRANSFORM_scale_global(float * tramat, MKZ_vector3 * along, float scalar);
void MKZ_TRANSFORM_scaleX_global(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleY_global(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleZ_global(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleUniform_global(float * tramat, float scalar);
void MKZ_TRANSFORM_set_position_global(float * modMat, MKZ_point3 * position);

/* local transform */
void MKZ_TRANSFORM_matrix_local(float * modMat, float * transformMat);
void MKZ_TRANSFORM_translate_local(float * tramat, MKZ_vector3 * v3);
void MKZ_TRANSFORM_rotate_local(float * tramat, MKZ_line * axis, float rads);
void MKZ_TRANSFORM_rotateX_local(float * tramat, float rads);
void MKZ_TRANSFORM_rotateY_local(float * tramat, float rads);
void MKZ_TRANSFORM_rotateZ_local(float * tramat, float rads);
void MKZ_TRANSFORM_scale_local(float * tramat, MKZ_vector3 * along, float scalar);
void MKZ_TRANSFORM_scaleX_local(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleY_local(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleZ_local(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleUniform_local(float * tramat, float scalar);

/** Arithmetic **/
float * MKZ_ARITHMETIC_create_matrix();
void MKZ_ARITHMETIC_matMul(float * mat1,float * mat2,float * mat3);
/* matrices */
void MKZ_ARITHMETIC_matrix_identity(float* mat);
void MKZ_ARITHMETIC_matrix_nul(float* mat);
void MKZ_ARITHMETIC_matrix_translate(MKZ_vector3 * v3,float* mat);
void MKZ_ARITHMETIC_matrix_rotate(MKZ_line * axis, float rads,float* mat);
void MKZ_ARITHMETIC_matrix_rotateX(float rads,float* mat);
void MKZ_ARITHMETIC_matrix_rotateY(float rads,float* mat);
void MKZ_ARITHMETIC_matrix_rotateZ(float rads,float* mat);
void MKZ_ARITHMETIC_matrix_scale(MKZ_vector3 * along, float scalar,float* mat);
void MKZ_ARITHMETIC_matrix_scaleX(float scalar,float* mat);
void MKZ_ARITHMETIC_matrix_scaleY(float scalar,float* mat);
void MKZ_ARITHMETIC_matrix_scaleZ(float scalar,float* mat);
void MKZ_ARITHMETIC_matrix_scaleUniform(float scalar,float* mat);
