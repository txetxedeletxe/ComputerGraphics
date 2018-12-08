#include "MKZEngine.h"
#include <stdlib.h>

int main(int argc, char **argv) {

	MKZinit();
	MKZcreateWindow(640,480);
	MKZenterMainLoop();


	return 0;
}
