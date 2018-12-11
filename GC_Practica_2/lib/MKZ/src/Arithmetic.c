#include <stdlib.h>

float * MKZ_ARITHMETIC_create_matrix(){
	return (float*) malloc(sizeof(float)*16);
}

void MKZ_ARITHMETIC_identityMatrix(float* mat){

	for (int i = 0 ; i < 16; i++) {
		mat[i] = ((i % 4) == (i / 4)) ? 1 : 0;
	}

}

float MKZ_ARITHMETIC_dotProduct_vector(MKZ_vector3 * v1, MKZ_vector3 * v2){

	return v1->x*v2->x + v1->y*v2->y + v1->z*v2->z;
}

float MKZ_ARITHMETIC_dotProduct(float * v1, float * v2){

	int i;
	float psum = 0;

	for (i = 0 ; i < 3 ; i++){
		psum += v1[i]*v2[i];
	}

	return psum;
}

void MKZ_ARITHMETIC_nulMatrix(float* mat){

	int i;
	for ( i = 0 ; i < 16 ; i++){
		mat[i] = 0;
	}

}
void MKZ_ARITHMETIC_copy_matrix(float * vin , float * vout){

	int i;
	for (i = 0; i < 16; i++) {
		vout[i] = vin[i];
	}
}

void MKZ_ARITHMETIC_matMul(float * mat1,float * mat2,float * mat3){

	MKZ_ARITHMETIC_nulMatrix(mat3);

	int i,j,k;
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ; j < 4 ; j++){

			for (k = 0 ; k < 4 ; k++){

				mat3[i + j*4] += mat1[i + k*4]*mat2[j*4 + k];
			}
		}
	}
}

