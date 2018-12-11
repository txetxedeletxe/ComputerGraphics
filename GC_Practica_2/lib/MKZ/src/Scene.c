#include "MKZ_Arithmetic.h"
#include "MKZ_Datastruct.h"
#include "MKZ_Objects.h"
#include "MKZ_Draw.h"

/** Internal state **/
/** camera **/
MKZ_camera * camera;

/** object **/
linkedList * objectList;

/** lights **/
linkedList * lightList;

/** Exported **/
/* Init */
void MKZ_SCENE_init(){


		objectList = 0;
		lightList = 0;

		camera = MKZ_create_camera();
}

/** Callback **/
void SCENE_draw();

/* camera */
void SCENE_set_camera(MKZ_camera * cam);
MKZ_camera * SCENE_get_camera();
void SCENE_reset_camera();

/* Objects */
void SCENE_add_mesh(MKZ_meshedObject * mo);
MKZ_meshedObject * SCENE_get_mesh(int id);
void SCENE_remove_mesh(int id);

/* Light */
void SCENE_add_light(MKZ_lightObject * lo);
MKZ_lightObject * SCENE_get_light(int id);
void SCENE_remove_light(int id);

/* MISC */
void SCENE_set_bg_color(MKZ_color3 * c3);
void SCENE_set_projectionMode(int projection_mode);
void SCENE_set_poligonMode(int poligon_mode);
void SCENE_set_drawMask(unsigned int mask);



float * DgetCameraTransform(){
	return camera_mat;

}

/** Exposed functions **/
void Dinit(){


}

/** callback **/
void Ddraw(){


	DTstartDrawing();
	DTclearScreen();

	linkedList * aux = objectList;

	while (aux != 0){
		DTdrawObject((meshed_object *)aux->content);
		aux = aux->ll;
	}

	DTendDrawing();

}


/* Objects */
int DaddObject(meshed_object * mo){

	linkedList * ll = DScreateLinkedList(mo,objNextId++);
	ll->ll  = objectList;
	objectList = ll;
	return ll->id;
}

meshed_object * DgetObject(int id){

	linkedList * aux = objectList;

	while (aux != 0){

		if (aux->id == id){
			return (meshed_object*) aux->content;
		}
		aux = aux->ll;
	}

	return 0;

}

void DremoveObject(int id){

	linkedList * aux = objectList;

	if (aux == 0)
		return;

	if (aux->id == id){
		objectList = aux->ll;
		return;
	}

	linkedList * aux2 = aux;
	aux = aux->ll;

	while (aux != 0){

			if (aux->id == id){
				aux2->ll = aux->ll;
				return;
			}
			aux2 = aux;
			aux = aux->ll;
		}


}

/* Light */
int DaddLight(light_object * lo){

	linkedList * ll = DScreateLinkedList(lo,lightNextId++);
	ll->ll  = lightList;
	lightList = ll;
	return ll->id;

}

light_object * DgetLight(int id){

	linkedList * aux = lightList;

		while (aux != 0){

			if (aux->id == id){
				return (light_object *) aux->content;
			}
			aux = aux->ll;
		}

		return 0;
}

void DremoveLight(int id){

	linkedList * aux = lightList;

		if (aux == 0)
			return;


		if (aux->id == id){
			objectList = aux->ll;
			return;
		}

		linkedList * aux2 = aux;
		aux = aux->ll;

		while (aux != 0){

				if (aux->id == id){
					aux2->ll = aux->ll;
					return;
				}
				aux2 = aux;
				aux = aux->ll;
			}

}
