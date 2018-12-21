#ifndef __MKZ_SCENE_IMPORTED__
#define __MKZ_SCENE_IMPORTED__

#include "MKZ_Objects.h"
#include "MKZ_Draw.h"
/** SCENE **/
void MKZ_SCENE_add_mesh(MKZ_meshedObject * mo);
void MKZ_SCENE_add_light(MKZ_lightObject * lo);
void MKZ_SCENE_set_camera(MKZ_camera * ca);

MKZ_meshedObject *  MKZ_SCENE_get_mesh(int id);
MKZ_lightObject * MKZ_SCENE_get_light(int id);
MKZ_camera * MKZ_SCENE_get_camera();
MKZ_camera * MKZ_SCENE_get_default_camera();

void MKZ_SCENE_remove_mesh(int id);
void MKZ_SCENE_remove_light(int id);
void MKZ_SCENE_restore_camera();

void MKZ_SCENE_set_global_mask(unsigned int g_mask);
unsigned int MKZ_SCENE_get_global_mask();

#endif
