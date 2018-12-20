
#include "MKZ_Definitions.h"

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

/** State variables **/
void (*callBack)(int event,void * state);
char* windowTitle = "";

/** call-back functions **/
void nothing(int event, void * state){}

void keyboardFunction(unsigned char key, int x, int y){


	MKZ_kb_event * kb_event = (MKZ_kb_event *) malloc(sizeof(MKZ_kb_event));

	kb_event->key = key;
	kb_event->x = x;
	kb_event->y = y;
	callBack(MKZ_CALLBACK_KEYBOARD,kb_event);
}

void specialFunction(int key, int x, int y){

	MKZ_kb_special_event * kb_event = (MKZ_kb_special_event *) malloc(sizeof(MKZ_kb_special_event));

	kb_event->key = key;
	kb_event->x = x;
	kb_event->y = y;
	callBack(MKZ_CALLBACK_SPECIAL_KEYBOARD,kb_event);
}


/** Exported part **/
void MKZ_WM_init(){

	int a = 0;
	glutInit(&a,0);

	callBack = nothing;

}

void MKZ_WM_bind_callback(){
	glutKeyboardFunc(keyboardFunction);
	glutSpecialFunc(specialFunction);
}
void MKZ_WM_set_display_function(void (* display )( void )){
	glutDisplayFunc(display);
}

void MKZ_WM_set_callBack_function(void (*cback)(int event,void * state)){
	callBack = cback;
}

void MKZ_WM_set_window_size(int width, int height){
	 glutInitWindowSize(width, height);
}

void MKZ_WM_set_window_title(char* title){
	windowTitle = title;
}

void MKZ_WM_create_window(){
	glutCreateWindow(windowTitle);
}

void MKZ_WM_enter_mainLoop(){
	glutMainLoop();
}

void MKZ_WM_draw(){
	glutPostRedisplay();
}


