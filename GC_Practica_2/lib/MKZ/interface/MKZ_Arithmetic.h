#ifndef __MKZ_ARITHMETIC_IMPORTED__
#define __MKZ_ARITHMETIC_IMPORTED__

#include "MKZ_Geometry.h"

/** Arithmetic **/
float * MKZ_ARITHMETIC_create_matrix();
void MKZ_ARITHMETIC_matMul(float * mat1,float * mat2,float * mat3);
/* matrices */
void MKZ_ARITHMETIC_matrix_identity(float* mat);
void MKZ_ARITHMETIC_matrix_nul(float* mat);
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
