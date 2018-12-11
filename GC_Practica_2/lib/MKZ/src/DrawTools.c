#include <Arithmetic.h>
#include "DrawTools.h"
#include "Transform.h"

#include <GL/gl.h>

/** Internal state **/
/** camera **/
float * baseChange_mat;

int projection_mode;

double c_left, c_right;
double c_bottom, c_top;
double c_near, c_far;


void DTinit(){


	baseChange_mat = UTcreateVector(16);
	UTmatIden(baseChange_mat,4);

	projection_mode = DT_PROJECTIONMODE_PARALLEL;

	c_left 		= -1;
	c_right 	= 1;
	c_bottom 	= -1;
	c_top 		= 1;
	c_near 		= -1;
	c_far 		= 1;

	glClearColor(0, 0, 0, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

}

void DTsetProjectionMode(int p_mode){

	projection_mode = p_mode;

}

void DTsetDrawVolume(double left, double right, double bottom, double top, double near, double far){

	c_left 		=  left;
	c_right 	=  right;
	c_bottom 	=  bottom;
	c_top 		=  top;
	c_near 		=  near;
	c_far 		=  far;

}

void DTsetCamera(float * camMat){
	TRtoCameraMatrix(camMat,baseChange_mat);
}

void DTsetBackgroundColor(MKZ_color3 * bg){

	glClearColor(bg->r, bg->g, bg->b, 1);
}


void DTstartDrawing(){


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (projection_mode == DT_PROJECTIONMODE_PARALLEL){
		glOrtho(c_left,c_right,c_bottom,c_top,c_near,c_far);
	}
	else
	{
		glFrustum(c_left,c_right,c_bottom,c_top,c_near,c_far);
	}


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void DTclearScreen(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void DTdrawObject(meshed_object * mo){

	glLoadMatrixf(baseChange_mat);
	glMultMatrixf(mo->obj.transform);


	MKZ_mesh * mesh = mo->mesh;
	int f;
	int v;
	int v_index;

	for (f = 0; f < mesh->num_faces; f++) {

		glBegin(GL_POLYGON);
		for (v = 0; v < mesh->face_table[f].num_vertices; v++) {
			v_index = mesh->face_table[f].vertex_table[v];
			glVertex3d(mesh->vertex_table[v_index].coord.x,
					mesh->vertex_table[v_index].coord.y,
					mesh->vertex_table[v_index].coord.z);

		}
		glEnd();
	}
}

void DTendDrawing(){
	glFlush();
}
