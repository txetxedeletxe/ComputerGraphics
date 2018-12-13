#include "MKZ_Geometry.h"
#include "MKZ_io.h"

#include <stdlib.h>
MKZ_point3 * MKZ_GEOMETRY_create_point3(){
	return (MKZ_point3*) malloc(sizeof(MKZ_point3));
}

MKZ_vector3 * MKZ_GEOMETRY_create_vector3(){
	return (MKZ_vector3*) malloc(sizeof(MKZ_vector3));
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

	return (MKZ_line*) malloc(sizeof(MKZ_line));
}
MKZ_color3 * MKZ_GEOMETRY_create_color3(){
	return (MKZ_color3*) malloc(sizeof(MKZ_color3));
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
void MKZ_GEOMETRY_free_color3(MKZ_color3 * col){
	free(col);
}


/** MESH **/
MKZ_mesh * MKZ_GEOMETRY_create_mesh(MKZ_point3 * vertices, MKZ_face * faces , int vertex_count , int face_count){

	MKZ_mesh * mesh = (MKZ_mesh*) malloc(sizeof(MKZ_mesh));

	mesh->num_faces = face_count;
	mesh->num_vertices = vertex_count;

	mesh->face_table = (MKZ_face *) malloc(sizeof(MKZ_face)*face_count);
	mesh->vertex_table = (MKZ_vertex *) malloc(sizeof(MKZ_vertex)*face_count);

	int i;
	for (i = 0; i < vertex_count; i++){
	        mesh->vertex_table[i].num_faces = 0;
	        mesh->vertex_table[i].coord.x= vertices->x;
	        mesh->vertex_table[i].coord.y= vertices->y;
	        mesh->vertex_table[i].coord.z= vertices->z;
	}

	for (i = 0; i < face_count; i++){

				int j;
				for (j = 0 ; j < faces[i].num_vertices ; j++){
					int vertex = faces[i].vertex_table[j];

					mesh->vertex_table[vertex].num_faces += 1;

				}

		        mesh->face_table[i] = faces[i];

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

	return mesh;


}


MKZ_mesh * MKZ_GEOMETRY_load_mesh(char * file_name){

	int vertex_count;
	int face_count;

	MKZ_point3 * p3;
	MKZ_face * fc;

	MKZ_IO_read_objFile(file_name, p3, fc, &vertex_count, &face_count);
	return MKZ_GEOMETRY_create_mesh(p3, fc, vertex_count, face_count);


}

void MKZ_GEOMETRY_free_mesh(MKZ_mesh * mesh){

	free(mesh->vertex_table);

	int i;
	for (i = 0 ; i < mesh->num_faces ; i++){
		MKZ_GEOMETRY_free_face(&mesh->face_table[i]);
	}

	free(mesh);
}
