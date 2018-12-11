#include "MKZ_Geometry.h"


#define DT_PROJECTIONMODE_PARALLEL 0
#define DT_PROJECTIONMODE_PERSPECTIVE 1

void DTinit();
void DTsetProjectionMode(int p_mode);
void DTsetDrawVolume(double left, double right, double bottom, double top, double near, double far);
void DTsetCamera(float * camMat);
void DTsetBackgroundColor(MKZ_color3 * bg);
void DTstartDrawing();
void DTclearScreen();
void DTdrawObject(MKZ_mesh * mo);
void DTendDrawing();

