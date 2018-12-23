#ifndef __MKZ_GEOMETRY_IMPORTED__
#define __MKZ_GEOMETRY_IMPORTED__

typedef struct {
    float x, y, z;
} MKZ_vector3;

typedef MKZ_vector3 MKZ_point3;

typedef struct {
    float r, g, b;
} MKZ_color3;

typedef struct {
    MKZ_point3 coord;                       /* coordinates,x, y, z */
    int num_faces;                    /* number of faces that share this MKZ_vertex */
} MKZ_vertex;

typedef struct {
    int num_vertices;                 /* number of vertices in the MKZ_face */
    int *vertex_table;                /* table with the index of each MKZ_vertex */
} MKZ_face;


typedef struct{

	MKZ_point3 p0;
	MKZ_point3 p1;

}MKZ_line;


typedef struct {

	int num_vertices;                 /* number of vertices in the object*/
	MKZ_vertex *vertex_table;               /* table of vertices */
	int num_faces;                    /* number of faces in the object */
	MKZ_face *face_table;                   /* table of faces */
	MKZ_point3 min;                         /* coordinates' lower bounds */
	MKZ_point3 max;

}MKZ_mesh;

typedef struct{

	float * floatMap; //array size = n*n

	int n;

}MKZ_map;

typedef struct{

	MKZ_map * ambientMapR;
	MKZ_map * ambientMapG;
	MKZ_map * ambientMapB;

	MKZ_map * difuseMapR;
	MKZ_map * difuseMapG;
	MKZ_map * difuseMapB;

	MKZ_map * specularMapR;
	MKZ_map * specularMapG;
	MKZ_map * specularMapB;

	float shininess;

}MKZ_material;

/** Geometry **/
MKZ_point3 * MKZ_GEOMETRY_create_point3();
MKZ_vector3 * MKZ_GEOMETRY_create_vector3();
MKZ_face * MKZ_GEOMETRY_create_face(int vertex_count);
MKZ_line * MKZ_GEOMETRY_create_line();
MKZ_color3 * MKZ_GEOMETRY_create_color3();

void MKZ_GEOMETRY_reset_to_origin(MKZ_point3 * p3);
void MKZ_GEOMETRY_reset_to_black(MKZ_color3 * c3);
void MKZ_GEOMETRY_face_add_vertex(MKZ_face * face, int p);

void MKZ_GEOMETRY_free_point3(MKZ_point3 * p3);
void MKZ_GEOMETRY_free_vector3(MKZ_vector3 * v3);
void MKZ_GEOMETRY_free_face(MKZ_face * face);
void MKZ_GEOMETRY_free_line(MKZ_line * line);
void MKZ_GEOMETRY_free_color3(MKZ_color3 * col);




/** MESH **/
MKZ_mesh * MKZ_GEOMETRY_create_mesh(MKZ_point3 * vertices, MKZ_face * faces , int vertex_count , int face_count);
MKZ_mesh * MKZ_GEOMETRY_load_mesh(char * filename);
void MKZ_GEOMETRY_free_mesh(MKZ_mesh * mesh);

/** MATERIAL **/
MKZ_material * MKZ_GEOMETRY_create_material();
MKZ_map * MKZ_GEOMETRY_create_map(int size);

void MKZ_GEOMETRY_free_material(MKZ_material * mat);
void MKZ_GEOMETRY_free_map(MKZ_map * map);

#endif
