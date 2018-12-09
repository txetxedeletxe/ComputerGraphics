void WMinit();
void WMsetDisplayFunction(void (*func)(void));
void WMsetCallbackFunction(void (*func)(int event,void * state));
void WMsetWindowSize(int width, int height);
void WMsetWindowTitle(char* title);
void WMcreateWindow();
void WMenterMainLoop();

void WMredisplay();
