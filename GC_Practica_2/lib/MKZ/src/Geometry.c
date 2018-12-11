#include "MKZ_Geometry.h"

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
MKZ_mesh * MKZ_GEOMETRY_create_mesh(MKZ_point3 * vertices, MKZ_face * faces){

}
MKZ_mesh * MKZ_GEOMETRY_load_mesh(char * filename);
void MKZ_GEOMETRY_free_mesh(MKZ_mesh * mesh);
