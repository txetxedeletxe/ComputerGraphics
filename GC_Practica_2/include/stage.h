#ifndef INCLUDE_STAGE_H_
#define INCLUDE_STAGE_H_

#include "objects.h"

unsigned int state;

linkedList * mesh_list;
linkedList * light_list;
linkedList * camera_list;

linkedList * selected_mesh;
linkedList * selected_light;
linkedList * selected_camera;

void addMesh(object * obj);

#endif /* INCLUDE_STAGE_H_ */
