#include "definitions.h"
#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>

void add_component(object * obj , component * comp){

	comp->next = obj->f_component;
	obj->f_component = comp;

}

void* get_component(object * obj , int component_id){


	component * c = obj->f_component;
	
	while (c != 0){


		if (c->component_id == component_id)
			return c->comp;
		c = c->next;
	}

	
	return 0;
}

transform_component* create_transform(){

	transform_component * tc = (transform_component*) malloc(sizeof(transform_component));
	tc->undoStack = (struct matStack *) malloc(sizeof(struct matStack));
	
	GLfloat * mat = (GLfloat*) malloc(sizeof(GLfloat)*16);
	matIden(mat);
	tc->undoStack->mat = mat;
	tc->undoStack->next = 0;
	tc->redoStack = 0;

	return tc;

}

component* create_component(int id, void * comp){

	component* compo = (component*) malloc(sizeof(component));
	compo->component_id = id;
	compo->comp = comp;
	compo->next = 0;

	return compo;

}

object* create_object(){
	object* obj = (object*) malloc(sizeof(object));
	transform_component *tc = create_transform();
	component* comp = create_component(COMPONENT_TRANSFORM,tc);
	obj->f_component = 0;
	add_component(obj,comp);
	//printf("%d\n", obj->f_component->component_id);
            
	
	return obj;
}

int checkState(unsigned int mask){

	return (stateField & mask) == mask;
}

int getState(unsigned int mask){
	return stateField & mask;
}

void changeState(unsigned int mask, int value){

	if (value == 0){
		stateField = stateField & (!mask);
	}
	else{
		stateField = stateField | mask;
	}
}

void flipState(unsigned int mask){

	stateField = stateField ^ mask;
}

void updateTransformObject(){

     _transform_object = (checkState(KG_TRANSFORM_CAMERA)) ? _actual_camera : _selected_object;

}

