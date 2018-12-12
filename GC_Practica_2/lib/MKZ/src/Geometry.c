#include "MKZ_Geometry.h"

#include <stdlib.h>
#define MAXLINE 200

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
	        mesh->vertex_table[i].coord= vertices;
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

	MKZ_point3 *vertex_table;
	MKZ_face *face_table;

	int num_vertices = -1, num_faces = -1, count_vertices = 0, count_faces = 0;
	FILE *obj_file;
	char line[MAXLINE], line_1[MAXLINE], aux[45];
	int k;
	int i, j;
	int values[MAXLINE];


	/*
	 * The function reads twice the file. In the first read the number of
	 * vertices and faces is obtained. Then, memory is allocated for each
	 * of them and in the second read the actual information is read and
	 * loaded. Finally, the object structure is created
	 */
	if ((obj_file = fopen(file_name, "r")) == NULL) return (1);
	while (fscanf(obj_file, "\n%[^\n]", line) > 0) {
		i = 0;
		while (line[i] == ' ') i++;
		if ((line[0] == '#') && ((int) strlen(line) > 5)) {
			i += 2;
			j = 0;
			while (line[i] != ' ') line_1[j++] = line[i++];
			i++;
			line_1[j] = '\0';
			j = 0;
			while ((line[i] != ' ') && (line[i] != '\0'))
				aux[j++] = line[i++];
			aux[j] = 0;
			if (strcmp(aux, "vertices") == 0) {
				num_vertices = atoi(line_1);
			}
			if (strncmp(aux, "elements", 7) == 0) {
				num_faces = atoi(line_1);
			}
		} else {
			if (strlen(line) > 6) {
				if (line[i] == 'f' && line[i + 1] == ' ')
					count_faces++;
				else if (line[i] == 'v' && line[i + 1] == ' ')
					count_vertices++;
			}
		}
	}
	fclose(obj_file);
//printf("1 pasada: num vert = %d (%d), num faces = %d(%d) \n",num_vertices,count_vertices,num_faces,count_faces);
	if ((num_vertices != -1 && num_vertices != count_vertices) || (num_faces != -1 && num_faces != count_faces)) {
		printf("WARNING: full file format: (%s)\n", file_name);
		//return (2);
	}
	if (num_vertices == 0 || count_vertices == 0) {
		printf("No vertex found: (%s)\n", file_name);
		return (3);
	}
	if (num_faces == 0 || count_faces == 0) {
		printf("No faces found: (%s)\n", file_name);
		return (3);
	}

	num_vertices = count_vertices;
	num_faces = count_faces;

	vertex_table = (MKZ_point3 *) malloc(num_vertices * sizeof (MKZ_point3));
	face_table = (MKZ_face *) malloc(num_faces * sizeof (MKZ_face));

	obj_file = fopen(file_name, "r");
	k = 0;
	j = 0;


	while (fscanf(obj_file, "\n%[^\n]", line) > 0) {
		switch (line[0]) {
			case 'v':
			if (line[1] == ' ')  // vn not interested
		{
				sscanf(line + 2, "%lf%lf%lf", &(vertex_table[k].x),
						&(vertex_table[k].y), &(vertex_table[k].z));
				k++;
		}
			   break;

			case 'f':
		if (line[1] == ' ') // fn not interested
				{
				for (i = 2; i <= (int) strlen(line); i++)
					line_1[i - 2] = line[i];
		line_1[i-2] = '\0';
				int face_num_vertices = sreadint2(line_1, values);
				face_table[j] = MKZ_GEOMETRY_create_face(face_num_vertices);

//printf("f %d vertices\n",face_table[j].num_vertices);
				for (i = 0; i < face_table[j].num_vertices; i++) {
					MKZ_GEOMETRY_face_add_vertex(face_table,  values[i] - 1);
//printf(" %d ",values[i] - 1);

					}
//printf("\n");
				j++;
				}
			  break;
		}
	}

	fclose(obj_file);

	return MKZ_GEOMETRY_create_mesh(vertex_table, face_table, count_vertices, count_faces);

}

void MKZ_GEOMETRY_free_mesh(MKZ_mesh * mesh){

	free(mesh->vertex_table);

	int i;
	for (i = 0 ; i < mesh->num_faces ; i++){
		MKZ_GEOMETRY_free_face(mesh->face_table[i]);
	}

	free(mesh);
}
