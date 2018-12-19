#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <GL/gl.h>
/** DEFINITIONS **/

#define KG_WINDOW_TITLE                     "Practica GPO"
#define KG_WINDOW_WIDTH                     600
#define KG_WINDOW_HEIGHT                    400

#define KG_MSSG_SELECT_FILE                 "Idatz ezazu fitxategiaren path-a: "
#define KG_MSSG_INVALIDFILE                 "Could not read from file"
#define KG_MSSG_FILEREAD                    "Fitxategiaren irakurketa buruta"

#define KG_STEP_MOVE                        5.0f
#define KG_STEP_ROTATE                      10.0f
#define KG_STEP_ZOOM                        0.75
#define KG_STEP_CAMERA_ANGLE                5.0f

#define KG_ORTHO_X_MIN_INIT                -5
#define KG_ORTHO_X_MAX_INIT                 5
#define KG_ORTHO_Y_MIN_INIT                -5
#define KG_ORTHO_Y_MAX_INIT                 5
#define KG_ORTHO_Z_MIN_INIT                -100
#define KG_ORTHO_Z_MAX_INIT                 100

#define KG_COL_BACK_R                       0.30f
#define KG_COL_BACK_G                       0.30f
#define KG_COL_BACK_B                       0.30f
#define KG_COL_BACK_A                       1.00f

#define KG_COL_SELECTED_R                   1.00f
#define KG_COL_SELECTED_G                   0.75f
#define KG_COL_SELECTED_B                   0.00f

#define KG_COL_NONSELECTED_R                1.00f
#define KG_COL_NONSELECTED_G                1.00f
#define KG_COL_NONSELECTED_B                1.00f

#define KG_MAX_DOUBLE                       10E25

#define KG_X_AXIS_POSITIVE 1
#define KG_X_AXIS_NEGATIVE -1
#define KG_Y_AXIS_POSITIVE 2
#define KG_Y_AXIS_NEGATIVE -2
#define KG_Z_AXIS_POSITIVE 3
#define KG_Z_AXIS_NEGATIVE -3

#define KG_ZOOM_IN -1
#define KG_ZOOM_OUT 1

/**BITMASK VALIUES**/
/* Codes for transformation operations */
#define KG_TRANSFORMATIONS_TRANSLATE 1
#define KG_TRANSFORMATIONS_ROTATE 2
#define KG_TRANSFORMATIONS_SCALE 4
#define KG_TRANSFORMATIONS 7
/* Scope of the transformation */
#define KG_SCOPE_GLOBAL 8
/*Camera type*/
#define KG_CAMERA_OBJECT 16
/*Transform type*/
#define KG_TRANSFORM_CAMERA 32


/* Step units for transformations */
#define KG_ROTATE_STEP 0.05235987755 // pi/60 radians, 3 degrees
#define KG_SCALE_STEP 1.1f
#define KG_TRANSLATE_STEP 0.3f
#define KG_SHEAR_STEP 0.05f

/*Camara mode*/
#define FLIGHT 0
#define ANALYZE 1


//Aliases para flags
typedef int AXIS;



#endif // DEFINITIONS_H

