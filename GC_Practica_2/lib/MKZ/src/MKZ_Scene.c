#include "MKZ_Definitions.h"
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

unsigned int global_mask;
/** Exported **/
/* Init */

void MKZ_SCENE_init(){


		objectList = 0;
		lightList = 0;
		global_mask = 0;

		default_camera = MKZ_OBJECT_create_camera();
		camera = default_camera;

		MKZ_DRAW_init();

}

void MKZ_SCENE_draw(){

		MKZ_camera * aux_camera = 0;
		aux_camera = ((global_mask & MKZ_GLOBAL_BG_COLOR) != 0) ? default_camera : camera;
		MKZ_DRAW_set_background_color(&aux_camera->skybox);

		aux_camera = ((global_mask & MKZ_GLOBAL_PROJECTION) != 0) ? default_camera : camera;
		MKZ_DRAW_set_projectionMode(aux_camera->projection_mode);

		aux_camera = ((global_mask & MKZ_GLOBAL_POLYGON) != 0) ? default_camera : camera;
		MKZ_DRAW_set_poligonMode(aux_camera->polygon_mode);

		aux_camera  = ((global_mask & MKZ_GLOBAL_CULLING) != 0) ? default_camera : camera;
		MKZ_DRAW_set_culling(aux_camera->culling_enabled);

		aux_camera = ((global_mask & MKZ_GLOBAL_TRANSFORM) != 0) ? default_camera : camera;
		MKZ_DRAW_set_cameraMat(aux_camera->obj.transform);

		aux_camera = ((global_mask & MKZ_GLOBAL_LIGHTING_ENABLE) != 0) ? default_camera : camera;
		MKZ_DRAW_set_lighting(aux_camera->lighting_enable);

		aux_camera = ((global_mask & MKZ_GLOBAL_LIGHTING_MODE) != 0) ? default_camera : camera;
		MKZ_DRAW_set_lighting_mode(aux_camera->lighting_mode);

		aux_camera = ((global_mask & MKZ_GLOBAL_RENDER_VOLUME) != 0) ? default_camera : camera;
		MKZ_DRAW_set_renderVolume(-aux_camera->v_x/2,aux_camera->v_x/2,
				-aux_camera->v_y/2,aux_camera->v_y/2,
				aux_camera->v_near,aux_camera->v_far);

		MKZ_DRAW_clear();
		MKZ_DRAW_start();

		MKZ_DRAW_clear_lights();

		MKZ_linkedList * aux = lightList;

		while (aux != 0){
					//printf("aux: %d\n",aux);
					MKZ_lightObject * lo = (MKZ_lightObject *)aux->content;
					if (lo->obj.active){
						MKZ_DRAW_add_light(lo);
					}
					aux = aux->ll;

		}

		aux = objectList;

		while (aux != 0){
			//printf("aux: %d\n",aux);
			MKZ_meshedObject * lo = (MKZ_meshedObject *)aux->content;
			if (lo->obj.active){
				MKZ_DRAW_object(lo);
			}
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

MKZ_camera * MKZ_SCENE_get_default_camera(){

	return default_camera;

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
		lightList = aux->ll;
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

void MKZ_SCENE_set_global_mask(unsigned int g_mask){
	global_mask = g_mask;
}

unsigned int MKZ_SCENE_get_global_mask(){
	return global_mask;
}

