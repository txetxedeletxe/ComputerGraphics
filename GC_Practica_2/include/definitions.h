#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <GL/gl.h>

/** DEFINITIONS **/

#define KG_WINDOW_TITLE                     "Práctica GPO"
#define KG_WINDOW_WIDTH                     600
#define KG_WINDOW_HEIGHT                    400
#define KG_WINDOW_X                         50
#define KG_WINDOW_Y                         50

#define KG_MSSG_SELECT_FILE                 "Idatz ezazu fitxategiaren path-a: "
#define KG_MSSG_FILENOTFOUND                "Fitxategi hori ez da existitzen!!"
#define KG_MSSG_INVALIDFILE                 "Arazoren bat egon da fitxategiarekin ..."
#define KG_MSSG_EMPTYFILE                   "Fitxategia hutsik dago"
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
#define KG_ORTHO_Z_MAX_INIT                 10000

#define KG_FRUS_X_MIN_INIT                -1
#define KG_FRUS_X_MAX_INIT                 1
#define KG_FRUS_Y_MIN_INIT                -1
#define KG_FRUS_Y_MAX_INIT                 1
#define KG_FRUS_Z_MIN_INIT                 1
#define KG_FRUS_Z_MAX_INIT                 10000

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

#define KG_COL_X_AXIS_R                     1.0f
#define KG_COL_X_AXIS_G                     0.0f
#define KG_COL_X_AXIS_B                     0.0f

#define KG_COL_Y_AXIS_R                     0.0f
#define KG_COL_Y_AXIS_G                     1.0f
#define KG_COL_Y_AXIS_B                     0.0f

#define KG_COL_Z_AXIS_R                     0.0f
#define KG_COL_Z_AXIS_G                     0.0f
#define KG_COL_Z_AXIS_B                     1.0f

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
#define KG_TRANSFORMATIONS_REFLECT 8
#define KG_TRANSFORMATIONS_SHEAR 16
#define KG_TRANSFORMATIONS 31
/* Scope of the transformation */
#define KG_SCOPE_GLOBAL 32
/*Camera projection mode*/
#define KG_PROJECT_ORTHO 64
/*Camera type*/
#define KG_CAMERA_OBJECT 128
/*Transform type*/
#define KG_TRANSFORM_CAMERA 256


/* Step units for transformations */
#define KG_ROTATE_STEP 0.05235987755 // pi/60 radians, 3 degrees
#define KG_SCALE_STEP 1.1f
#define KG_TRANSLATE_STEP 0.3f
#define KG_SHEAR_STEP 0.05f

/*Camara mode*/
#define FLIGHT 0
#define ANALYZE 1

/*Component Ids*/

#define COMPONENT_TRANSFORM 1
#define COMPONENT_MESH 2

/** STRUCTURES **/

/****************************
 * Structure to store the   *
 * coordinates of 3D points *
 ****************************/
typedef struct {
    GLdouble x, y, z;
} point3;

/*****************************
 * Structure to store the    *
 * coordinates of 3D vectors *
 *****************************/
typedef struct {
    GLdouble x, y, z;
} vector3;

/****************************
 * Structure to store the   *
 * colors in RGB mode       *
 ****************************/
typedef struct {
    GLfloat r, g, b;
} color3;

/****************************
 * Structure to store       *
 * objects' vertices         *
 ****************************/
typedef struct {
    point3 coord;                       /* coordinates,x, y, z */
    GLint num_faces;                    /* number of faces that share this vertex */
} vertex;

/****************************
 * Structure to store       *
 * objects' faces or        *
 * polygons                 *
 ****************************/
typedef struct {
    GLint num_vertices;                 /* number of vertices in the face */
    GLint *vertex_table;                /* table with the index of each vertex */
} face;


struct matStack{

    GLfloat* mat;
    struct matStack * next;

};

/****************************
 * Structure to store a     *
 * pile of 3D objects       *
 ****************************/
struct object3d{
    GLint num_vertices;                 /* number of vertices in the object*/
    vertex *vertex_table;               /* table of vertices */
    GLint num_faces;                    /* number of faces in the object */
    face *face_table;                   /* table of faces */
    point3 min;                         /* coordinates' lower bounds */
    point3 max;                         /* coordinates' bigger bounds */
    
    
};

struct transform_component{

    struct matStack * undoStack;
    struct matStack * redoStack;   
    
};


struct component{

    int component_id;
    
    struct component * next;
    void * comp;
};

struct object{

    struct component* f_component; 
    struct object *next;
};



typedef struct object3d object3d;
typedef struct transform_component transform_component;
typedef struct component component;
typedef struct object object;

//Aliases para flags
typedef int AXIS;
typedef int ZOOM_DIRECTION;


/** GLOBAL VARIABLES **/



unsigned int stateField;



GLdouble _window_ratio;                     /*Control of window's proportions */
GLdouble _ortho_x_min,_ortho_x_max;         /*Variables for the control of the orthographic projection*/
GLdouble _ortho_y_min ,_ortho_y_max;        /*Variables for the control of the orthographic projection*/
GLdouble _ortho_z_min,_ortho_z_max;         /*Variables for the control of the orthographic projection*/
GLdouble _frust_x_min,_frust_x_max;         /*Variables for the control of the orthographic projection*/
GLdouble _frust_y_min ,_frust_y_max;        /*Variables for the control of the orthographic projection*/
GLdouble _frust_z_min,_frust_z_max;         /*Variables for the control of the orthographic projection*/

object * _first_object;                /*List of objects*/
object * _selected_object;
object * _first_camera;             /*Object currently selected*/
object * _selected_camera;

object * _actual_camera;

object * _transform_object;

object * _analyze_object;

vector3 origin;


/*Exported functions to manipulate datastructs*/

transform_component* create_transform();
object* create_object();
component* create_component(int id, void * comp);
void add_component(object * obj , component * comp);
void* get_component(object * obj , int component_id);

int checkState(unsigned int mask);
void changeState(unsigned int mask, int value);
int getState(unsigned int mask);
void flipState(unsigned int mask);

void addCamera(object * cam);
void add3dObject(object * obj);

void nextCamera();
void nextObject();

void deleteCamera();
void deleteCamera();
void updateTransformObject();
#endif // DEFINITIONS_H

