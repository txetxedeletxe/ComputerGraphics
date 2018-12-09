#include "Geometry.h"

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

	float* transform;

}MKZ_camera;
