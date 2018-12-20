#include <stdlib.h>
#include "objects.h"


void linkedlist_add(linkedList ** ll, void * content){

	linkedList * l = *(ll);
	linkedList * l2 = (linkedList *) malloc(sizeof(linkedList));
	l2->content = content;
	l2->ll_before = 0;
	l2->ll_after = l;

	if (l != 0)
		l->ll_before = l2;

	*(ll) = l2;

}

object * create_object_meshed(MKZ_meshedObject * mo){

	object * obj = (object *) malloc(sizeof(object));

	obj->mat = 0;
	obj->objectType = KG_OBJECT_TYPE_MESH;
	obj->object = mo;
	obj->children = 0;
	return obj;
}

object * create_object_camera(MKZ_camera * ca){

	object * obj = (object *) malloc(sizeof(object));

	obj->mat = 0;
	obj->objectType = KG_OBJECT_TYPE_CAMERA;
	obj->object = ca;
	obj->children = 0;
	return obj;
}

object * create_object_light(MKZ_lightObject * lo){

	object * obj = (object *) malloc(sizeof(object));

	obj->mat = 0;
	obj->objectType = KG_OBJECT_TYPE_LIGHT;
	obj->object = lo;
	obj->children = 0;
	return obj;
}



void add_child(object * parent, object * child){

	linkedlist_add(&parent->children, child);
}

void free_matstack(matStack * matS){
	if (matS != 0){
		free_matstack(matS->matStack);
		free(matS->mat);
		free(matS);
	}
}

void free_linkedlist(linkedList * ll, void (*free_tool)(void* obj)){
	if (ll != 0){
			free_linkedlist(ll->ll_after,free_tool);

			if (free_tool == 0){
				free(ll->content);
			}
			else{
				free_tool(ll->content);
			}
			free(ll);
		}
}

void __free_object(void * obj);

void free_object_linkedlist(linkedList * ll){
	free_linkedlist(ll,__free_object);
}

void free_object(object * obj){

	switch (obj->objectType){

		case KG_OBJECT_TYPE_MESH:
			MKZ_OBJECT_free_meshedObject((MKZ_meshedObject *) obj->object);
			break;

		case KG_OBJECT_TYPE_CAMERA:
			MKZ_OBJECT_free_camera((MKZ_camera *) obj->object);
			break;

		case KG_OBJECT_TYPE_LIGHT:
			MKZ_OBJECT_free_lightObject((MKZ_lightObject *) obj->object);
			break;
	}

	free_object_linkedlist(obj->children);
	free_matstack(obj->mat);
	free(obj);
}

void __free_object(void * obj){
	free_object((object*)obj);
}
