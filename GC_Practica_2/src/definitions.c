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

lighting_component* create_light(int type, GLfloat intensityA, GLfloat intensityD, GLfloat intensityS, GLdouble red, GLdouble green, GLdouble blue, GLfloat shiny, int as){
	lighting_component *lc = (lighting_component*) malloc(sizeof(lighting_component));

	lc->light_type = type;
	lc->intensity[0] = intensityA;
	lc->intensity[1] = intensityD;
	lc->intensity[2] = intensityS;
	lc->shininess = shiny;
	lc->color.r = red;
	lc->color.g = green;
	lc->color.b = blue;
	lc->associated = as;

	return lc;

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
		stateField = stateField & (~mask);
	}
	else{
		stateField = stateField | mask;
	}
}

void flipState(unsigned int mask){

	stateField = stateField ^ mask;
}

void updateTransformObject() {

	if (checkState(KG_TRANSFORM_CAMERA)) {
		_transform_object = _actual_camera;
	} else if (checkState(KG_TRANSFORM_LIGHTING)) {
		_transform_object = _lights[_selected_light];
	} else {
		_transform_object = _selected_object;
	}

}
void addVectors(vector3 *v1, vector3 *v2){
	v1->x += v2->x;
	v1->y += v2->y;
	v1->z += v2->z;
}

void vectorFromPoints(point3 *p1, point3 *p2, vector3 *v){
	//normalOfPlane(v, p1, p2);
	v->x = p1->x - p2->x;
	v->y = p1->y - p2->y;
	v->z = p1->z - p2->z;
}

void normalOfObject(object3d*  o){

	//First the normal of each polygon is calculated
	int i;
	int j;
	point3 first;
	point3 second;
	point3 third;
	vector3 one;
	vector3 two;
	for (i = 0; i<o->num_faces; i++){

		first = o->vertex_table[o->face_table[i].vertex_table[0]].coord;
		second = o->vertex_table[o->face_table[i].vertex_table[1]].coord;
		third = o->vertex_table[o->face_table[i].vertex_table[2]].coord;
		vectorFromPoints(&first, &second, &one);
		vectorFromPoints(&first, &third, &two);
		normalOfPlane(&o->face_table[i].normal, &one, &two);

		for(j=0; j<o->face_table[i].num_vertices; j++){
			addVectors(&o->vertex_table[o->face_table[i].vertex_table[j]].normal, &o->face_table[i].normal);
		}
	}

	for (i=0; i<o->num_vertices; i++){
		unitaryVector(&o->vertex_table[i].normal);
	}


}





