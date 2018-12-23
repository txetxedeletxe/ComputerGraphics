#ifndef __MKZ_OBJECTS_IMPORTED__
#define __MKZ_OBJECTS_IMPORTED__

#include "MKZ_Geometry.h"



typedef struct{

	float* transform;
	int active;
	int id;

}MKZ_object;

typedef struct {

	MKZ_object obj;

	MKZ_mesh * mesh;
	MKZ_material * material;


}MKZ_meshedObject;

typedef struct {

	MKZ_object obj;

	int light_type;

	float intensityAmbient;
	float intensityDifuse;
	float intensitySpecular;

	MKZ_color3 color;

	float atenuationConstant;
	float atenuationLinear;
	float atenuationQuadratic;

	float spotExponent;

}MKZ_lightObject;

typedef struct{

	MKZ_object obj;

	MKZ_color3 skybox;

	int projection_mode;

	double v_x, v_y, v_near, v_far;

	int polygon_mode;
	int culling_enabled;

	int lighting_enable;
	int lighting_mode;


}MKZ_camera;

/** Objects **/
MKZ_meshedObject * MKZ_OBJECT_create_meshedObject();
MKZ_lightObject * MKZ_OBJECT_create_lightObject();
MKZ_camera * MKZ_OBJECT_create_camera();

void MKZ_OBJECT_free_meshedObject(MKZ_meshedObject * mo);
void MKZ_OBJECT_free_lightObject(MKZ_lightObject * lo);
void MKZ_OBJECT_free_camera(MKZ_camera * ca);

#endif
