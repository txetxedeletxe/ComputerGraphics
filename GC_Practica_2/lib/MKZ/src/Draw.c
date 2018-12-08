#include "Draw.h"
#include "Utilities.h"
#include "Datastruct.h"

/** Internal state **/
/** camera **/
float * camera_mat;

/** object **/
int objNextId;
linkedList * objectList;

/** lights **/
int lightNextId;
linkedList * lightList;

void DsetCameraTransform(float * camMat){
	UTvectorCP(camMat,camera_mat,16);
	DTsetCamera(camera_mat);
}

float * DgetCameraTransform(){
	return camera_mat;

}

/** Exposed functions **/
void Dinit(){

	objNextId = 0;
	objectList = 0;
	lightList = 0;
	lightNextId = 0;

	camera_mat = UTcreateVector(16);
	UTmatIden(camera_mat,4);
	DTinit();
	DTsetCamera(camera_mat);
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
