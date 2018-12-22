#ifndef __MKZ_DRAW_IMPORTED__
#define __MKZ_DRAW_IMPORTED__

#include "MKZ_Objects.h"

void MKZ_DRAW_init();
void MKZ_DRAW_set_projectionMode(int p_mode);
void MKZ_DRAW_set_poligonMode(int p_mode);
void MKZ_DRAW_set_renderVolume(double left, double right, double bottom, double top, double near, double far);
void MKZ_DRAW_set_cameraMat(float * camMat);
void MKZ_DRAW_reset_identity_camera();
void MKZ_DRAW_set_background_color(MKZ_color3 * bg);
void MKZ_DRAW_set_lighting(int boolean);
void MKZ_DRAW_set_lighting_mode(int mode);
void MKZ_DRAW_set_culling(int boolean);
void MKZ_DRAW_start();
void MKZ_DRAW_clear();
void MKZ_DRAW_clear_lights();
void MKZ_DRAW_add_light(MKZ_lightObject * lo);
void MKZ_DRAW_object(MKZ_meshedObject * mo);
void MKZ_DRAW_enable_drawMask(unsigned int d_mask);
void MKZ_DRAW_disable_drawMask(unsigned int d_mask);
void MKZ_DRAW_end();


#endif
