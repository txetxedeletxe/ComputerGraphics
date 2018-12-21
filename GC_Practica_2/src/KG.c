#include "MKZ/MKZ.h"
#include "objects.h"
#include "KG.h"

#include <stdio.h>

#define KG_WINDOW_WIDTH 640
#define KG_WINDOW_HEIGHT 480

#define KG_WINDOW_TITLE "Practica GPO"

#define KG_COL_BACK_R                       0.60f
#define KG_COL_BACK_G                       0.30f
#define KG_COL_BACK_B                       0.60f
#define KG_COL_BACK_A                       1.00f

#define KG_ORTHO_WIDTH 8
#define KG_ORTHO_HEIGHT 6
#define KG_ORTHO_DEPTH 10


#define KG_TRANSLATE_STEP 0.3f
#define KG_ROTATE_STEP 0.05235987755
#define KG_SCALE_STEP 1.1f

#define KG_SP_FUNC_OBJECT_CAMERA 1

/** Internal state */
/* objects */
object * lightList[8];
linkedList * cameraList;
linkedList * objList;


linkedList * selectedCamera;
linkedList * selectedObject;
int selectedLight;


/** transform state **/
int t_type;
int t_scope;
int t_target;

/** special functions**/
int special_function;

/** Private Functions **/
void KG_save_object_matrix(object * obj){

	/** copy matrix to stack */


	MKZ_object * mkz_obj = get_mkz_object(obj);

	float * mat = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_copy_matrix(mkz_obj->transform,mat);
	MKZ_ARITHMETIC_print_matrix(mat);
	matStack_push(&obj->undoStack,mat);

	/**cannot redo **/
	free_matstack(obj->redoStack);
	obj->redoStack = 0;

}

void KG_update_children(object * obj){

	linkedList * ch = obj->children;
	MKZ_object * mkzo = get_mkz_object(obj);
	float * tramat = mkzo->transform;

	while (ch != 0){

		object * ch_obj = (object *) ch->content;
		MKZ_object * ch_mkz = get_mkz_object(ch_obj);

		MKZ_ARITHMETIC_matMul(tramat,ch_obj->undoStack->mat,ch_mkz->transform);

		ch = ch->ll_after;
	}


}

void __KG_init(){

	cameraList = 0;
	objList = 0;
	selectedLight = 0;
	selectedCamera = 0;
	selectedObject = 0;

	t_type = KG_TRANSFORM_TYPE_TRANSLATE;
	t_scope = KG_TRANSFORM_SCOPE_GLOBAL;
	t_target = KG_TRANSFORM_TARGET_OBJECT;
	special_function = 0;

	/** init scene**/
	MKZ_camera * cam  = MKZ_SCENE_get_default_camera();
	cam->polygon_mode = MKZ_POLYGONMODE_FILLED;
	cam->skybox.r = KG_COL_BACK_R;
	cam->skybox.g = KG_COL_BACK_G;
	cam->skybox.b = KG_COL_BACK_B;
	cam->lighting_enable = 1;
	cam->lighting_mode = MKZ_LIGHTING_FLAT;

	MKZ_SCENE_set_global_mask(MKZ_GLOBAL_BG_COLOR | MKZ_GLOBAL_POLYGON | MKZ_GLOBAL_LIGHTING_ENABLE | MKZ_GLOBAL_LIGHTING_MODE);

	/** Init first cam*/
	cam = MKZ_OBJECT_create_camera();

	cam->projection_mode = MKZ_PROJECTIONMODE_PERSPECTIVE;

	MKZ_vector3 * v3 = MKZ_GEOMETRY_create_vector3();
	v3->x = 1.0f/(KG_ORTHO_WIDTH);
	v3->y = 1.0f/(KG_ORTHO_HEIGHT);
	v3->z = 1.0f/(KG_ORTHO_DEPTH);

	MKZ_TRANSFORM_set_absolute_scale(cam->obj.transform,v3);

	v3->x = 0;
	v3->y = 0;
	v3->z = 15;

	MKZ_TRANSFORM_translate_global(cam->obj.transform,v3);
	MKZ_SCENE_set_camera(cam);

	object * obj = create_object_camera(cam);
	KG_save_object_matrix(obj);
	linkedlist_add(&cameraList,obj);
	selectedCamera = cameraList;


	MKZ_lightObject * lo = MKZ_OBJECT_create_lightObject();
	lo->light_type = MKZ_LIGHT_TYPE_POINT;
	MKZ_SCENE_add_light(lo);

	obj = create_object_light(lo);
	KG_save_object_matrix(obj);
	lightList[0] = obj;

	//printf("%d\n",lightList[0]);

	free(v3);
}


void KG_transform_object(int axis){

	if (t_target == KG_TRANSFORM_TARGET_OBJECT && selectedObject == 0)
		return;

	if (t_target == KG_TRANSFORM_TARGET_LIGHT && lightList[selectedLight] == 0)
		return;

	object * obj;

	if (t_target == KG_TRANSFORM_TARGET_OBJECT)
		obj = (object *) selectedObject->content;
	else
		obj = lightList[selectedLight];


	MKZ_object * mo = get_mkz_object(obj);

	int sense = axis;
	int magnitude = axis;

	if (magnitude < 0){
		magnitude = -magnitude;
	}

	sense = sense/magnitude;

	MKZ_vector3 * v3 = MKZ_GEOMETRY_create_vector3();

	float scaleFactor = 1.0f;

	float * n_mat = MKZ_ARITHMETIC_create_matrix();

	switch (t_type){

	case KG_TRANSFORM_TYPE_TRANSLATE:

		switch (magnitude){

		case KG_TRANSFORM_AXIS_X:
			v3->x = sense * KG_TRANSLATE_STEP;
			break;

		case KG_TRANSFORM_AXIS_Y:
			v3->y = sense * KG_TRANSLATE_STEP;
			break;

		case KG_TRANSFORM_AXIS_Z:
			v3->z = sense * KG_TRANSLATE_STEP;
			break;

		}

		MKZ_ARITHMETIC_matrix_translate(v3,n_mat);
		break;

	case KG_TRANSFORM_TYPE_ROTATE:

		switch (magnitude){

		case KG_TRANSFORM_AXIS_X:
			MKZ_ARITHMETIC_matrix_rotateY(sense*KG_ROTATE_STEP,n_mat);
			break;

		case KG_TRANSFORM_AXIS_Y:
			MKZ_ARITHMETIC_matrix_rotateX(sense*KG_ROTATE_STEP,n_mat);
			break;

		case KG_TRANSFORM_AXIS_Z:
			MKZ_ARITHMETIC_matrix_rotateZ(sense*KG_ROTATE_STEP,n_mat);
			break;

		}
		break;

	case KG_TRANSFORM_TYPE_SCALE:

		if (sense > 0){
			scaleFactor *= KG_SCALE_STEP;
		}
		else{
			scaleFactor /= KG_SCALE_STEP;
		}

		switch (magnitude){

		case KG_TRANSFORM_AXIS_X:
			MKZ_ARITHMETIC_matrix_scaleX(scaleFactor,n_mat);
			break;

		case KG_TRANSFORM_AXIS_Y:
			MKZ_ARITHMETIC_matrix_scaleY(scaleFactor,n_mat);
			break;

		case KG_TRANSFORM_AXIS_Z:
			MKZ_ARITHMETIC_matrix_scaleZ(scaleFactor,n_mat);
			break;

		}
		break;

	}

	MKZ_GEOMETRY_free_vector3(v3);


	fprintf(stdout,"obj_ptr: %d\n",obj);
	fprintf(stdout,"mkz_obj_ptr: %d\n",mo);
	if (t_scope == KG_TRANSFORM_SCOPE_LOCAL){
		MKZ_TRANSFORM_matrix_local(n_mat,mo->transform);
	}else{
		MKZ_TRANSFORM_matrix_global(n_mat,mo->transform);
	}

	MKZ_ARITHMETIC_print_matrix(mo->transform);

	KG_update_children(obj);
	KG_save_object_matrix(obj);


}

void KG_transform_camera(int axis){

	if (selectedCamera == 0)
		return;

	object * obj = (object *) selectedCamera->content;
	MKZ_object* ca = get_mkz_object(obj);


	int sense = axis;
	int magnitude = axis;

	if (magnitude < 0){
		magnitude = -magnitude;
	}

	sense = sense/magnitude;

	MKZ_vector3 * v3 = MKZ_GEOMETRY_create_vector3();

	float scaleFactor = 1.0f;

	if (t_scope == KG_TRANSFORM_SCOPE_GLOBAL){

		object * objobj = (object *) selectedObject->content;
		MKZ_meshedObject * mo = (MKZ_meshedObject *) objobj->object;
		v3->x = mo->obj.transform[12] - ca->transform[12];
		v3->y = mo->obj.transform[13] - ca->transform[13];
		v3->z = mo->obj.transform[14] - ca->transform[14];

		float dist = MKZ_ARITHMETIC_eulidean_norm_vector(v3);

		v3->x = 0;
		v3->y = 0;


		if (magnitude == KG_TRANSFORM_AXIS_Z){

			v3->z = -KG_TRANSLATE_STEP/MKZ_ARITHMETIC_eulidean_norm(ca->transform+8);

			if (sense == 1){

				if (dist > KG_TRANSLATE_STEP){
					MKZ_TRANSFORM_translate_local(ca->transform,v3);
				}
			}
			else{

				v3->z = -v3->z;
				MKZ_TRANSFORM_translate_local(ca->transform,v3);
			}
		}
		else
		{

			v3->z = -dist/MKZ_ARITHMETIC_eulidean_norm(ca->transform+8);
			switch(magnitude){

			case KG_TRANSFORM_AXIS_X:
				MKZ_TRANSFORM_translate_local(ca->transform,v3);
				MKZ_TRANSFORM_rotateY_local(ca->transform,KG_ROTATE_STEP*sense);
				v3->z = dist/MKZ_ARITHMETIC_eulidean_norm(ca->transform+8);
				MKZ_TRANSFORM_translate_local(ca->transform,v3);
				break;

			case KG_TRANSFORM_AXIS_Y:
				MKZ_TRANSFORM_translate_local(ca->transform,v3);
				MKZ_TRANSFORM_rotateX_local(ca->transform,KG_ROTATE_STEP*sense);
				v3->z = dist/MKZ_ARITHMETIC_eulidean_norm(ca->transform+8);
				MKZ_TRANSFORM_translate_local(ca->transform,v3);
				break;
			}
		}

		v3->x = mo->obj.transform[12];
		v3->y = mo->obj.transform[13];
		v3->z = mo->obj.transform[14];
		MKZ_TRANSFORM_look_at(ca->transform, v3);
	}
	else{
		switch (t_type){

		case KG_TRANSFORM_TYPE_TRANSLATE:

			switch (magnitude){

			case KG_TRANSFORM_AXIS_X:
				v3->x = sense * KG_TRANSLATE_STEP;
				break;

			case KG_TRANSFORM_AXIS_Y:
				v3->y = sense * KG_TRANSLATE_STEP;
				break;

			case KG_TRANSFORM_AXIS_Z:
				v3->z = sense * KG_TRANSLATE_STEP;
				break;

			}

			MKZ_TRANSFORM_translate_local(ca->transform,v3);
			break;

		case KG_TRANSFORM_TYPE_ROTATE:

			switch (magnitude){

			case KG_TRANSFORM_AXIS_X:
				MKZ_TRANSFORM_rotateY_local(ca->transform,-sense*KG_ROTATE_STEP);
				break;

			case KG_TRANSFORM_AXIS_Y:
				MKZ_TRANSFORM_rotateX_local(ca->transform,sense*KG_ROTATE_STEP);
				break;

			case KG_TRANSFORM_AXIS_Z:
				MKZ_TRANSFORM_rotateZ_local(ca->transform,sense*KG_ROTATE_STEP);
				break;

			}
			break;

		case KG_TRANSFORM_TYPE_SCALE:

			if (sense > 0){
				scaleFactor *= KG_SCALE_STEP;
			}
			else{
				scaleFactor /= KG_SCALE_STEP;
			}

			switch (magnitude){

			case KG_TRANSFORM_AXIS_X:
				MKZ_TRANSFORM_scaleX_local(ca->transform,scaleFactor);
				break;

			case KG_TRANSFORM_AXIS_Y:
				MKZ_TRANSFORM_scaleY_local(ca->transform,scaleFactor);
				break;

			case KG_TRANSFORM_AXIS_Z:
				MKZ_TRANSFORM_scaleZ_local(ca->transform,scaleFactor);
				break;

			}
			break;

		}
	}
	float det = MKZ_ARITHMETIC_determinant(ca->transform);
	//printf("det: %f\n",det);
	MKZ_GEOMETRY_free_vector3(v3);

	KG_update_children(obj);
	KG_save_object_matrix(obj);


}




/** Exported part **/
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

		KG_save_object_matrix(obj);

		MKZ_camera * cam = MKZ_OBJECT_create_camera();

		cam->obj.transform[10] = -1;
		cam->obj.transform[13] = 2;

		object * obj_cam = create_object_camera(cam);
		linkedlist_add(&obj->children,obj_cam);

		KG_save_object_matrix(obj_cam);

		if (selectedObject == 0)
			selectedObject = objList;

		return 0;
	}

}

void KG_select_next_object(){

	if (special_function != 0)
		return;

	if (selectedObject == 0)
		return;

	selectedObject = selectedObject->ll_after;

	if (selectedObject == 0){
		selectedObject = objList;
	}



}

void KG_delete_selected_object(){

	if (special_function != 0)
		return;

	if (selectedObject == 0)
		return;

	if (selectedObject->ll_before == 0){

		objList = selectedObject->ll_after;

		if (objList != 0)
			objList->ll_before = 0;

		selectedObject->ll_after = 0;

		object * obj = (object *) selectedObject->content;
		MKZ_meshedObject * mo = (MKZ_meshedObject *) obj->object;
		MKZ_SCENE_remove_mesh(mo->obj.id);

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

		object * obj = (object *) selectedObject->content;
		MKZ_meshedObject * mo = (MKZ_meshedObject *) obj->object;
		MKZ_SCENE_remove_mesh(mo->obj.id);

		free_object_linkedlist(selectedObject);

		selectedObject = ll;

		if (selectedObject == 0){
			selectedObject = objList;
		}
	}


	if (selectedObject == 0 && t_target == KG_TRANSFORM_TARGET_CAMERA){
		t_scope = KG_TRANSFORM_SCOPE_LOCAL;
	}

}

void KG_transform_type_set(int transform_type){

	if (special_function != 0)
		return;

	t_type = transform_type;

}

void KG_transform_scope_set(int transform_scope){


	if (special_function != 0)
			return;

	t_scope = transform_scope;

	if (t_target == KG_TRANSFORM_TARGET_CAMERA){
		if (selectedObject == 0)
			t_scope = KG_TRANSFORM_SCOPE_LOCAL;
		else if (selectedCamera != 0 && t_scope == KG_TRANSFORM_SCOPE_GLOBAL)
		{
			object * obj = (object *) selectedCamera->content;
			MKZ_camera * ca = (MKZ_camera *) obj->object;

			KG_save_object_matrix(obj);

			obj = (object *) selectedObject->content;
			MKZ_meshedObject * mo = (MKZ_meshedObject *) obj->object;

			MKZ_point3 p3;
			p3.x = mo->obj.transform[12];
			p3.y = mo->obj.transform[13];
			p3.z = mo->obj.transform[14];
			MKZ_TRANSFORM_look_at(ca->obj.transform,&p3);
		}

	}


}

void KG_transform_target_set(int transform_target){

	if (special_function != 0)
			return;

	t_target = transform_target;
	t_scope = KG_TRANSFORM_SCOPE_LOCAL;
	t_type = KG_TRANSFORM_TYPE_TRANSLATE;
}



void KG_transform(int axis){

	if (special_function != 0)
			return;

	if (t_target == KG_TRANSFORM_TARGET_CAMERA)
		KG_transform_camera(axis);
	else
		KG_transform_object(axis);

}



void KG_uniform_scale(int sense){

	if (special_function != 0)
		return;

	object * traend = 0;

	switch(t_target){

		case KG_TRANSFORM_TARGET_OBJECT:
			traend = (object*) objList->content;
			break;
		case KG_TRANSFORM_TARGET_CAMERA:
			traend = (object*) cameraList->content;
			break;
		case KG_TRANSFORM_TARGET_LIGHT:
			traend = lightList[selectedLight];
			break;
	}

	if (traend == 0)
		return;

	float s_factor = 1.0f;

	if (sense < 0){
		s_factor /= KG_SCALE_STEP;
	}
	else{
		s_factor *= KG_SCALE_STEP;
	}


	MKZ_object * obj = get_mkz_object(traend);

	if (t_scope == KG_TRANSFORM_SCOPE_GLOBAL){
		MKZ_TRANSFORM_scaleUniform_global(obj->transform,s_factor);
	}
	else{
		MKZ_TRANSFORM_scaleUniform_local(obj->transform,s_factor);
	}

	KG_update_children(traend);
	KG_save_object_matrix(traend);

}

void KG_undo_transformation(){

	if (special_function != 0)
		return;

	object * obj;

	switch(t_target){

		case KG_TRANSFORM_TARGET_OBJECT:

			if (selectedObject == 0)
				return;
			obj = (object *) selectedObject->content;
			break;


		case KG_TRANSFORM_TARGET_CAMERA:
			if (selectedCamera == 0)
				return;
			obj = (object *) selectedCamera->content;
			break;

		case KG_TRANSFORM_TARGET_LIGHT:
			obj = (object *) lightList[selectedLight];
			break;
	}

	if (obj->undoStack->matStack != 0){

		MKZ_object * mkz_obj = get_mkz_object(obj);

		float * n_mat = matStack_pop(&obj->undoStack);
		matStack_push(&obj->redoStack,n_mat);

		MKZ_ARITHMETIC_copy_matrix(obj->undoStack->mat,mkz_obj->transform);
		KG_update_children(obj);
	}
}

void KG_redo_transformation(){

	if (special_function != 0)
		return;

	object * obj;
	MKZ_object * mkz_obj;

	switch(t_target){

			case KG_TRANSFORM_TARGET_OBJECT:

				if (selectedObject == 0)
					return;

				obj = (object *) selectedObject->content;
				mkz_obj = (MKZ_object *)&(((MKZ_meshedObject * ) obj->object)->obj);
				break;


			case KG_TRANSFORM_TARGET_CAMERA:
				if (selectedCamera == 0)
					return;

				obj = (object *) selectedCamera->content;
				mkz_obj = (MKZ_object *)&(((MKZ_camera * ) obj->object)->obj);
				break;

			case KG_TRANSFORM_TARGET_LIGHT:
				if (lightList[selectedLight] == 0)
					return;

				obj = (object *) lightList[selectedLight];
				mkz_obj = (MKZ_object *)&(((MKZ_lightObject * ) obj->object)->obj);
				break;
		}

	if (obj->redoStack != 0){

			float * n_mat = matStack_pop(&obj->redoStack);
			matStack_push(&obj->undoStack,n_mat);

			MKZ_ARITHMETIC_copy_matrix(obj->undoStack->mat,mkz_obj->transform);
			KG_update_children(obj);
	}

}


void KG_next_camera(){

	if (special_function != 0)
		return;

	if (selectedCamera == 0)
		return;

	selectedCamera = selectedCamera->ll_after;

	if (selectedCamera == 0){
		selectedCamera = cameraList;
	}
	object * obj = (object *) selectedCamera->content;
	MKZ_camera * cam = (MKZ_camera *) obj->object;
	MKZ_SCENE_set_camera(cam);


}

void KG_object_camera(){

	if (special_function != 0)
		return;

	if (selectedObject == 0)
		return;

	object * obj = (object *)selectedObject->content;

	linkedList* aux = obj->children;
	MKZ_camera * cam = 0;
	while (aux != 0){

		object * obj_aux = (object *) aux->content;

		if (obj_aux->objectType == KG_OBJECT_TYPE_CAMERA){
			cam = (MKZ_camera *) obj_aux->object;
			break;
		}

		aux = aux->ll_after;
	}

	if (cam != 0){

		MKZ_SCENE_set_camera(cam);
		special_function = KG_SP_FUNC_OBJECT_CAMERA;
	}
}

void KG_camera_camera(){

	if (special_function != KG_SP_FUNC_OBJECT_CAMERA)
		return;

	if (selectedCamera == 0)
		return;

	object * obj = (object *) selectedCamera->content;
	MKZ_camera * cam = (MKZ_camera *) obj->object;
	MKZ_SCENE_set_camera(cam);
	special_function = 0;


}


void KG_switch_camera_projection(){


	if (selectedCamera == 0)
		return;

	MKZ_camera * cam = MKZ_SCENE_get_camera();

	if (cam->projection_mode == MKZ_PROJECTIONMODE_PARALLEL){
		cam->projection_mode = MKZ_PROJECTIONMODE_PERSPECTIVE;
	}
	else{
		cam->projection_mode = MKZ_PROJECTIONMODE_PARALLEL;
	}

}

void KG_lighting_switch(){

	MKZ_camera * cam =  MKZ_SCENE_get_default_camera();

	cam->lighting_enable = 1 - cam->lighting_enable;
}


void KG_lights_switch(int l_index){

	if (lightList[l_index] == 0)
		return;

	MKZ_object * obj = get_mkz_object(lightList[l_index]);

	obj->active = 1 - obj->active;
}


void KG_light_select(int l_index){

	selectedLight = l_index;
}


void KG_switch_light_type(){

	if (lightList[selectedLight] == 0)
		return;

	MKZ_lightObject * lo = (MKZ_lightObject *) lightList[selectedLight]->object;

	lo->light_type = (lo->light_type + 1) % 3;


}


void KG_switch_lighting_mode(){

	MKZ_camera * cam =  MKZ_SCENE_get_default_camera();

	if (cam->lighting_mode == MKZ_LIGHTING_FLAT)
		cam->lighting_mode = MKZ_LIGHTING_SMOOTH;
	else
		cam->lighting_mode = MKZ_LIGHTING_FLAT;
}


/** Getters **/
int KG_get_transformation_target(){
	return t_target;
}

int KG_get_transformation_scope(){
	return t_scope;
}

int KG_get_transformation_type(){
	return t_type;
}

MKZ_meshedObject * KG_get_selected_object(){

	if (selectedObject == 0)
		return 0;

	object * obj = (object*) selectedObject->content;
	MKZ_meshedObject * mo = (MKZ_meshedObject*) obj->object;

	return mo;
}

MKZ_lightObject * KG_get_selected_light(){

	object * obj = lightList[selectedLight];
	MKZ_lightObject * lo = (MKZ_lightObject *)obj->object;
	return lo;
}

MKZ_camera * KG_get_selected_camera(){

	if (selectedCamera == 0)
		return 0;

	object * obj = (object*) selectedCamera->content;
	MKZ_camera * ca = (MKZ_camera*) obj->object;

	return ca;
}


void KG_create_camera(){

	MKZ_camera * cam = MKZ_OBJECT_create_camera();
	object * obj = create_object_camera(cam);
	linkedlist_add(&cameraList, obj);

	selectedCamera = cameraList;
	MKZ_SCENE_set_camera(cam);
}
