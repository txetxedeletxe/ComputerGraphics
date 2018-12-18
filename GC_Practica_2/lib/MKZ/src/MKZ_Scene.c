#include "MKZ_Datastruct.h"
#include "MKZ_Objects.h"
#include "MKZ_Draw.h"

#include <stdlib.h>
#include <unistd.h>

/** Internal state **/
/** camera **/
MKZ_camera * default_camera;
MKZ_camera * camera;

/** object **/
MKZ_linkedList * objectList;

/** lights **/
MKZ_linkedList * lightList;

/** Exported **/
/* Init */
void MKZ_SCENE_init(){


		objectList = 0;
		lightList = 0;
		default_camera = MKZ_OBJECT_create_camera();
		camera = default_camera;

		MKZ_DRAW_init();

}

void MKZ_SCENE_draw(){


		//MKZ_DRAW_set_background_color(bg_color);
		//MKZ_DRAW_set_projectionMode(projection_mode);
		MKZ_DRAW_set_cameraMat(camera->obj.transform);


		MKZ_DRAW_clear();
		MKZ_DRAW_start();


		MKZ_linkedList * aux = objectList;


		while (aux != 0){

			MKZ_DRAW_object((MKZ_meshedObject *)aux->content);
			aux = aux->ll;
		}



		MKZ_DRAW_end();
}

void MKZ_SCENE_add_mesh(MKZ_meshedObject * mo){

		MKZ_linkedList * ll = MKZ_DATASTRUCT_create_linkedList();
		ll->content = mo;
		ll->ll  = objectList;
		objectList = ll;


}

void MKZ_SCENE_add_light(MKZ_lightObject * lo){

		MKZ_linkedList * ll = MKZ_DATASTRUCT_create_linkedList();
		ll->content = lo;
		ll->ll  = lightList;
		lightList = ll;

}

void MKZ_SCENE_set_camera(MKZ_camera * ca){
	camera = ca;
}

MKZ_meshedObject *  MKZ_SCENE_get_mesh(int id){

	MKZ_linkedList * aux = objectList;

	MKZ_meshedObject * mo;
	while (aux != 0){

		mo = (MKZ_meshedObject * )aux->content;
		if (mo->obj.id == id){
			return mo;
		}
		aux = aux->ll;
	}

	return 0;
}

MKZ_lightObject * MKZ_SCENE_get_light(int id){

	MKZ_linkedList * aux = lightList;

	MKZ_lightObject * lo;
		while (aux != 0){

			lo = (MKZ_lightObject * )aux->content;
			if (lo->obj.id == id){
				return lo;
			}
			aux = aux->ll;
		}

		return 0;

}

MKZ_camera * MKZ_SCENE_get_camera(){
	return camera;
}

void MKZ_SCENE_remove_mesh(int id){

	MKZ_linkedList * aux = objectList;


	if (aux == 0)
		return;

	MKZ_meshedObject * mo = (MKZ_meshedObject *)aux->content;

	if (mo->obj.id == id){
		objectList = aux->ll;
		free(aux);
		return;
	}

	MKZ_linkedList * aux2 = aux;
	aux = aux->ll;

	while (aux != 0){
			mo = (MKZ_meshedObject *)aux->content;
			if (mo->obj.id == id){
				aux2->ll = aux->ll;
				free(aux);
				return;
			}
			aux2 = aux;
			aux = aux->ll;
		}

}

void MKZ_SCENE_remove_light(int id){

	MKZ_linkedList * aux = lightList;

	if (aux == 0)
		return;

	MKZ_lightObject * lo = (MKZ_lightObject *)aux->content;

	if (lo->obj.id == id){
		objectList = aux->ll;
		free(aux);
		return;
	}

	MKZ_linkedList * aux2 = aux;
	aux = aux->ll;

	while (aux != 0){
		lo = (MKZ_lightObject *)aux->content;
		if (lo->obj.id == id){
			aux2->ll = aux->ll;
			free(aux);
			return;
		}
		aux2 = aux;
		aux = aux->ll;
	}

}

void MKZ_SCENE_restore_camera(){

	camera = default_camera;

}



