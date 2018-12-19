#ifndef __MKZ_WM_IMPORTED__
#define __MKZ_WM_IMPORTED__

#define MKZ_CALLBACK_KEYBOARD 0
#define MKZ_CALLBACK_SPECIAL_KEYBOARD 1

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

void MKZ_WM_init();
void MKZ_WM_set_display_function(void (*func)(void));
void KMZ_WM_set_callBack_function(void (*cback)(int event,void * state));
void MKZ_WM_create_window();
void MKZ_WM_set_window_size(int width, int height);
void MKZ_WM_set_window_title(char* title);
void MKZ_WM_enter_mainLoop();
void MKZ_WM_draw();

#endif
