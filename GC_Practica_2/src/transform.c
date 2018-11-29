#include "transform.h"
#include "utilities.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>



/**
 * @brief Calculates in mat the translation matrix in the specified direction
 * @param direction : (+-1, +-2, +-3), specifying the axis/direction
 * @param result matrix
 */
void translate(AXIS direction, GLfloat* mat);

/**
 * @brief Calculates in mat the scaling matrix in the specified direction
 * @param direction : (+-1, +-2, +-3), specifying the axis/direction
 * @param result matrix
 */
void scale(AXIS direction, GLfloat* mat);

/**
 * @brief Calculates in mat the rotation matrix in the specified direction
 * @param direction : (+-1, +-2, +-3), specifying the axis/direction
 * @param result matrix
 */
void rotate(AXIS direction, GLfloat* mat);

/**
 * @brief Calculates in mat the reflection matrix in the specified direction
 * @param direction : (+-1, +-2, +-3), specifying the axis/direction
 * @param result matrix
 */
void reflect(AXIS direction, GLfloat* mat);

/**
 * @brief Calculates in mat the shear matrix in the specified direction
 * @param direction : (+-1, +-2, +-3), specifying the axis/direction
 * @param result matrix
 */
void shear(AXIS direction, GLfloat* mat);

/**
 * @brief Updates the stack containing all the transformations steps.
 * @param The matrix that has to be included in the stack.
 */
void updateObjectMatrix(GLfloat * matrix);



void transform(AXIS direction){

    if (!_transform_object)
    	return;

	GLfloat* matrix = (GLfloat*) malloc(sizeof(GLfloat)*16);
	GLfloat* matrix2 = (GLfloat*) malloc(sizeof(GLfloat)*16);

    int sense = 0;

	/* SELECTS TRANSFORMATION */
	switch(getState(KG_TRANSFORMATIONS)){

		case KG_TRANSFORMATIONS_TRANSLATE:
			translate(direction,matrix);
			break;

		case KG_TRANSFORMATIONS_ROTATE:           
            
            if (direction > 0){
                sense = 1;            
            }
            else{
                sense = -1;
                direction = -direction;
            }
            //invertir ejes X e Y
            direction = (direction != 3) ? 3 - direction : 3;
			rotate(sense*direction,matrix);
			break;

		case KG_TRANSFORMATIONS_SCALE:
			scale(direction,matrix);
			break;

        case KG_TRANSFORMATIONS_REFLECT:
			reflect(direction,matrix);
			break;

        case KG_TRANSFORMATIONS_SHEAR:
			shear(direction,matrix);
			break;

	}

	transform_component * tc = (transform_component *)get_component(_transform_object,COMPONENT_TRANSFORM);

	
		
	

	/* left or right multiplication depending on the scope */
	if (checkState(KG_SCOPE_GLOBAL)){
		MatMul(matrix,tc->undoStack->mat,matrix2);
	}
	else{
		MatMul(tc->undoStack->mat,matrix,matrix2);
	}

	updateObjectMatrix(matrix2); //update the undo/redo stack

	free(matrix);



}


void undo(){

	if (!_transform_object)
		return;

	transform_component * tc = (transform_component *)get_component(_transform_object,COMPONENT_TRANSFORM);

	if (tc->undoStack->next != 0){
		struct matStack * ms = tc->undoStack;
		tc->undoStack = ms->next;
		ms->next = tc->redoStack;
		tc->redoStack = ms;
	}

}

void redo(){

	if (!_transform_object)
		return;

	transform_component * tc = (transform_component *)get_component(_transform_object,COMPONENT_TRANSFORM);

	if (tc->redoStack != 0){
		struct matStack * ms = tc->redoStack;
		tc->redoStack = tc->redoStack->next;
		ms->next = tc->undoStack;
		tc->undoStack = ms;
	}
}

void zoom(ZOOM_DIRECTION direction){

	GLdouble wd,he,midx,midy;
	if (direction == KG_ZOOM_IN){
		/*Increase the projection plane; compute the new dimensions*/
            wd=(_ortho_x_max-_ortho_x_min)*KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)*KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates*/
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane*/
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
	}
	else{
		 /*Increase the projection plane; compute the new dimensions*/
            wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates*/
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane*/
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
	}
}



void translate(AXIS direction, GLfloat * mat){

	matIden(mat);
    
	if (direction > 0)
		mat[11 + direction] = KG_TRANSLATE_STEP;
	else
		mat[11 - direction] = -KG_TRANSLATE_STEP;

}

void scale(AXIS direction, GLfloat * matrix) {

	matIden(matrix);

	if (direction > 0)
		matrix[5 * (direction - 1)] = KG_SCALE_STEP;
	else
		matrix[5 * ((-direction) - 1)] = 1/KG_SCALE_STEP;
}

 void rotate(AXIS direction, GLfloat* matrix)
{

    double sense; /* checks whether the orientation of the rotation is positive (counterclockwise) o negative (clockwise) */
    sense = direction > 0 ? 1 : -1; /* the sine could be affected, not the cosine */
    direction = direction > 0 ? direction : -direction; /* absolute value of the direction to know the axis to be modified (1-x, 2-y, 3-z) */
    static double seno = sin(KG_ROTATE_STEP);
    static double coseno = cos(KG_ROTATE_STEP);
    matIden(matrix);

    switch(direction) {

            case (1):
                    matrix[5]=coseno;
                    matrix[6]=sense*seno;
                    matrix[9]=-(sense)*seno;
                    matrix[10]=coseno;
        	break;

            case(2):
                    matrix[0]=coseno;
                    matrix[2]=-(sense)*seno;
                    matrix[8]=sense*seno;
                    matrix[10]=coseno;
        	break;

            case(3):
                    matrix[0]=coseno;
                    matrix[1]=sense*seno;
                    matrix[4]=-(sense)*seno;
                    matrix[5]=coseno;
        	break;
    }


}

void reflect(AXIS direction, GLfloat * matrix) {

	matIden(matrix);

    direction = (direction > 0) ? direction : -direction;

    matrix[5*(direction - 1)] *= -1; 	
    
}

void shear(AXIS direction, GLfloat * matrix) {
	
	matIden(matrix);

	switch(direction) {

		/* positive y */
		case(2):
			matrix[1] = KG_SHEAR_STEP;
			matrix[2] = KG_SHEAR_STEP;
			break;
		/* negative y */
		case(-2):
			matrix[1] = -KG_SHEAR_STEP;
			matrix[2] = -KG_SHEAR_STEP;
			break;
		/* positive x */
		case(1):
			matrix[4] = KG_SHEAR_STEP;
			matrix[6] = KG_SHEAR_STEP;
			break;
		/* negative x */
		case(-1):
			matrix[4] = -KG_SHEAR_STEP;
			matrix[6] = -KG_SHEAR_STEP;
			break;
		/* positive z */
		case(3):
			matrix[8] = KG_SHEAR_STEP;
			matrix[9] = KG_SHEAR_STEP;
			break;
		/* negative z */
		case(-3):
			matrix[8] = -KG_SHEAR_STEP;
			matrix[9] = -KG_SHEAR_STEP;
			break;
		default:
			break;
	}

}

void uniformScale(int direction){


	if (!_transform_object)
    	return;

	GLfloat* matrix = (GLfloat*) malloc(sizeof(GLfloat)*16);
	GLfloat* matrix2 = (GLfloat*) malloc(sizeof(GLfloat)*16);

	matIden(matrix);

	matrix[0] = (direction == 1) ? KG_SCALE_STEP : 1/KG_SCALE_STEP;
	matrix[5] = (direction == 1) ? KG_SCALE_STEP : 1/KG_SCALE_STEP;
	matrix[10] = (direction == 1) ? KG_SCALE_STEP: 1/KG_SCALE_STEP;

	transform_component * tc = (transform_component *)get_component(_transform_object,COMPONENT_TRANSFORM);

	/* left or right multiplication depending on the scope */
	if (checkState(KG_SCOPE_GLOBAL)){
		MatMul(matrix,tc->undoStack->mat,matrix2);
	}
	else{
		MatMul(tc->undoStack->mat,matrix,matrix2);
	}

	updateObjectMatrix(matrix2); //update the undo/redo stack

	free(matrix);

}


void updateObjectMatrix(GLfloat* matrix){

	transform_component * tc = (transform_component *)get_component(_transform_object,COMPONENT_TRANSFORM);

	struct matStack * ms = ( struct matStack *) malloc(sizeof(struct matStack));
	ms->mat = matrix;
	ms->next = tc->undoStack;
	tc->undoStack = ms;

	//Flush redo matStack

	while (tc->redoStack != 0){

		struct matStack *ms = tc->redoStack;
		free(ms->mat);
		tc->redoStack = ms->next;
		free(ms);
	}


}
