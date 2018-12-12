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

void MKZ_TRANSFORM_matrix_global(float * modMat, float * transformMat){

	float * temp = MKZ_ARITHMETIC_create_matrix();

	MKZ_ARITHMETIC_matMul(modMat, transformMat, temp);

	MKZ_ARITHMETIC_copy_matrix(temp, transformMat);

	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_translate_global(float * tramat, MKZ_vector3 * v3){

	tramat[12] += v3->x;
	tramat[13] += v3->y;
	tramat[14] += v3->z;

}

void MKZ_TRANSFORM_rotate_global(float * tramat, MKZ_line * axis,  float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotate(axis, rads, temp);
	MKZ_TRANSFORM_matrix_global(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateX_global(float * tramat, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateX(rads, temp);
	MKZ_TRANSFORM_matrix_global(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateY_global(float * tramat, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateY(rads, temp);
	MKZ_TRANSFORM_matrix_global(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateZ_global(float * tramat, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateZ(rads, temp);
	MKZ_TRANSFORM_matrix_global(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scale_global(float * tramat, MKZ_vector3 * along, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scale(along, scalar, temp);
	MKZ_TRANSFORM_matrix_global(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleX_global(float * tramat, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleX(scalar, temp);
	MKZ_TRANSFORM_matrix_global(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleY_global(float * tramat, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleY(scalar, temp);
	MKZ_TRANSFORM_matrix_global(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleZ_global(float * tramat, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleZ(scalar, temp);
	MKZ_TRANSFORM_matrix_global(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleUniform_global(float * tramat, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleUniform(scalar, temp);
	MKZ_TRANSFORM_matrix_global(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_set_position_global(float * modMat, MKZ_point3 * position){

	modMat[12] = position->x;
	modMat[12] = position->y;
	modMat[12] = position->z;

}

/* local transform */
void MKZ_TRANSFORM_matrix_local(float * modMat, float * transformMat){

	float * temp = MKZ_ARITHMETIC_create_matrix();

	MKZ_ARITHMETIC_matMul( transformMat, modMat, temp);

	MKZ_ARITHMETIC_copy_matrix(temp, transformMat);

	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_translate_local(float * tramat, MKZ_vector3 * v3){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_translate(v3, temp);
	MKZ_TRANSFORM_matrix_local(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);


}

void MKZ_TRANSFORM_rotate_local(float * tramat, MKZ_line * axis, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotate(axis, rads, temp);
	MKZ_TRANSFORM_matrix_local(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateX_local(float * tramat, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateX(rads, temp);
	MKZ_TRANSFORM_matrix_local(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateY_local(float * tramat, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateY(rads, temp);
	MKZ_TRANSFORM_matrix_local(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_rotateZ_local(float * tramat, float rads){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_rotateZ(rads, temp);
	MKZ_TRANSFORM_matrix_local(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scale_local(float * tramat, MKZ_vector3 * along, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scale(along, scalar, temp);
	MKZ_TRANSFORM_matrix_local(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleX_local(float * tramat, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleX( scalar, temp);
	MKZ_TRANSFORM_matrix_local(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleY_local(float * tramat, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleY( scalar, temp);
	MKZ_TRANSFORM_matrix_local(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleZ_local(float * tramat, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleZ( scalar, temp);
	MKZ_TRANSFORM_matrix_local(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}

void MKZ_TRANSFORM_scaleUniform_local(float * tramat, float scalar){

	float * temp = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_matrix_scaleUniform(scalar, temp);
	MKZ_TRANSFORM_matrix_local(temp, tramat);
	MKZ_ARITHMETIC_free_matrix(temp);

}


