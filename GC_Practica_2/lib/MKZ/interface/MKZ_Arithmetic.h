#ifndef __MKZ_ARITHMETIC_IMPORTED__
#define __MKZ_ARITHMETIC_IMPORTED__

#include "MKZ_Geometry.h"

float * MKZ_ARITHMETIC_create_matrix();
void MKZ_ARITHMETIC_free_matrix(float * mat);
void MKZ_ARITHMETIC_copy_matrix(float * vin , float * vout);

void MKZ_ARITHMETIC_identityMatrix(float* mat);
void MKZ_ARITHMETIC_nulMatrix(float* mat);

void MKZ_ARITHMETIC_matMul(float * mat1,float * mat2,float * mat3);

void MKZ_ARITHMETIC_normalize(float * v3);
void MKZ_ARITHMETIC_normalize_vector(MKZ_vector3 * v3);
void MKZ_ARITHMETIC_corssProduct_vector(MKZ_vector3* v1, MKZ_vector3* v2 , MKZ_vector3* v3);

float MKZ_ARITHMETIC_dotProduct_vector(MKZ_vector3 * v1, MKZ_vector3 * v2);
float MKZ_ARITHMETIC_dotProduct(float * v1, float * v2);

float MKZ_ARITHMETIC_eulidean_norm_vector(MKZ_vector3 * v3);
float MKZ_ARITHMETIC_eulidean_norm(float * v3);

void MKZ_ARITHMETIC_transform_vector(float * mat, MKZ_vector3 * v3);

float MKZ_ARITHMETIC_determinant(float * mat);


/** Transformation matrix **/
void MKZ_ARITHMETIC_matrix_translate(MKZ_vector3 * v3,float* mat);
void MKZ_ARITHMETIC_matrix_rotate(MKZ_line * axis, float rads,float* mat);
void MKZ_ARITHMETIC_matrix_rotateX(float rads,float* mat);
void MKZ_ARITHMETIC_matrix_rotateY(float rads,float* mat);
void MKZ_ARITHMETIC_matrix_rotateZ(float rads,float* mat);
void MKZ_ARITHMETIC_matrix_scale(MKZ_vector3 * along, float scalar,float* mat);
void MKZ_ARITHMETIC_matrix_scaleX(float scalar,float* mat);
void MKZ_ARITHMETIC_matrix_scaleY(float scalar,float* mat);
void MKZ_ARITHMETIC_matrix_scaleZ(float scalar,float* mat);
void MKZ_ARITHMETIC_matrix_scaleUniform(float scalar,float* mat);
void MKZ_ARITHMETIC_print_matrix(float * mat);


#endif
