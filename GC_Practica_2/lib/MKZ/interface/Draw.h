#include "DrawTools.h"
/** init **/
void Dinit();
/** callback **/
void Ddraw();

/* camera */
void DsetCameraTransform(float * camMat);
float * DgetCameraTransform();

/* Objects */
int DaddObject(meshed_object * mo);
meshed_object * DgetObject(int id);
void DremoveObject(int id);

/* Light */
int DaddLight(light_object * lo);
light_object * DgetLight(int id);
void DremoveLight(int id);
