#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "definitions.h"
#include "math.h"

/**
 * @brief Converts a given matrix intro the identity matrix of its size.
 * @param a matrix defined by columns on an array
 */
void matIden(GLfloat* mat);

/**
 * @brief Converts a given matrix intro the null matrix of its size.
 * @param a matrix defined by columns on an array
 */
void nulMat(GLfloat* mat);

/**
 * @brief Multiplies two matrices and leaves the result in a third matrix.
 * @param mat1 is the first operand
 * @param mat2 is the second operand
 * @param mat3 is the result of the product
 */
void MatMul(GLfloat* mat1, GLfloat* mat2 , GLfloat* mat3);

GLfloat dotProduct(GLfloat* v1, GLfloat* v2, int dimension  );

void printVector(GLfloat* vec, int size);

void printMat(GLfloat* mat, int col, int row);

void unitaryVector(MKZ_vector3* v);

void normalOfPlane(MKZ_vector3* normal, MKZ_vector3* v1, MKZ_vector3* v2);