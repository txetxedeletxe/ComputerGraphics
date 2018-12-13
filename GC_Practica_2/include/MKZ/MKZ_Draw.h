#ifndef __MKZ_DRAW_IMPORTED__
#define __MKZ_DRAW_IMPORTED__

#include "MKZ_Geometry.h"


#define MKZ_DRAW_PROJECTIONMODE_PARALLEL 0
#define MKZ_DRAW_PROJECTIONMODE_PERSPECTIVE 1

/** DRAW CONTROL**/
void MKZ_DRAW_enable_drawMask(unsigned int d_mask);
void MKZ_DRAW_disable_drawMask(unsigned int d_mask);
void MKZ_DRAW_set_renderVolume(double left, double right, double bottom, double top, double near, double far);

#endif
