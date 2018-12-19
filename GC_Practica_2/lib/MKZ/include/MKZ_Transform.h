#ifndef __MKZ_TRANSFORM_IMPORTED__
#define __MKZ_TRANSFORM_IMPORTED__

#include "MKZ_Geometry.h"

void MKZ_TRANSFORM_to_cameraMatrix(float* transform_mat , float* camera_mat);

/** Transforms **/
/* global transform */
void MKZ_TRANSFORM_matrix_global(float * modMat, float * transformMat);
void MKZ_TRANSFORM_translate_global(float * tramat, MKZ_vector3 * v3);
void MKZ_TRANSFORM_rotate_global(float * tramat, MKZ_line * axis,  float rads);
void MKZ_TRANSFORM_rotateX_global(float * tramat, float rads);
void MKZ_TRANSFORM_rotateY_global(float * tramat, float rads);
void MKZ_TRANSFORM_rotateZ_global(float * tramat, float rads);
void MKZ_TRANSFORM_scale_global(float * tramat, MKZ_vector3 * along, float scalar);
void MKZ_TRANSFORM_scaleX_global(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleY_global(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleZ_global(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleUniform_global(float * tramat, float scalar);
void MKZ_TRANSFORM_set_position_global(float * modMat, MKZ_point3 * position);
void MKZ_TRANSFORM_set_absolute_scale(float* modMat, MKZ_vector3 * scaleVector);

MKZ_vector3 * MKZ_TRANSFORM_get_absolute_scale(float* tramat);

/* local transform */
void MKZ_TRANSFORM_matrix_local(float * modMat, float * transformMat);
void MKZ_TRANSFORM_translate_local(float * tramat, MKZ_vector3 * v3);
void MKZ_TRANSFORM_rotate_local(float * tramat, MKZ_line * axis, float rads);
void MKZ_TRANSFORM_rotateX_local(float * tramat, float rads);
void MKZ_TRANSFORM_rotateY_local(float * tramat, float rads);
void MKZ_TRANSFORM_rotateZ_local(float * tramat, float rads);
void MKZ_TRANSFORM_scale_local(float * tramat, MKZ_vector3 * along, float scalar);
void MKZ_TRANSFORM_scaleX_local(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleY_local(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleZ_local(float * tramat, float scalar);
void MKZ_TRANSFORM_scaleUniform_local(float * tramat, float scalar);


#endif
