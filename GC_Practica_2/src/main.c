#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "display.h"
#include "io.h"
#include "definitions.h"
#include "load_obj.h"



/** GENERAL INITIALIZATION **/
void initialization (){

    /*Initialization of all the variables with the default values*/
    _ortho_x_min = KG_ORTHO_X_MIN_INIT;
    _ortho_x_max = KG_ORTHO_X_MAX_INIT;
    _ortho_y_min = KG_ORTHO_Y_MIN_INIT;
    _ortho_y_max = KG_ORTHO_Y_MAX_INIT;
    _ortho_z_min = KG_ORTHO_Z_MIN_INIT;
    _ortho_z_max = KG_ORTHO_Z_MAX_INIT;

    _frust_x_min = KG_FRUS_X_MIN_INIT;
    _frust_x_max = KG_FRUS_X_MAX_INIT;
    _frust_y_min = KG_FRUS_Y_MIN_INIT;
    _frust_y_max = KG_FRUS_Y_MAX_INIT;
    _frust_z_min = KG_FRUS_Z_MIN_INIT;
    _frust_z_max = KG_FRUS_Z_MAX_INIT;

    _window_ratio = (GLdouble) KG_WINDOW_WIDTH / (GLdouble) KG_WINDOW_HEIGHT;

    /*Definition of the background color*/
    glClearColor(KG_COL_BACK_R, KG_COL_BACK_G, KG_COL_BACK_B, KG_COL_BACK_A);

    /*Definition of the method to draw the objects*/
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); //SUN
    //glEnable(GL_LIGHT1);
    glDisable(GL_LIGHT3); //Luz puntual en la primera camara. Siempre lo acompaña. En un principio estará apagado.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    object * cam = create_object();
    transform_component * trans = (transform_component * ) get_component(cam,COMPONENT_TRANSFORM);

    trans->undoStack->mat[14] = 10;

    cam->next = _first_camera;
    _first_camera = cam;
    _selected_camera = cam;
    _actual_camera = cam;

    lighting_component * lcc = create_light(PUNCTUAL, 10.0, 5.0, 1.0, 1.0, 0.0, 1.0, 10.0, 1);
    component * ccl = create_component(COMPONENT_LIGHT,lcc);
    add_component(cam, ccl);

    GLfloat light2_ambient[] = {lcc->color.r*lcc->intensity[0],lcc->color.g*lcc->intensity[0], lcc->color.b*lcc->intensity[0], 1.0};
    GLfloat light2_diffuse[] = { lcc->color.r*lcc->intensity[1], lcc->color.g*lcc->intensity[1], lcc->color.b*lcc->intensity[1], 1.0 };
    GLfloat light2_specular[] = {lcc->color.r*lcc->intensity[2], lcc->color.g*lcc->intensity[2], lcc->color.b*lcc->intensity[2], 1.0 };
    GLfloat light2_position[] = { trans->undoStack->mat[12], trans->undoStack->mat[13], trans->undoStack->mat[14], 1.0 };
    GLfloat spot2_direction[] = { trans->undoStack->mat[8], trans->undoStack->mat[9], -trans->undoStack->mat[10] };

    glLightfv(GL_LIGHT3, GL_AMBIENT, light2_ambient);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light2_specular);
    glLightfv(GL_LIGHT3, GL_POSITION, light2_position);
    glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.5);
    glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 1);
    glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0);

    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 90.0);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot2_direction);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);


    /*Foco del objeto -Falta realizar ajustes-*/
    /* Y tanto que necesita ajustes, esto no ilumina bien *CASI* nunca */
    lighting_component * lco = create_light(FOCUS, 1.0, 5.0, 5.0, 10.0, 0.0, 0.0, 20.0, 1);
    component * clo = create_component(COMPONENT_LIGHT,lco);
    object * objLightob = create_object();
    add_component(objLightob,clo);

    _lights[2] = objLightob;
    transform_component* tclo= (transform_component * ) get_component(objLightob,COMPONENT_TRANSFORM);
    tclo->undoStack->mat[0]=0;
    tclo->undoStack->mat[1]=0;
    tclo->undoStack->mat[2]=1;

    tclo->undoStack->mat[4]=1;
    tclo->undoStack->mat[5]=1;
    tclo->undoStack->mat[6]=0;

    tclo->undoStack->mat[8]=-1.0;
    tclo->undoStack->mat[9]=1.0;
    tclo->undoStack->mat[10]=0.0;

    tclo->undoStack->mat[12]=-2.0;
    tclo->undoStack->mat[13]=2.0;
    tclo->undoStack->mat[14]=0.0;

    GLfloat light3_ambient[] = {lco->color.r*lco->intensity[0],lco->color.g*lco->intensity[0], lco->color.b*lco->intensity[0], 1.0};
    GLfloat light3_diffuse[] = { lco->color.r*lco->intensity[1], lco->color.g*lco->intensity[1], lco->color.b*lco->intensity[1], 1.0 };
    GLfloat light3_specular[] = {lco->color.r*lco->intensity[2], lco->color.g*lco->intensity[2], lco->color.b*lco->intensity[2], 1.0 };
    GLfloat light3_position[] = { tclo->undoStack->mat[12], tclo->undoStack->mat[13], tclo->undoStack->mat[14], 1.0 };
    GLfloat spot3_direction[] = { 1.0, -1.0, 0.0 };

    glLightfv(GL_LIGHT2, GL_AMBIENT, light3_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light3_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light3_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light3_position);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.5);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 1);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0);

    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90.0);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot3_direction);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 2.0);
 /**************************************************************/


    lighting_component * lc = create_light(DIRECTIONAL, 3, 100.0, 50.0, 1, 1, 1, 100.0, 0); //SUN (directional light)
    component * c = create_component(COMPONENT_LIGHT,lc);
    object * objLight = create_object();
    add_component(objLight,c);

    _lights[0] = objLight;
    transform_component* tcl= (transform_component * ) get_component(objLight,COMPONENT_TRANSFORM);
    //X vector of the sun
    tcl->undoStack->mat[0]=1;
    tcl->undoStack->mat[1]=0;
    tcl->undoStack->mat[2]=0;
    //Y vector of the sun
    tcl->undoStack->mat[4]=0;
    tcl->undoStack->mat[5]=0;
    tcl->undoStack->mat[6]=-1;
    //Z vector of the sun
    tcl->undoStack->mat[8]=0.5;
    tcl->undoStack->mat[9]=1;
    tcl->undoStack->mat[10]=0.5;
    //Direction of the sun
    tcl->undoStack->mat[12]=0.5;
    tcl->undoStack->mat[13]=1;
    tcl->undoStack->mat[14]=0.5;




    GLfloat l_ambient[] = {lc->color.r*lc->intensity[0],lc->color.g*lc->intensity[0], lc->color.b*lc->intensity[0], 1.0};
    GLfloat l_difuse[] = { lc->color.r*lc->intensity[1], lc->color.g*lc->intensity[1], lc->color.b*lc->intensity[1], 1.0 };
    GLfloat l_specular[] = { lc->color.r*lc->intensity[2], lc->color.g*lc->intensity[2], lc->color.b*lc->intensity[2], 1.0 };
    GLfloat lightpos[4] = {tcl->undoStack->mat[12], tcl->undoStack->mat[13], tcl->undoStack->mat[14], 0}; //sun in direction (0, 1, 0, 0). The last cero means that is directional.
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    /*The sun suffers no attenuation min(1, 1/(a_0+a_1*d+a_2*d^2)) a_i being the coefficient and d the distance from the light to each vertex/polygon of the object*/
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, l_difuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, l_specular);
    glLightf(GL_LIGHT0, GL_SHININESS, lc->shininess);


    lighting_component * lcp = create_light(PUNCTUAL, 100.0, 1.0, 1.0, 0.4, 0.2, 0.1, 20.0, 0);
    component * c1l = create_component(COMPONENT_LIGHT,lcp);
    object * objLight1l = create_object();
    add_component(objLight1l,c1l);

    _lights[1] = objLight1l;
    transform_component* tcl1= (transform_component * ) get_component(objLight1l,COMPONENT_TRANSFORM);
    tcl1->undoStack->mat[0]=0;
    tcl1->undoStack->mat[1]=0;
    tcl1->undoStack->mat[2]=1;

    tcl1->undoStack->mat[4]=1;
    tcl1->undoStack->mat[5]=1;
    tcl1->undoStack->mat[6]=0;

    tcl1->undoStack->mat[8]=-1.0;
    tcl1->undoStack->mat[9]=1.0;
    tcl1->undoStack->mat[10]=0.0;

    tcl1->undoStack->mat[12]=-2.0;
    tcl1->undoStack->mat[13]=2.0;
    tcl1->undoStack->mat[14]=0.0;


    GLfloat light1_ambient[] = {lcp->color.r*lcp->intensity[0],lcp->color.g*lcp->intensity[0], lcp->color.b*lcp->intensity[0], 1.0};
    GLfloat light1_diffuse[] = { lcp->color.r*lcp->intensity[1], lcp->color.g*lcp->intensity[1], lcp->color.b*lcp->intensity[1], 1.0 };
    GLfloat light1_specular[] = {lcp->color.r*lcp->intensity[2], lcp->color.g*lcp->intensity[2], lcp->color.b*lcp->intensity[2], 1.0 };
    GLfloat light1_position[] = { tcl1->undoStack->mat[12], tcl1->undoStack->mat[13], tcl1->undoStack->mat[14], 1.0 };
    GLfloat spot_direction[] = { 1.0, -1.0, 0.0 };

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 1);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0);

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);



    changeState(KG_TRANSFORM_CAMERA,0);
    changeState(KG_PROJECT_ORTHO,0);
    changeState(KG_TRANSFORMATIONS,0);
    changeState(KG_TRANSFORMATIONS_TRANSLATE,1);
    changeState(KG_LIGHTING_ACTIVE, 1);

    GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat mat_difuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 0, 0, 0, 1 };
    GLfloat mat_shininess[] = { 100.0 };
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);


    char def_load[] = "resources/abioia.obj";

    object * obj1 = create_object();
    object * obj2 = create_object();

    object3d * mesh = (object3d*) malloc(sizeof(object3d));

    read_wavefront(def_load,mesh);

    component * c1 = create_component(COMPONENT_MESH,mesh);
    component * c2 = create_component(COMPONENT_MESH,mesh);

    add_component(obj1,c1);
    add_component(obj2,c2);

    obj1->next = _first_object;
    _first_object = obj1;

    obj2->next = _first_object;
    _first_object = obj2;

    _selected_object = _first_object;

    updateTransformObject();

    transform_component * tc  = get_component(obj1,COMPONENT_TRANSFORM);
    tc->undoStack->mat[12] = 2;

    tc = get_component(obj2,COMPONENT_TRANSFORM);
    tc->undoStack->mat[12] = -2;


}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {

    /*First of all, print the help information*/
    print_help();

    /* glut initializations */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y);
    glutCreateWindow(KG_WINDOW_TITLE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_DEPTH_TEST); // Z-buffer



    /* set the callback functions */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard); // function and direction keys control

    /* this initialization has to be AFTER the creation of the window */
    initialization();

    /* start the main loop */
    glutMainLoop();
    return 0;
}
