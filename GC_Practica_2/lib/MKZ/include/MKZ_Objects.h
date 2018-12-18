#ifndef __MKZ_OBJECTS_IMPORTED__
#define __MKZ_OBJECTS_IMPORTED__

#include "MKZ_Geometry.h"

typedef struct{

	float* transform;
	int active;
	int id;

}MKZ_object;

typedef struct {


	MKZ_mesh * mesh;
	MKZ_material * material;

	MKZ_object obj;


}MKZ_meshedObject;

typedef struct {

	int light_type;

	float intensity;
	MKZ_color3 color;

	MKZ_object obj;


}MKZ_lightObject;

typedef struct{

	MKZ_object obj;

	MKZ_color3 skybox;


}MKZ_camera;

/** Objects **/
MKZ_meshedObject * MKZ_OBJECT_create_meshedObject();
MKZ_lightObject * MKZ_OBJECT_create_lightObject();
MKZ_camera * MKZ_OBJECT_create_camera();

void MKZ_OBJECT_free_meshedObject(MKZ_meshedObject * mo);
void MKZ_OBJECT_free_lightObject(MKZ_lightObject * lo);
void MKZ_OBJECT_free_camera(MKZ_camera * ca);

#endif
