#include "MKZ_Objects.h"
/** Init **/
void MKZ_SCENE_init();

/** Callback **/
void MKZ_SCENE_draw();

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


