#include "MKZ_Objects.h"
#include "MKZ_Arithmetic.h"
#include "MKZ_Definitions.h"

#include <stdlib.h>

int next_id = 0;

void MKZ_OBJECT_init_object(MKZ_object * obj){

	obj->transform = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_identityMatrix(obj->transform);
	obj->active = 1;
	obj->id = next_id++;

}

MKZ_meshedObject * MKZ_OBJECT_create_meshedObject(){

	MKZ_meshedObject * mmo = (MKZ_meshedObject *) malloc(sizeof(MKZ_meshedObject));
	MKZ_OBJECT_init_object(&mmo->obj);
	mmo->material = 0;
	mmo->mesh = 0;
	return mmo;

}

MKZ_lightObject * MKZ_OBJECT_create_lightObject(){

	MKZ_lightObject * mlo = (MKZ_lightObject *) malloc(sizeof(MKZ_lightObject));
	MKZ_OBJECT_init_object(&mlo->obj);
	mlo->color.r = 1;
	mlo->color.g = 1;
	mlo->color.b = 1;
	mlo->intensityAmbient = 1;
	mlo->intensityDifuse = 1;
	mlo->intensitySpecular = 1;

	mlo->atenuationConstant = 1;
	mlo->atenuationLinear = 1;
	mlo->atenuationQuadratic = 1;

	mlo->spotExponent = 0;

	mlo->light_type = 0;

	return mlo;
}

MKZ_camera * MKZ_OBJECT_create_camera(){

	MKZ_camera * mc = (MKZ_camera *) malloc(sizeof(MKZ_camera));
	MKZ_OBJECT_init_object(&mc->obj);
	mc->projection_mode = MKZ_PROJECTIONMODE_PARALLEL;
	mc->polygon_mode = MKZ_POLYGONMODE_FILLED;
	MKZ_GEOMETRY_reset_to_black(&mc->skybox);
	mc->lighting_enable = 0;
	mc->lighting_mode = 0;
	mc->culling_enabled = 1;
	mc->v_x = 2;
	mc->v_y = 2;
	mc->v_near = 1;
	mc->v_far = 1000;

	return mc;

}

void MKZ_OBJECT_free_object(MKZ_object * obj){

	MKZ_ARITHMETIC_free_matrix(obj->transform);

}

void MKZ_OBJECT_free_meshedObject(MKZ_meshedObject * mo){

	MKZ_OBJECT_free_object(&mo->obj);
	free(mo);
}

void MKZ_OBJECT_free_lightObject(MKZ_lightObject * lo){

	MKZ_OBJECT_free_object(&lo->obj);
	free(lo);

}
void MKZ_OBJECT_free_camera(MKZ_camera * ca){

	MKZ_OBJECT_free_object(&ca->obj);
	free(ca);
}
