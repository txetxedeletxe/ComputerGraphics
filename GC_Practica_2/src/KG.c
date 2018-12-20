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

/** Internal state */
/* objects */
linkedList * cameraList;
linkedList * objList;
object lightList[8];

linkedList * selectedCamera;
linkedList * selectedObject;
int selectedLight;


/** transform state **/
int t_type;
int t_scope;
int t_target;


/** Private Functions **/
void __KG_init(){

	cameraList = 0;
	objList = 0;
	selectedLight = 0;
	selectedCamera = 0;
	selectedObject = 0;

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

	v3->x = 0;
	v3->y = 0;
	v3->z = 15;

	MKZ_TRANSFORM_translate_global(cam->obj.transform,v3);

	MKZ_SCENE_set_camera(cam);

	object * obj = create_object_camera(cam);

	linkedlist_add(&cameraList,obj);
	selectedCamera = cameraList;

	free(v3);
}

void KG_save_object_matrix(object * obj, MKZ_object * mkz_obj){

	/** copy matrix to stack */


	float * mat = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_copy_matrix(mkz_obj->transform,mat);
	matStack_push(&obj->undoStack,mat);

	/**cannot redo **/
	free_matstack(obj->redoStack);
	obj->redoStack = 0;

}



void KG_transform_object(int axis){

	if (selectedObject != 0){

		object * obj = (object *) selectedObject->content;
		MKZ_meshedObject * mo = (MKZ_meshedObject *) obj->object;

		KG_save_object_matrix(obj,&mo->obj);

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


		if (t_scope == KG_TRANSFORM_SCOPE_LOCAL){
			MKZ_TRANSFORM_matrix_local(n_mat,mo->obj.transform);
		}else{
			//printf("t_c : %d \n", t_scope);
			MKZ_TRANSFORM_matrix_global(n_mat,mo->obj.transform);
		}


	}

}

void KG_transform_camera(int axis){

	if (selectedCamera != 0){


		object * obj = (object *) selectedCamera->content;
		MKZ_camera* ca = (MKZ_camera *) obj->object;

		KG_save_object_matrix(obj,&ca->obj);


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
			v3->x = mo->obj.transform[12] - ca->obj.transform[12];
			v3->y = mo->obj.transform[13] - ca->obj.transform[13];
			v3->z = mo->obj.transform[14] - ca->obj.transform[14];

			float dist = MKZ_ARITHMETIC_eulidean_norm_vector(v3);

			v3->x = 0;
			v3->y = 0;


			if (magnitude == KG_TRANSFORM_AXIS_Z){

				v3->z = -KG_TRANSLATE_STEP/MKZ_ARITHMETIC_eulidean_norm(ca->obj.transform+8);

				if (sense == 1){

					if (dist > KG_TRANSLATE_STEP){
						MKZ_TRANSFORM_translate_local(ca->obj.transform,v3);
					}
				}
				else{

					v3->z = -v3->z;
					MKZ_TRANSFORM_translate_local(ca->obj.transform,v3);
				}
			}
			else
			{

				v3->z = -dist/MKZ_ARITHMETIC_eulidean_norm(ca->obj.transform+8);
				switch(magnitude){

				case KG_TRANSFORM_AXIS_X:
					MKZ_TRANSFORM_translate_local(ca->obj.transform,v3);
					MKZ_TRANSFORM_rotateY_local(ca->obj.transform,KG_ROTATE_STEP*sense);
					v3->z = dist/MKZ_ARITHMETIC_eulidean_norm(ca->obj.transform+8);
					MKZ_TRANSFORM_translate_local(ca->obj.transform,v3);
					break;

				case KG_TRANSFORM_AXIS_Y:
					MKZ_TRANSFORM_translate_local(ca->obj.transform,v3);
					MKZ_TRANSFORM_rotateX_local(ca->obj.transform,KG_ROTATE_STEP*sense);
					v3->z = dist/MKZ_ARITHMETIC_eulidean_norm(ca->obj.transform+8);
					MKZ_TRANSFORM_translate_local(ca->obj.transform,v3);
					break;
				}
			}

			v3->x = mo->obj.transform[12];
			v3->y = mo->obj.transform[13];
			v3->z = mo->obj.transform[14];
			MKZ_TRANSFORM_look_at(ca->obj.transform, v3);
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

				MKZ_TRANSFORM_translate_local(ca->obj.transform,v3);
				break;

			case KG_TRANSFORM_TYPE_ROTATE:

				switch (magnitude){

				case KG_TRANSFORM_AXIS_X:
					MKZ_TRANSFORM_rotateY_local(ca->obj.transform,-sense*KG_ROTATE_STEP);
					break;

				case KG_TRANSFORM_AXIS_Y:
					MKZ_TRANSFORM_rotateX_local(ca->obj.transform,sense*KG_ROTATE_STEP);
					break;

				case KG_TRANSFORM_AXIS_Z:
					MKZ_TRANSFORM_rotateZ_local(ca->obj.transform,sense*KG_ROTATE_STEP);
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
					MKZ_TRANSFORM_scaleX_local(ca->obj.transform,scaleFactor);
					break;

				case KG_TRANSFORM_AXIS_Y:
					MKZ_TRANSFORM_scaleY_local(ca->obj.transform,scaleFactor);
					break;

				case KG_TRANSFORM_AXIS_Z:
					MKZ_TRANSFORM_scaleZ_local(ca->obj.transform,scaleFactor);
					break;

				}
				break;

			}
		}
		float det = MKZ_ARITHMETIC_determinant(ca->obj.transform);
		//printf("det: %f\n",det);
		MKZ_GEOMETRY_free_vector3(v3);

	}


}

void KG_transform_light(int axis){

}

void KG_uniform_scale_object(int sense){

	if (selectedObject != 0){

		object * obj = (object *) selectedObject->content;
		MKZ_meshedObject * mo = (MKZ_meshedObject * ) obj->object;

		KG_save_object_matrix(obj,&mo->obj);

		float f = 1.0f;

		if (sense < 0){
			f /= KG_SCALE_STEP;
		}
		else{
			f *= KG_SCALE_STEP;
		}

		if (t_scope == KG_TRANSFORM_SCOPE_GLOBAL){
			MKZ_TRANSFORM_scaleUniform_global(mo->obj.transform,f);
		}else{
			MKZ_TRANSFORM_scaleUniform_local(mo->obj.transform,f);
		}
	}
}

void KG_uniform_scale_camera(int sense){

	if (selectedCamera != 0){

			object * obj = (object *) selectedCamera->content;
			MKZ_camera * ca = (MKZ_camera * ) obj->object;

			KG_save_object_matrix(obj,&ca->obj);

			float f = 1.0f;

			if (sense < 0){
				f /= KG_SCALE_STEP;
			}
			else{
				f *= KG_SCALE_STEP;
			}

			if (t_scope == KG_TRANSFORM_SCOPE_GLOBAL){
				MKZ_TRANSFORM_scaleUniform_global(ca->obj.transform,f);
			}else{
				MKZ_TRANSFORM_scaleUniform_local(ca->obj.transform,f);
			}
		}

}

void KG_uniform_scale_light(int sense){

	if (selectedObject != 0){

		MKZ_meshedObject * lo = (MKZ_meshedObject * ) lightList[selectedLight].object;

		KG_save_object_matrix(&lightList[selectedLight],&lo->obj);

		float f = 1.0f;

		if (sense < 0){
			f /= KG_SCALE_STEP;
		}
		else{
			f *= KG_SCALE_STEP;
		}

		if (t_scope == KG_TRANSFORM_SCOPE_GLOBAL){
			MKZ_TRANSFORM_scaleUniform_global(lo->obj.transform,f);
		}else{
			MKZ_TRANSFORM_scaleUniform_local(lo->obj.transform,f);
		}
	}

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
	}

	if (selectedObject == 0 && t_target == KG_TRANSFORM_TARGET_CAMERA){
		t_scope = KG_TRANSFORM_SCOPE_LOCAL;
	}

}

void KG_transform_type_set(int transform_type){

	t_type = transform_type;

}

void KG_transform_scope_set(int transform_scope){
	t_scope = transform_scope;

	if (t_target == KG_TRANSFORM_TARGET_CAMERA){
		if (selectedObject == 0)
			t_scope = KG_TRANSFORM_SCOPE_LOCAL;
		else if (selectedCamera != 0 && t_scope == KG_TRANSFORM_SCOPE_GLOBAL)
		{
			object * obj = (object *) selectedCamera->content;
			MKZ_camera * ca = (MKZ_camera *) obj->object;

			KG_save_object_matrix(obj,&ca->obj);

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
	t_target = transform_target;
	t_scope = KG_TRANSFORM_SCOPE_LOCAL;
	t_type = KG_TRANSFORM_TYPE_TRANSLATE;
}



void KG_transform(int axis){

	switch(t_target){

	case KG_TRANSFORM_TARGET_OBJECT:
		KG_transform_object(axis);
		break;
	case KG_TRANSFORM_TARGET_CAMERA:
		KG_transform_camera(axis);
		break;
	case KG_TRANSFORM_TARGET_LIGHT:
		KG_transform_light(axis);
		break;
	}

}



void KG_uniform_scale(int sense){

	switch(t_target){

		case KG_TRANSFORM_TARGET_OBJECT:
			KG_uniform_scale_object(sense);
			break;
		case KG_TRANSFORM_TARGET_CAMERA:
			KG_uniform_scale_camera(sense);
			break;
		case KG_TRANSFORM_TARGET_LIGHT:
			KG_uniform_scale_light(sense);
			break;
		}
}

void KG_undo_transformation(){

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

			obj = (object *) &lightList[selectedLight];
			mkz_obj = (MKZ_object *)&(((MKZ_lightObject * ) obj->object)->obj);
			break;
	}

	if (obj->undoStack != 0){

		matStack_push(&obj->redoStack,mkz_obj->transform);
		float * n_mat = matStack_pop(&obj->undoStack);
		mkz_obj->transform = n_mat;
	}
}

void KG_redo_transformation(){

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
				if (selectedLight == 0)
					return;

				obj = (object *) &lightList[selectedLight];
				mkz_obj = (MKZ_object *)&(((MKZ_lightObject * ) obj->object)->obj);
				break;
		}

	if (obj->redoStack != 0){

			matStack_push(&obj->undoStack,mkz_obj->transform);
			float * n_mat = matStack_pop(&obj->redoStack);
			mkz_obj->transform = n_mat;
		}

}


void KG_next_camera(){

	if (selectedCamera != 0){
		selectedCamera = selectedCamera->ll_after;

		if (selectedCamera == 0){
			selectedCamera = cameraList;
		}
		object * obj = (object *) selectedCamera->content;
		MKZ_camera * cam = (MKZ_camera *) obj->object;
		MKZ_SCENE_set_camera(cam);

	}
}

void KG_object_camera(){

}

void KG_camera_camera(){

}


void KG_switch_camera_projection(){

	//printf("here\n");
	if (selectedCamera != 0){
		//printf("also here\n");
		object * obj = (object *)selectedCamera->content;
		MKZ_camera * cam = (MKZ_camera *) obj->object;
		if (cam->projection_mode == MKZ_PROJECTIONMODE_PARALLEL)
			cam->projection_mode = MKZ_PROJECTIONMODE_PERSPECTIVE;
		else
			cam->projection_mode = MKZ_PROJECTIONMODE_PARALLEL;
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


	object * obj = (object *)lightList[selectedLight].object;
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
