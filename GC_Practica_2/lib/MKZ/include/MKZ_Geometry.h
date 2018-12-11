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

	float ** r;
	float ** g;
	float ** b;

}MKZ_RGBmap;

typedef struct{

	MKZ_RGBmap * ambientMap;
	MKZ_RGBmap * difuseMap;
	MKZ_RGBmap * specularMap;

}MKZ_material;

/** Geometry **/
MKZ_point3 * MKZ_create_point3();
MKZ_vector3 * MKZ_create_point3();
MKZ_face * MKZ_create_face(int vertex_count);
MKZ_line * MKZ_create_line();


void MKZ_face_add_vertex(MKZ_face * face, int p);

void MKZ_free_point3(MKZ_point3 * p3);
void MKZ_free_vector3(MKZ_vector3 * v3);
void MKZ_free_face(MKZ_face * face);
void MKZ_free_line(MKZ_line * line);



/** MESH **/
MKZ_mesh * MKZ_create_mesh(MKZ_point3 * vertices, MKZ_face * faces);
MKZ_mesh * MKZ_load_mesh(char * filename);
void MKZ_free_mesh(MKZ_mesh * mesh);
