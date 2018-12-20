#include "MKZ/MKZ.h"
#include "objects.h"
#include "KG.h"

#define KG_WINDOW_WIDTH 640
#define KG_WINDOW_HEIGHT 480

#define KG_WINDOW_TITLE "Practica GPO"

#define KG_COL_BACK_R                       0.60f
#define KG_COL_BACK_G                       0.30f
#define KG_COL_BACK_B                       0.60f
#define KG_COL_BACK_A                       1.00f

#define KG_ORTHO_WIDTH 8
#define KG_ORTHO_HEIGHT 6
#define KG_ORTHO_DEPTH 1000


/** Internal state */
/* objects */
linkedList * cameraList;
linkedList * objList;
object lightList[8];

linkedList * selectedCamera;
linkedList * selectedObject;
int selectedLight;


/** transform state **/
unsigned int t_type;
unsigned int t_scope;
unsigned int t_target;

void __KG_init(){

	cameraList = 0;
	objList = 0;
	selectedLight = 0;

	t_type = KG_TRANSFORM_TYPE_TRANSLATE;
	t_scope = KG_TRANSFORM_SCOPE_GLOBAL;
	t_target = KG_TRANSFORM_TARGET_OBJECT;

	/** Init first cam*/
	MKZ_camera * cam = MKZ_OBJECT_create_camera();
	cam->polygon_mode = MKZ_POLYGONMODE_FILLED;
	cam->skybox.r = KG_COL_BACK_R;
	cam->skybox.g = KG_COL_BACK_G;
	cam->skybox.b = KG_COL_BACK_B;
	cam->projection_mode = MKZ_PROJECTIONMODE_PERSPECTIVE;

	MKZ_vector3 * v3 = MKZ_GEOMETRY_create_vector3();
	v3->x = 1.0f/(KG_ORTHO_WIDTH);
	v3->y = 1.0f/(KG_ORTHO_HEIGHT);
	v3->z = 1.0f/(KG_ORTHO_DEPTH);

	MKZ_TRANSFORM_set_absolute_scale(cam->obj.transform,v3);

	MKZ_SCENE_set_camera(cam);

	linkedlist_add(&cameraList,cam);

	free(v3);
}

void KG_init(){

	MKZ_init();
	MKZ_WM_set_window_size(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
	MKZ_WM_set_window_title(KG_WINDOW_TITLE);
	MKZ_create_window();

	__KG_init();

}


void KG_set_callback(void (*func)(int event,void * state)){

	MKZ_WM_set_callBack_function(func);
}

void KG_enter_loop(){
	MKZ_WM_enter_mainLoop();
}

int KG_load_object(char * filename){

	MKZ_mesh * mesh = MKZ_GEOMETRY_load_mesh(filename);

	if (mesh == 0){
		return -1;
	}
	else{

		MKZ_meshedObject * mo = MKZ_OBJECT_create_meshedObject();
		mo->mesh = mesh;

		MKZ_SCENE_add_mesh(mo);

		object * obj = create_object_meshed(mo);
		linkedlist_add(&objList,obj);
		selectedObject = objList;
		return 0;
	}

}

void KG_select_next_object(){

	if (selectedObject != 0){
		selectedObject = selectedObject->ll_after;

		if (selectedObject == 0){
			selectedObject = objList;
		}

	}

}

void KG_delete_selected_object(){

	if (selectedObject != 0){

		if (selectedObject->ll_before == 0){

			objList = selectedObject->ll_after;

			if (objList != 0)
				objList->ll_before = 0;

			selectedObject->ll_after = 0;
			free_object_linkedlist(selectedObject);
			selectedObject = objList;
		}
		else{

			selectedObject->ll_before->ll_after = selectedObject->ll_after;

			if (selectedObject->ll_after != 0)
				selectedObject->ll_after->ll_before = selectedObject->ll_before;

			linkedList * ll = selectedObject->ll_after;

			selectedObject->ll_after = 0;
			selectedObject->ll_before = 0;

			free_object_linkedlist(selectedObject);

			selectedObject = ll;

			if (selectedObject == 0){
				selectedObject = objList;
			}
		}
	}
}

void KG_transform_type_set(unsigned int transform_type){

	t_type = transform_type;
}

void KG_transform_scope_set(unsigned int transform_scope){
	t_scope = transform_scope;
}

void KG_transform_target_set(unsigned int transform_target){
	t_target = transform_target;
}

void KG_transform(int axis){


}

void KG_uniform_scale(int sense){

}

void KG_undo_transformation(){

}

void KG_redo_transformation(){

}


void KG_next_camera(){

	if (selectedCamera != 0){
		selectedCamera = selectedCamera->ll_after;

			if (selectedCamera == 0){
				selectedCamera = cameraList;
			}

		}
}

void KG_object_camera(){

}


void KG_set_camera_projection(unsigned int p_mode){

	if (selectedCamera != 0){
		MKZ_camera * cam = (MKZ_camera *)selectedCamera->content;
		cam->projection_mode = p_mode;
	}
}

void KG_lighting_switch(){

}


void KG_lights_switch(int l_index){

}


void KG_light_select(int l_index){

}


void KG_switch_light_type(){

}


void KG_switch_lighting_mode(){

}

