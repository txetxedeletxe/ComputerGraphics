#include "MKZ_Arithmetic.h"
#include "MKZ_Transform.h"
#include "MKZ_Draw.h"
#include "MKZ_Definitions.h"

#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

/** Internal state **/
/** camera **/
float * identity_mat;
float * baseChange_mat;

int projection_mode;

double c_left, c_right;
double c_bottom, c_top;
double c_near, c_far;

int next_light;
int lighting_mode;
int lighting_enabled;

void MKZ_DRAW_init(){


	identity_mat = MKZ_ARITHMETIC_create_matrix();
	MKZ_ARITHMETIC_identityMatrix(identity_mat);
	baseChange_mat = identity_mat;

	projection_mode = MKZ_PROJECTIONMODE_PARALLEL;

	c_left 		= -1;
	c_right 	= 1;
	c_bottom 	= -1;
	c_top 		= 1;
	c_near 		= 1;
	c_far 		= 1000;

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glClearColor(0, 0, 0, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	next_light = 0;
	lighting_enabled = 0;
	lighting_mode = MKZ_LIGHTING_FLAT;

	GLfloat mat_ambient[] = {0.2, 0.2, 0.2, 1.0};
	GLfloat mat_difuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat mat_specular[] = { 0, 0, 0, 1 };
	GLfloat mat_shininess[] = { 100.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_difuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

}

void MKZ_DRAW_set_projectionMode(int p_mode){

	projection_mode = p_mode;

}

void MKZ_DRAW_set_poligonMode(int p_mode){

	glPolygonMode(GL_FRONT_AND_BACK , p_mode);


}

void MKZ_DRAW_set_culling(int boolean){

	if (boolean){
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}
	else{
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}
}

void MKZ_DRAW_set_renderVolume(double left, double right, double bottom, double top, double near, double far){

	c_left 		=  left;
	c_right 	=  right;
	c_bottom 	=  bottom;
	c_top 		=  top;
	c_near 		=  near;
	c_far 		=  far;

}

void MKZ_DRAW_set_cameraMat(float * camMat){
	MKZ_TRANSFORM_to_cameraMatrix(camMat,baseChange_mat);
}

void MKZ_DRAW_reset_identity_camera(){
	baseChange_mat = identity_mat;
}

void MKZ_DRAW_set_background_color(MKZ_color3 * bg){

	glClearColor(bg->r, bg->g, bg->b, 1);
}

void MKZ_DRAW_set_lighting(int boolean){

	if (boolean){
		glEnable(GL_LIGHTING);
		//printf("Enabled");
		lighting_enabled = 1;
	}
	else{
		glDisable(GL_LIGHTING);
		lighting_enabled = 0;
	}

}

void MKZ_DRAW_set_lighting_mode(int mode){
	if (mode == MKZ_LIGHTING_FLAT){
		glShadeModel(GL_FLAT);
	} else if (mode == MKZ_LIGHTING_SMOOTH){
		glShadeModel(GL_SMOOTH);
	} else if (mode == MKZ_LIGHTING_RAY_TRACED){
		printf("Sorry, the ray-traced lighting feature is not ready yet.\n");
	}

	lighting_mode = mode;
}

void MKZ_DRAW_start(){

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//fprintf(stdout,"P_mode : %d\n", projection_mode);
	if (projection_mode == MKZ_PROJECTIONMODE_PARALLEL){

		glOrtho(c_left,c_right,c_bottom,c_top,c_near,c_far);
	}
	else
	{
		glFrustum(c_left,c_right,c_bottom,c_top,c_near,c_far);
	}


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void MKZ_DRAW_clear(){
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

}

void MKZ_DRAW_object(MKZ_meshedObject * mo){

	glLoadMatrixf(baseChange_mat);
	glMultMatrixf(mo->obj.transform);



	MKZ_mesh * mesh = mo->mesh;
	int f;
	int v;
	int v_index;

	float face_normals[mesh->num_faces][3];
	float vertex_normals[mesh->num_vertices][3];

	MKZ_vector3 v1;
	MKZ_vector3 v2;
	MKZ_vector3 v3;

	if (lighting_enabled){

		for (v = 0 ; v < mesh->num_vertices ; v++){
			vertex_normals[v][0] = 0;
			vertex_normals[v][1] = 0;
			vertex_normals[v][2] = 0;
		}

		for (f = 0 ; f < mesh->num_faces ; f++){

			MKZ_face face =  mesh->face_table[f];

			v1.x = mesh->vertex_table[face.vertex_table[1]].coord.x - mesh->vertex_table[face.vertex_table[0]].coord.x;
			v1.y = mesh->vertex_table[face.vertex_table[1]].coord.y - mesh->vertex_table[face.vertex_table[0]].coord.y;
			v1.z = mesh->vertex_table[face.vertex_table[1]].coord.z - mesh->vertex_table[face.vertex_table[0]].coord.z;

			v2.x = mesh->vertex_table[face.vertex_table[2]].coord.x - mesh->vertex_table[face.vertex_table[0]].coord.x;
			v2.y = mesh->vertex_table[face.vertex_table[2]].coord.y - mesh->vertex_table[face.vertex_table[0]].coord.y;
			v2.z = mesh->vertex_table[face.vertex_table[2]].coord.z - mesh->vertex_table[face.vertex_table[0]].coord.z;

			MKZ_ARITHMETIC_corssProduct_vector(&v1,&v2,&v3);

			for (v = 0 ; v < face.num_vertices ; v++){
				v_index = face.vertex_table[v];
				vertex_normals[v_index][0] += v3.x;
				vertex_normals[v_index][1] += v3.y;
				vertex_normals[v_index][2] += v3.z;
			}

			MKZ_ARITHMETIC_normalize_vector(&v3);
			face_normals[f][0] = v3.x;
			face_normals[f][1] = v3.y;
			face_normals[f][2] = v3.z;
		}

		for (v = 0 ; v < mesh->num_vertices ; v++){
			v3.x = vertex_normals[v][0];
			v3.y = vertex_normals[v][1];
			v3.z = vertex_normals[v][2];

			MKZ_ARITHMETIC_normalize_vector(&v3);

			vertex_normals[v][0] = v3.x;
			vertex_normals[v][1] = v3.y;
			vertex_normals[v][2] = v3.z;

		}

	}


	for (f = 0; f < mesh->num_faces; f++) {
		glBegin(GL_POLYGON);
		if (lighting_enabled && lighting_mode == MKZ_LIGHTING_FLAT)
			glNormal3f(face_normals[f][0], face_normals[f][1], face_normals[f][2]);

		for (v = 0; v < mesh->face_table[f].num_vertices; v++) {

			v_index = mesh->face_table[f].vertex_table[v];
			if (lighting_enabled && lighting_mode == MKZ_LIGHTING_SMOOTH)
				glNormal3f(vertex_normals[v_index][0], vertex_normals[v_index][1], vertex_normals[v_index][2]);
			glVertex3d(mesh->vertex_table[v_index].coord.x,
					mesh->vertex_table[v_index].coord.y,
					mesh->vertex_table[v_index].coord.z);
		}

		glEnd();
	}
}

void MKZ_DRAW_clear_lights(){

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
	glDisable(GL_LIGHT7);

	next_light = 0;


}

void MKZ_DRAW_add_light(MKZ_lightObject * lo){


	glLoadMatrixf(baseChange_mat);

	GLenum light_ind;
	float f[4];
	switch(next_light){

		case 0:
			light_ind = GL_LIGHT0;
			break;
		case 1:
			light_ind = GL_LIGHT1;
			break;
		case 2:
			light_ind = GL_LIGHT2;
			break;
		case 3:
			light_ind = GL_LIGHT3;
			break;
		case 4:
			light_ind = GL_LIGHT4;
			break;
		case 5:
			light_ind = GL_LIGHT5;
			break;
		case 6:
			light_ind = GL_LIGHT6;
			break;
		case 7:
			light_ind = GL_LIGHT7;
			break;

	}

	glEnable(light_ind);

	if (lo->light_type != MKZ_LIGHT_TYPE_DIRECTIONAL)
		glLightfv(light_ind, GL_POSITION, lo->obj.transform+12);
	else{


		f[0] = -lo->obj.transform[8];
		f[1] = -lo->obj.transform[9];
		f[2] = -lo->obj.transform[10];
		f[3] = 0;

		glLightfv(light_ind, GL_POSITION, f);

	}

	f[0] = lo->color.r * lo->intensityAmbient;
	f[1] = lo->color.g * lo->intensityAmbient;
	f[2] = lo->color.b * lo->intensityAmbient;
	f[3] = 1;

	glLightfv(light_ind, GL_AMBIENT, f);

	f[0] = lo->color.r * lo->intensityDifuse;
	f[1] = lo->color.g * lo->intensityDifuse;
	f[2] = lo->color.b * lo->intensityDifuse;
	f[3] = 1;


	glLightfv(light_ind, GL_DIFFUSE, f);

	f[0] = lo->color.r * lo->intensitySpecular;
	f[1] = lo->color.g * lo->intensitySpecular;
	f[2] = lo->color.b * lo->intensitySpecular;
	f[3] = 1;

	glLightfv(light_ind, GL_SPECULAR, f);


	glLightf(light_ind, GL_CONSTANT_ATTENUATION, lo->atenuationConstant);
	glLightf(light_ind, GL_LINEAR_ATTENUATION, 	lo->atenuationLinear);
	glLightf(light_ind, GL_QUADRATIC_ATTENUATION, lo->atenuationQuadratic);

	if (lo->light_type == MKZ_LIGHT_TYPE_FOCAL){

		f[0] = -lo->obj.transform[8];
		f[1] = -lo->obj.transform[9];
		f[2] = -lo->obj.transform[10];
		f[3] = 0;

		glLightfv(light_ind, GL_SPOT_DIRECTION, f);

		float det = MKZ_ARITHMETIC_determinant(lo->obj.transform);
		//printf("det: %f\n",det);

		float a = 1.0/10.0f;

		det = (75.0/(1.0+exp(-a*(log(det)-2)))) +15; //Funcion sigmoide parametrizada

		//printf("det: %f\n",det);

		if (det > 90)
			det = 90;

		if (det < 15)
			det = 15;

		glLightf(light_ind, GL_SPOT_CUTOFF, det);

		glLightf(light_ind, GL_SPOT_EXPONENT, lo->spotExponent);
	}

	next_light++;
}

void MKZ_DRAW_enable_drawMask(unsigned int d_mask){
	glEnable(d_mask);
}
void MKZ_DRAW_disable_drawMask(unsigned int d_mask){
	glDisable(d_mask);
}

void MKZ_DRAW_end(){
	glutSwapBuffers();
}