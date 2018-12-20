#ifndef __MKZ_DEFINITIONS_IMPORTED__
#define __MKZ_DEFINITIONS_IMPORTED__

#include <GL/gl.h>
#include <GL/glut.h>

typedef struct {
		unsigned char key;
		int x;
		int y;
}MKZ_kb_event;

typedef struct {
		int key;
		int x;
		int y;
}MKZ_kb_special_event;



#define MKZ_PROJECTIONMODE_PARALLEL 0
#define MKZ_PROJECTIONMODE_PERSPECTIVE 1

#define MKZ_CALLBACK_KEYBOARD 0
#define MKZ_CALLBACK_SPECIAL_KEYBOARD 1

#define MKZ_POLYGONMODE_DOTTED GL_POINT
#define MKZ_POLYGONMODE_WIREFRAME GL_LINE
#define MKZ_POLYGONMODE_FILLED GL_FILL

#define MKZ_KEY_RIGHT 		GLUT_KEY_RIGHT
#define MKZ_KEY_LEFT 		GLUT_KEY_LEFT
#define MKZ_KEY_UP 			GLUT_KEY_UP
#define MKZ_KEY_DOWN 		GLUT_KEY_DOWN
#define MKZ_KEY_PAGE_UP 	GLUT_KEY_PAGE_UP
#define MKZ_KEY_PAGE_DOWN 	GLUT_KEY_PAGE_DOWN
#define MKZ_KEY_F1			GLUT_KEY_F1
#define MKZ_KEY_F2			GLUT_KEY_F2
#define MKZ_KEY_F3			GLUT_KEY_F3
#define MKZ_KEY_F4			GLUT_KEY_F4
#define MKZ_KEY_F5			GLUT_KEY_F5
#define MKZ_KEY_F6			GLUT_KEY_F6
#define MKZ_KEY_F7			GLUT_KEY_F7
#define MKZ_KEY_F8			GLUT_KEY_F8
#define MKZ_KEY_F9			GLUT_KEY_F9
#define MKZ_KEY_F10			GLUT_KEY_F10
#define MKZ_KEY_F11			GLUT_KEY_F11
#define MKZ_KEY_F12			GLUT_KEY_F12


#endif
