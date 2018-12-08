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
void WMinit(){

	int a = 0;
	glutInit(&a,0);
	glutInitDisplayMode(GLUT_RGB);

	callBack = nothing;

	//glutKeyboardFunc(keyboardFunction);
	//glutSpecialFunc(specialFunction);

}

void WMsetDisplayFunction(void (* display )( void )){
	glutDisplayFunc(display);
}

void WMsetCallbackFunction(void (*cback)(int event,void * state)){

	callBack = cback;

}

void WMsetWindowSize(int width, int height){
	 glutInitWindowSize(width, height);
}
void WMsetWindowTitle(char* title){
	windowTitle = title;
}
void WMcreateWindow(){
	glutCreateWindow(windowTitle);
}

void WMenterMainLoop(){
	glutMainLoop();
}

void WMredisplay(){
	glutPostRedisplay();
}


