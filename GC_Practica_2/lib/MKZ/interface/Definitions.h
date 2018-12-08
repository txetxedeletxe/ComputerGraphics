#include "Geometry.h"

struct empty_object{

	float* transform;
	int visible;

};

typedef struct empty_object empty_object;


typedef struct {

	mesh * mesh;
	material * material;
	empty_object obj;

}meshed_object;

typedef struct {

	int light_type;
	empty_object obj;

}light_object;
