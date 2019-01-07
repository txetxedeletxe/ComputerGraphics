#include "MKZ_Lighting.h"
#include "MKZ_Definitions.h"
#include <stdlib.h>

void MKZ_LIGHTING_reset_to_black(MKZ_color3 * c3){

	c3->r = 0;
	c3->g = 0;
	c3->b = 0;

}

MKZ_color3 * MKZ_LIGHTING_create_color3(){
	MKZ_color3 * c3 = (MKZ_color3*) malloc(sizeof(MKZ_color3));
	MKZ_LIGHTING_reset_to_black(c3);
	return c3;
}


void MKZ_LIGHTING_free_color3(MKZ_color3 * col){
	free(col);
}


MKZ_material * MKZ_LIGHTING_create_material(){

	MKZ_material * mat = (MKZ_material *) malloc(sizeof(MKZ_material));
	mat->property_mask = 0;
	mat->ambient = 0;
	mat->diffuse = 0;
	mat->specular = 0;

	mat->translucent = 0;
	mat->reflectivity = 0;

	mat->normal_map = 0;
	mat->displacement_map = 0;

	mat->light_map = 0;
	mat->radiance_map = 0;

	mat->reflection_cube_map = 0;
	return mat;
}


MKZ_map * MKZ_LIGHTING_create_map(int size){

	MKZ_map * map = (MKZ_map *) malloc(sizeof(MKZ_map));
	map->n = size;
	map->floatMap = (float*) malloc(sizeof(float)*size*size);

	int i;

	for (i = 0 ; i < size*size ; i++){
		map->floatMap[i] = 0;
	}

	return map;
}

MKZ_3map * MKZ_LIGHTING_create_3map(int size){
	MKZ_3map * map = (MKZ_3map *) malloc(sizeof(MKZ_3map));
	map->n = size;
	map->floatMap1 = (float*) malloc(sizeof(float)*size*size);
	map->floatMap2 = (float*) malloc(sizeof(float)*size*size);
	map->floatMap3 = (float*) malloc(sizeof(float)*size*size);

	int i;

	for (i = 0 ; i < size*size ; i++){
		map->floatMap1[i] = 0;
		map->floatMap2[i] = 0;
		map->floatMap3[i] = 0;
	}

	return map;
}

MKZ_cube_map * MKZ_LIGHTING_create_cube_map(){

	MKZ_cube_map * c_map = (MKZ_cube_map *) malloc(sizeof(MKZ_cube_map));
	return c_map;
}

MKZ_ambient_component * MKZ_LIGHTING_create_ambient(){
	MKZ_ambient_component * ambient = (MKZ_ambient_component *) malloc(sizeof(MKZ_ambient_component));
	return ambient;
}

MKZ_diffuse_component * MKZ_LIGHTING_create_diffuse(){
	return (MKZ_diffuse_component *) MKZ_LIGHTING_create_ambient();
}

MKZ_specular_component * MKZ_LIGHTING_create_specular(){
	MKZ_specular_component * specular = (MKZ_specular_component *) malloc(sizeof(MKZ_specular_component));
	return specular;
}

MKZ_translucency_component* MKZ_LIGHTING_create_translucency(){
	MKZ_translucency_component * trans = (MKZ_translucency_component *) malloc(sizeof(MKZ_translucency_component));
	return trans;
}

MKZ_reflective_component * MKZ_LIGHTING_create_reflective(){
	MKZ_reflective_component * reflect = (MKZ_reflective_component *) malloc(sizeof(MKZ_reflective_component));
	return reflect;
}


void MKZ_LIGHTING_free_material(MKZ_material * mat){
	free(mat);
}

void MKZ_LIGHTING_free_map(MKZ_map * map){

	free(map->floatMap);
	free(map);
}

void MKZ_LIGHTING_free_3map(MKZ_3map * map3){

	free(map3->floatMap1);
	free(map3->floatMap2);
	free(map3->floatMap3);
	free(map3);

}

void MKZ_LIGHTING_free_cube_map(MKZ_cube_map * c_map){

	free(c_map);
}

void MKZ_LIGHTING_free_ambient(MKZ_ambient_component * ambient){
	free(ambient);
}

void MKZ_LIGHTING_free_diffuse(MKZ_diffuse_component * diffuse){
	free(diffuse);
}

void MKZ_LIGHTING_free_specular(MKZ_specular_component * specular){
	free(specular);
}

void MKZ_LIGHTING_free_translucency(MKZ_translucency_component * translucency){
	free(translucency);
}

void MKZ_LIGHTING_free_reflective(MKZ_reflective_component * reflective){
	free(reflective);
}

