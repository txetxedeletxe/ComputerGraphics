#include "definitions.h"
#include "utilities.h"
#include "camera.h"

void toCameraMatrix(GLfloat* transform_mat , GLfloat* camera_mat){

	matIden(camera_mat);
	int i = 0;
	for (i = 0; i < 9 ; i++){
		camera_mat[((i%3)*4) + i/3] = transform_mat[ i%3 + 4*(i/3)];
	}

	for (i = 0 ; i < 3 ; i++ ){
		camera_mat[12 + i] = -dotProduct(transform_mat+i*4,transform_mat+12,3);
	}



}