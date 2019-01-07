#include "MKZ_Io.h"
#include "MKZ_Geometry.h"
#include <stdlib.h>

void MKZ_GEOMETRY_reset_to_origin(MKZ_point3 * p3){

	p3->x = 0;
	p3->y = 0;
	p3->z = 0;

}

MKZ_point3 * MKZ_GEOMETRY_create_point3(){
	MKZ_point3 * p3  = (MKZ_point3*) malloc(sizeof(MKZ_point3));
	MKZ_GEOMETRY_reset_to_origin(p3);
	return p3;
}

MKZ_vector3 * MKZ_GEOMETRY_create_vector3(){
	return MKZ_GEOMETRY_create_point3();
}

MKZ_face * MKZ_GEOMETRY_create_face(int vertex_count){
	MKZ_face * face = (MKZ_face*) malloc(sizeof(MKZ_face));
	face->num_vertices = vertex_count;
	face->vertex_table = (int*) malloc(sizeof(int)*vertex_count);

	int i;
	for (i = 0 ; i < vertex_count ; i++){
		face->vertex_table[i] = -1;
	}

	return face;
}

MKZ_line * MKZ_GEOMETRY_create_line(){

	MKZ_line * l = (MKZ_line*) malloc(sizeof(MKZ_line));
	MKZ_GEOMETRY_reset_to_origin(&l->p0);
	MKZ_GEOMETRY_reset_to_origin(&l->p1);
	return l;
}

void MKZ_GEOMETRY_face_add_vertex(MKZ_face * face, int p){

	int i;

	for (i = 0 ; i < face->num_vertices ; i++){
		if (face->vertex_table[i] == -1){
			face->vertex_table[i] = p;
			break;
		}
	}
}

void MKZ_GEOMETRY_free_point3(MKZ_point3 * p3){
	free(p3);
}

void MKZ_GEOMETRY_free_vector3(MKZ_vector3 * v3){
	free(v3);
}
void MKZ_GEOMETRY_free_face(MKZ_face * face){
	free(face->vertex_table);
	free(face);
}
void MKZ_GEOMETRY_free_line(MKZ_line * line){
	free(line);
}

/** MESH **/
MKZ_mesh * MKZ_GEOMETRY_create_mesh(MKZ_point3 * vertices, MKZ_face * faces , int vertex_count , int face_count){

	MKZ_mesh * mesh = (MKZ_mesh*) malloc(sizeof(MKZ_mesh));

	mesh->num_faces = face_count;
	mesh->num_vertices = vertex_count;

	mesh->face_table = (MKZ_face *) malloc(sizeof(MKZ_face)*face_count);
	mesh->vertex_table = (MKZ_vertex *) malloc(sizeof(MKZ_vertex)*vertex_count);

	int i;
	for (i = 0; i < vertex_count; i++){
	        mesh->vertex_table[i].num_faces = 0;
	        mesh->vertex_table[i].coord.x= vertices[i].x;
	        mesh->vertex_table[i].coord.y= vertices[i].y;
	        mesh->vertex_table[i].coord.z= vertices[i].z;
	}

	for (i = 0; i < face_count; i++){

				int j;
				//mesh->face_table[i].vertex_table = faces[i].vertex_table;
				mesh->face_table[i].num_vertices = faces[i].num_vertices;
				mesh->face_table[i].vertex_table = (int*) malloc(sizeof(int)*faces[i].num_vertices);
				for (j = 0 ; j < faces[i].num_vertices ; j++){
					int vertex = faces[i].vertex_table[j];
					mesh->face_table[i].vertex_table[j] = faces[i].vertex_table[j];
					mesh->vertex_table[vertex].num_faces += 1;
				}



	}

	mesh->max.x = mesh->vertex_table[0].coord.x;
	mesh->max.y = mesh->vertex_table[0].coord.y;
	mesh->max.z = mesh->vertex_table[0].coord.z;
	mesh->min.x = mesh->vertex_table[0].coord.x;
	mesh->min.y = mesh->vertex_table[0].coord.y;
	mesh->min.z = mesh->vertex_table[0].coord.z;

	for (i = 1; i < mesh->num_vertices; i++)
	{
		if (mesh->vertex_table[i].coord.x < mesh->min.x)
			mesh->min.x = mesh->vertex_table[i].coord.x;

		if (mesh->vertex_table[i].coord.y < mesh->min.y)
			mesh->min.y = mesh->vertex_table[i].coord.y;

		if (mesh->vertex_table[i].coord.z < mesh->min.z)
			mesh->min.z = mesh->vertex_table[i].coord.z;

		if (mesh->vertex_table[i].coord.x > mesh->max.x)
			mesh->max.x = mesh->vertex_table[i].coord.x;

		if (mesh->vertex_table[i].coord.y > mesh->max.y)
			mesh->max.y = mesh->vertex_table[i].coord.y;

		if (mesh->vertex_table[i].coord.z > mesh->max.z)
			mesh->max.z = mesh->vertex_table[i].coord.z;

	}

	/*
	fprintf(stdout, "n_vertex: %d\n",mesh->num_vertices);

	for (i = 0 ; i < mesh->num_vertices ; i++){
		fprintf(stdout, "vertex: %d\n",i);
		fprintf(stdout, "face count:%d\n",mesh->vertex_table[i].num_faces);
		fprintf(stdout, "x:%lf\n",mesh->vertex_table[i].coord.x);
		fprintf(stdout, "y:%lf\n",mesh->vertex_table[i].coord.y);
		fprintf(stdout, "z:%lf\n",mesh->vertex_table[i].coord.z);
	}


	fprintf(stdout, "n_faces: %d\n",mesh->num_faces);
	/*
	for (i = 0 ; i < mesh->num_faces ; i++){
		fprintf(stdout, "face: %d\n",i);
		fprintf(stdout, "vertex count:%d\n",mesh->face_table[i].num_vertices);

		int j = 0;

		for (j = 0 ; j < mesh->face_table[i].num_vertices ; j++){
			fprintf(stdout, "vertex:%d\n",j);
			fprintf(stdout, "vertex_index:%d\n",mesh->face_table[i].vertex_table[j]);
		}


	}
	*/

	return mesh;


}


MKZ_mesh * MKZ_GEOMETRY_load_mesh(char * file_name){

	int vertex_count;
	int face_count;

	MKZ_point3 * p3 = 0;
	MKZ_face * fc = 0;


	int error = MKZ_IO_read_objFile(file_name, &p3, &fc, &vertex_count, &face_count);
	MKZ_mesh * mesh = 0;
	if (error == 0)
		mesh = MKZ_GEOMETRY_create_mesh(p3, fc, vertex_count, face_count);

	if (p3 != 0)
		free(p3);
	if (fc != 0)
		free(fc);

	return mesh;
}

void MKZ_GEOMETRY_free_mesh(MKZ_mesh * mesh){

	free(mesh->vertex_table);

	int i;
	for (i = 0 ; i < mesh->num_faces ; i++){
		free(mesh->face_table[i].vertex_table);
	}

	free(mesh->face_table);
	free(mesh);
}

