#include "MKZ_Objects.h"
#include "MKZ_Arithmetic.h"
#include <stdlib.h>

/*
 * MKZ_Objects.c
 *
 *  Created on: Dec 14, 2018
 *      Author: 837459
 */

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
	return mmo;

}

MKZ_lightObject * MKZ_OBJECT_create_lightObject(){

	MKZ_lightObject * mlo = (MKZ_lightObject *) malloc(sizeof(MKZ_lightObject));
	MKZ_OBJECT_init_object(&mlo->obj);
	return mlo;
}

MKZ_camera * MKZ_OBJECT_create_camera(){

	MKZ_camera * mc = (MKZ_camera *) malloc(sizeof(MKZ_camera));
	MKZ_OBJECT_init_object(&mc->obj);
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
