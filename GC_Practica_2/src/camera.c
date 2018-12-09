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


void toAnalyzeMode(GLfloat *camara, GLfloat *objeto){

	//direct es el vector dirección de la camaŕa al objeto.
	GLfloat direct_x = objeto[12] - camara[12];
	GLfloat direct_y = objeto[13] - camara[13];
	GLfloat direct_z = objeto[14] - camara[14];

	MKZ_vector3 direction;
	direction.x = direct_x;
	direction.y = direct_y;
	direction.z = direct_z;

	MKZ_vector3 vup;
	vup.x = camara[4];
	vup.y = camara[5];
	vup.z = camara[6];

	MKZ_vector3 newX;

	unitaryVector(&direction);
	unitaryVector(&vup);
	normalOfPlane(&newX, &direction, &vup);
	normalOfPlane(&vup, &newX , &direction);

	camara[0] = newX.x;
	camara[1] = newX.y;
	camara[2] = newX.z;

	camara[4]= vup.x;
	camara[5]= vup.y;
	camara[6]= vup.z;

	camara[8] = -direction.x;
	camara[9] = -direction.y;
	camara[10] = -direction.z;
}
