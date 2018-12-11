#include "MKZ_Arithmetic.h"
void MKZ_TRANSFORM_to_cameraMatrix(float* transform_mat , float* camera_mat){

	MKZ_ARITHMETIC_identityMatrix(camera_mat);

	int i = 0;
	for (i = 0; i < 9 ; i++){
		camera_mat[((i%3)*4) + i/3] = transform_mat[ i%3 + 4*(i/3)];
	}

	for (i = 0 ; i < 3 ; i++ ){
		camera_mat[12 + i] = -MKZ_ARITHMETIC_dotProduct(transform_mat+i*4,transform_mat+12);
	}

}
