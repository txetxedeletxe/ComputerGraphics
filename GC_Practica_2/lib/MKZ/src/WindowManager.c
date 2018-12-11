#include <GL/glut.h>
#include <stdio.h>

/** State variables **/
void (*callBack)(int event,void * state);
char* windowTitle = "";

/** call-back functions **/
void nothing(int event, void * state){}

void keyboardFunction(unsigned char key, int x, int y){

	struct {
		unsigned char key;
		int x;
		int y;
	}kb;

	kb.key = key;
	kb.x = x;
	kb.y = y;
	callBack(0,&kb);
}

void specialFunction(int key, int x, int y){

	struct {
		int key;
		int x;
		int y;
	}kb;

	kb.key = key;
	kb.x = x;
	kb.y = y;
	callBack(1,&kb);
}


/** Exported part **/
void MKZ_WM_init(){

	int a = 0;
	glutInit(&a,0);
	glutInitDisplayMode(GLUT_RGB);

	callBack = nothing;

	glutKeyboardFunc(keyboardFunction);
	glutSpecialFunc(specialFunction);

}

void MKZ_WM_set_display_function(void (* display )( void )){
	glutDisplayFunc(display);
}

void KMZ_WM_set_callBack_function(void (*cback)(int event,void * state)){
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


