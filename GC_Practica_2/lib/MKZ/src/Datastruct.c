#include "Datastruct.h"
#include "Utilities.h"
#include <stdlib.h>

linkedList * DScreateLinkedList(void* element,int id){

	linkedList * ll = (linkedList*) malloc(sizeof(linkedList));
	ll->content = element;
	ll->id = id;
	return ll;
}
