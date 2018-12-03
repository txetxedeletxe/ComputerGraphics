#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "camera.h"
#include "utilities.h"


/**
 * @brief Function to draw the axes
 */
void draw_axes()
{
    /*Draw X axis*/
    glColor3f(KG_COL_X_AXIS_R,KG_COL_X_AXIS_G,KG_COL_X_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(KG_MAX_DOUBLE,0,0);
    glVertex3d(-1*KG_MAX_DOUBLE,0,0);
    glEnd();
    /*Draw Y axis*/
    glColor3f(KG_COL_Y_AXIS_R,KG_COL_Y_AXIS_G,KG_COL_Y_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,KG_MAX_DOUBLE,0);
    glVertex3d(0,-1*KG_MAX_DOUBLE,0);
    glEnd();
    /*Draw Z axis*/
    glColor3f(KG_COL_Z_AXIS_R,KG_COL_Z_AXIS_G,KG_COL_Z_AXIS_B);
    glBegin(GL_LINES);
    glVertex3d(0,0,KG_MAX_DOUBLE);
    glVertex3d(0,0,-1*KG_MAX_DOUBLE);
    glEnd();
}


/**
 * @brief Callback reshape function. We just store the new proportions of the window
 * @param width New width of the window
 * @param height New height of the window
 */
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    /*  Take care, the width and height are integer numbers, but the ratio is a GLdouble so, in order to avoid
     *  rounding the ratio to integer values we need to cast width and height before computing the ratio */
    _window_ratio = (GLdouble) width / (GLdouble) height;
}


/**
 * @brief Callback display function
 */
void display(void) {
    GLint v_index, v, f;
    object *aux_obj = _first_object;

    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Define the projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*When the window is wider than our original projection plane we extend the plane in the X axis*/
    if (checkState(KG_PROJECT_ORTHO)){
        if ((_ortho_x_max - _ortho_x_min) / (_ortho_y_max - _ortho_y_min) < _window_ratio) {
            /* New width */
            GLdouble wd = (_ortho_y_max - _ortho_y_min) * _window_ratio;
            /* Midpoint in the X axis*/ 
            GLdouble midpt = (_ortho_x_min + _ortho_x_max) / 2;
            /*Definition of the projection*/
            glOrtho(midpt - (wd / 2), midpt + (wd / 2), _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);
        } else {/* In the opposite situation we extend the Y axis */
            /* New height */
            GLdouble he = (_ortho_x_max - _ortho_x_min) / _window_ratio;
            /* Midpoint in the Y axis */
            GLdouble midpt = (_ortho_y_min + _ortho_y_max) / 2;
            /*Definition of the projection*/
            glOrtho(_ortho_x_min, _ortho_x_max, midpt - (he / 2), midpt + (he / 2), _ortho_z_min, _ortho_z_max);
        }
    }
    else
    {
        glFrustum(_frust_x_min,_frust_x_max,_frust_y_min,_frust_y_max,_frust_z_min,_frust_z_max);
    }

    

    /* Now we start drawing the object */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*First, we draw the axes*/
    draw_axes();

    transform_component * camera = (transform_component *) get_component(_actual_camera,COMPONENT_TRANSFORM);
    GLfloat* camera_mat = (GLfloat*) malloc(sizeof(GLfloat)*16);
    toCameraMatrix(camera->undoStack->mat , camera_mat);

    /*Now each of the objects in the list*/
    while (aux_obj != 0) {

        /* Select the color, depending on whether the current object is the selected one or not */
        if (aux_obj == _selected_object){
            glColor3f(KG_COL_SELECTED_R,KG_COL_SELECTED_G,KG_COL_SELECTED_B);
        }else{
            glColor3f(KG_COL_NONSELECTED_R,KG_COL_NONSELECTED_G,KG_COL_NONSELECTED_B);
        }
        transform_component * transform = (transform_component *) get_component(aux_obj,COMPONENT_TRANSFORM);
        object3d * mesh = (object3d *)get_component(aux_obj,COMPONENT_MESH);
        /* Draw the object; for each face create a new polygon with the corresponding vertices */
        glLoadMatrixf(camera_mat);
        glMultMatrixf(transform->undoStack->mat);
        for (f = 0; f < mesh->num_faces; f++) {

            glBegin(GL_POLYGON);
            for (v = 0; v < mesh->face_table[f].num_vertices; v++) {
                v_index = mesh->face_table[f].vertex_table[v];
                glVertex3d(mesh->vertex_table[v_index].coord.x,
                        mesh->vertex_table[v_index].coord.y,
                        mesh->vertex_table[v_index].coord.z);

            }
            glEnd();
        }
        aux_obj = aux_obj->next;
    }
    /*Do the actual drawing*/
    glFlush();
}
