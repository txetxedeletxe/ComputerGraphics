#ifndef __MKZ_DRAW_IMPORTED__
#define __MKZ_DRAW_IMPORTED__

#include "MKZ_Objects.h"

#define MKZ_DRAW_PROJECTIONMODE_PARALLEL 0
#define MKZ_DRAW_PROJECTIONMODE_PERSPECTIVE 1

void MKZ_DRAW_init();
void MKZ_DRAW_set_projectionMode(int p_mode);
void MKZ_DRAW_set_poligonMode(int p_mode);
void MKZ_DRAW_set_renderVolume(double left, double right, double bottom, double top, double near, double far);
void MKZ_DRAW_set_cameraMat(float * camMat);
void MKZ_DRAW_set_background_color(MKZ_color3 * bg);
void MKZ_DRAW_start();
void MKZ_DRAW_clear();
void MKZ_DRAW_object(MKZ_meshedObject * mo);
void MKZ_DRAW_enable_drawMask(unsigned int d_mask);
void MKZ_DRAW_disable_drawMask(unsigned int d_mask);
void MKZ_DRAW_end();

#endif
