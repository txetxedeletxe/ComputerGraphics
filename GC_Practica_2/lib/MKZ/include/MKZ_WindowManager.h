#ifndef __MKZ_WM_IMPORTED__
#define __MKZ_WM_IMPORTED__


void MKZ_WM_init();
void MKZ_WM_set_display_function(void (*func)(void));
void MKZ_WM_set_callBack_function(void (*cback)(int event,void * state));
void MKZ_WM_bind_callback();
void MKZ_WM_create_window();
void MKZ_WM_set_window_size(int width, int height);
void MKZ_WM_set_window_title(char* title);
void MKZ_WM_enter_mainLoop();
void MKZ_WM_draw();

#endif
