#include "MKZEngine.h"
#include "WindowManager.h"
#include "Draw.h"


void MKZinit(){

	WMinit();
	Dinit();

}

void MKZsetWindowSize(int width, int height){
	WMsetWindowSize(width,height);
}

void MKZsetWindowTitle(char * title){
	WMsetWindowTitle(title);
}

void MKZcreateWindow(){

	WMcreateWindow();
	WMsetDisplayFunction(Ddraw);
}

void MKZsetCallback(void (*func)(int event,void * state)){

	WMsetCallbackFunction(func);

}

void MKZenterMainLoop(){
	WMenterMainLoop();
}


void MKZdraw(){
	WMredisplay();
}

