#ifndef INCLUDE_MKZ_OBJECTS_H_
#define INCLUDE_MKZ_OBJECTS_H_

#include "MKZ/MKZ.h"

#define KG_OBJECT_TYPE_MESH 0
#define KG_OBJECT_TYPE_CAMERA 1
#define KG_OBJECT_TYPE_LIGHT 2


struct matStack{

	float * mat;
	struct matStack * matStack;
};

typedef struct matStack matStack;

struct linkedList{

	void * content;
	struct linkedList * ll_before;
	struct linkedList * ll_after;

};

typedef struct linkedList linkedList;

typedef struct{

	void * object;
	matStack * mat;
	int objectType;
	linkedList * children;

}object;

void linkedlist_add(linkedList ** ll, void * content);
void free_linkedlist(linkedList * ll,void (*free_tool)(void* obj));
void free_object_linkedlist(linkedList * ll);
object * create_object_meshed(MKZ_meshedObject * mo);
object * create_object_camera(MKZ_camera * ca);
object * create_object_light(MKZ_lightObject * lo);

void add_child(object * parent, object * child);

void free_object(object * obj);


#endif /* INCLUDE_MKZ_OBJECTS_H_ */
