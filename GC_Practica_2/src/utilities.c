#include <stdio.h>
#include "utilities.h"

void matIden(GLfloat* mat){

	for (int i = 0 ; i < 16 ; i++) {
		mat[i] = ((i % 4) == (i / 4)) ? 1 : 0;
	}

}

void nulMat(GLfloat* mat) {
	for (int i = 0 ; i < 16 ; i++){
		mat[i] = 0;
	}
}

void MatMul(GLfloat* mat1, GLfloat* mat2 , GLfloat* mat3){

	int i;
	int j;
	int k;

	nulMat(mat3);
	for (i = 0 ; i < 4 ; i++){
		for (j = 0 ; j < 4 ; j++){
			for (k = 0 ; k < 4 ; k++){
				mat3[4*i + j] += mat1[4*k + j]*mat2[4*i + k];
			}
		}
	}


}

GLfloat dotProduct(GLfloat* v1, GLfloat* v2, int dimension ){

	int i;
	GLfloat psum = 0;

	for (i = 0 ; i < dimension ; i++){
		psum += v1[i]*v2[i];
	}

	return psum;
}

void printVector(GLfloat* vec, int size){


	printf("%f", vec[0]);
	int i = 1;
	for (; i< size ; i++){
		printf(" %f", vec[i]);
	}
	printf("\n");
	printf("\n");

}
void printMat(GLfloat* mat, int col, int row){

	int j = 0;
	for (; j < row ; j++){
		printf("%f", mat[j]);
		int i = 1;
		for (; i< col ; i++){
			printf(" %f", mat[i*4 + j]);
		}
		printf("\n");
	}
	printf("\n");
}