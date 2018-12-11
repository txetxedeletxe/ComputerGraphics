#include <Arithmetic.h>
void TRtoCameraMatrix(float* transform_mat , float* camera_mat){

	UTmatIden(camera_mat,4);
	int i = 0;
	for (i = 0; i < 9 ; i++){
		camera_mat[((i%3)*4) + i/3] = transform_mat[ i%3 + 4*(i/3)];
	}

	for (i = 0 ; i < 3 ; i++ ){
		camera_mat[12 + i] = -UTdotProduct(transform_mat+i*4,transform_mat+12,3);
	}

}
