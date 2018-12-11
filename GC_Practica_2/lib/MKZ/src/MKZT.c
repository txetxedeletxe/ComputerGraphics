#include <stdlib.h>

#include "MKZT.h"

/** Tools **/
/** Objects **/
MKZ_meshedObject * MKZ_create_meshedObject(){
	MKZ_meshedObject * mo = (MKZ_meshedObject *) malloc(sizeof(MKZ_meshedObject));
	return mo;
}

MKZ_lightObject * MKZ_create_lightObject();
MKZ_camera * MKZ_create_camera();

void MKZ_free_meshedObject(MKZ_meshedObject * mo);
void MKZ_free_lightObject(MKZ_lightObject * lo);
void MKZ_free_camera(MKZ_camera * ca);

/** Geometry **/
MKZ_point3 * MKZ_create_point3();
MKZ_vector3 * MKZ_create_point3();
MKZ_face * MKZ_create_face(int vertex_count);
MKZ_line * MKZ_create_line();


void MKZ_face_add_vertex(MKZ_face * face, int p);

void MKZ_free_point3(MKZ_point3 * p3);
void MKZ_free_vector3(MKZ_vector3 * v3);
void MKZ_free_face(MKZ_face * face);
void MKZ_free_line(MKZ_line * line);



/** MESH **/
MKZ_mesh * MKZ_create_mesh(MKZ_point3 * vertices, MKZ_face * faces);
MKZ_mesh * MKZ_load_mesh(char * filename);
void MKZ_free_mesh(MKZ_mesh * mesh);

/** Transforms **/
/* matrices */
float * MKZ_matrix_identity();
float * MKZ_matrix_null();
float * MKZ_matrix_translate(MKZ_vector3 * v3);
float * MKZ_matrix_rotate(MKZ_line * axis, float rads);
float * MKZ_matrix_rotateX( float rads);
float * MKZ_matrix_rotateY( float rads);
float * MKZ_matrix_rotateZ( float rads);
float * MKZ_matrix_scale(MKZ_vector3 * along, float scalar);
float * MKZ_matrix_scaleX(float scalar);
float * MKZ_matrix_scaleY(float scalar);
float * MKZ_matrix_scaleZ(float scalar);
float * MKZ_matrix_scaleUniform(float scalar);

/* local transform */
void MKZ_transform_matrix_global(float * modMat, float * transformMat);
void MKZ_transform_translate_global(float * tramat, MKZ_vector3 * v3);
void MKZ_transform_rotate_global(float * tramat, MKZ_line * axis,  float rads);
void MKZ_transform_rotateX_global(float * tramat, float rads);
void MKZ_transform_rotateY_global(float * tramat, float rads);
void MKZ_transform_rotateZ_global(float * tramat, float rads);
void MKZ_transform_scale_global(float * tramat, MKZ_vector3 * along, float scalar);
void MKZ_transform_scaleX_global(float * tramat, float scalar);
void MKZ_transform_scaleY_global(float * tramat, float scalar);
void MKZ_transform_scaleZ_global(float * tramat, float scalar);
void MKZ_transform_scaleUniform_global(float * tramat, float scalar);

/* global transform */
void MKZ_transform_matrix_local(float * modMat, float * transformMat);
void MKZ_transform_translate_local(float * tramat, MKZ_vector3 * v3);
void MKZ_transform_rotate_local(float * tramat, MKZ_line * axis, float rads);
void MKZ_transform_rotateX_local(float * tramat, float rads);
void MKZ_transform_rotateY_local(float * tramat, float rads);
void MKZ_transform_rotateZ_local(float * tramat, float rads);
void MKZ_transform_scale_local(float * tramat, MKZ_vector3 * along, float scalar);
void MKZ_transform_scaleX_local(float * tramat, float scalar);
void MKZ_transform_scaleY_local(float * tramat, float scalar);
void MKZ_transform_scaleZ_local(float * tramat, float scalar);
void MKZ_transform_scaleUniform_local(float * tramat, float scalar);

/** Arithmetic **/

float * MKZ_matrix_multiply(float * mat_left, float * mat_right);
