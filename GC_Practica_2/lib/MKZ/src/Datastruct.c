#include "MKZ_Datastruct.h"
#include <stdlib.h>

MKZ_linkedList * MKZ_DATASTRUCT_create_linkedList(){

	MKZ_linkedList * ll = (MKZ_linkedList*) malloc(sizeof(MKZ_linkedList));
	return ll;
}
