#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "definitions.h"

/**
 * @brief Applies the selected transformation on the selected object and direction.
 * @param direction (axis and whether it is positive or negative)
 */
void transform(AXIS direction);

/**
 * @brief Zooms in the specified direction.
 * @param direction (axis and whether it is positive or negative)
 */
void zoom(ZOOM_DIRECTION direction);


/**
 * @brief Goes back to the previous state of the object.
 */
void undo();

/**
 * @brief It applies again an undone transformation.
 */
void redo();

void uniformScale(int direction);