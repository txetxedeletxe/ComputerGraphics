#include "MKZ_Geometry.h"
float * MKZ_ARITHMETIC_create_matrix();
void MKZ_ARITHMETIC_identityMatrix(float* mat);
void MKZ_ARITHMETIC_nulMatrix(float* mat);
void MKZ_ARITHMETIC_copy_matrix(float * vin , float * vout);
float MKZ_ARITHMETIC_dotProduct_vector(MKZ_vector3 * v1, MKZ_vector3 * v2);
float MKZ_ARITHMETIC_dotProduct(float * v1, float * v2);
float * MKZ_ARITHMETIC_matMul(float * mat1,float * mat2,float * mat3);
