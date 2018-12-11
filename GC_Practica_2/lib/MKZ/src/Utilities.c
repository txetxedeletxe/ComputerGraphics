#include <Arithmetic.h>
#include <stdlib.h>


float* UTcreateVector(int length){
	return (float *) malloc(sizeof(float)*length);
}

void UTmatIden(float* mat, int dim){

	for (int i = 0 ; i < dim*dim ; i++) {
		mat[i] = ((i % dim) == (i / dim)) ? 1 : 0;
	}

}

float UTdotProduct(float* v1, float* v2, int dimension ){

	int i;
	float psum = 0;

	for (i = 0 ; i < dimension ; i++){
		psum += v1[i]*v2[i];
	}

	return psum;
}

void UTnulVector(float* vec, int dim){

	int i;
	for ( i = 0 ; i < dim ; i++){
		vec[i] = 0;
	}
}
void UTvectorCP(float* vin, float* vout, int dim) {
	int i;
	for (i = 0; i < dim; i++) {
		vout[i] = vin[i];
	}
}
