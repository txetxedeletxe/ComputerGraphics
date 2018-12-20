#ifndef INCLUDE_KG_H_
#define INCLUDE_KG_H_

#include "MKZ/MKZ.h"

#define KG_TRANSFORM_TYPE_TRANSLATE 0
#define KG_TRANSFORM_TYPE_ROTATE 1
#define KG_TRANSFORM_TYPE_SCALE 2

#define KG_TRANSFORM_SCOPE_LOCAL 0
#define KG_TRANSFORM_SCOPE_GLOBAL 1

#define KG_TRANSFORM_TARGET_OBJECT 0
#define KG_TRANSFORM_TARGET_CAMERA 1
#define KG_TRANSFORM_TARGET_LIGHT 2

#define KG_TRANSFORM_AXIS_X 1
#define KG_TRANSFORM_AXIS_Y 2
#define KG_TRANSFORM_AXIS_Z 3

#define KG_CAMERA_PROJECTION_PARALLEL 0
#define KG_CAMERA_PROJECTION_PERSPECTIVE 1

void KG_init();
void KG_set_callback(void (*func)(int event,void * state));
void KG_enter_loop();

int KG_load_object(char * filename);
void KG_select_next_object();
void KG_delete_selected_object();

void KG_create_camera();

void KG_transform_type_set(int t_type);
void KG_transform_scope_set(int t_scope);
void KG_transform_target_set(int t_target);

void KG_transform(int axis);
void KG_uniform_scale(int sense);
void KG_undo_transformation();
void KG_redo_transformation();

void KG_next_camera();
void KG_object_camera();
void KG_camera_camera();
void KG_switch_camera_projection();

void KG_lighting_switch();
void KG_lights_switch(int l_index);
void KG_light_select(int l_index);
void KG_switch_light_type();
void KG_switch_lighting_mode();


/** getters **/

int KG_get_transformation_target();
int KG_get_transformation_scope();
int KG_get_transformation_type();

MKZ_meshedObject * KG_get_selected_object();
MKZ_lightObject * KG_get_selected_light();
MKZ_camera * KG_get_selected_camera();

#endif /* INCLUDE_KG_H_ */
