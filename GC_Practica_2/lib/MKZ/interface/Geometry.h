typedef struct {
    float x, y, z;
} vector3;

typedef vector3 point3;

typedef struct {
    float r, g, b;
} color3;

typedef struct {
    point3 coord;                       /* coordinates,x, y, z */
    int num_faces;                    /* number of faces that share this vertex */
} vertex;

typedef struct {
    int num_vertices;                 /* number of vertices in the face */
    int *vertex_table;                /* table with the index of each vertex */
} face;

typedef struct {

	int num_vertices;                 /* number of vertices in the object*/
	vertex *vertex_table;               /* table of vertices */
	int num_faces;                    /* number of faces in the object */
	face *face_table;                   /* table of faces */
	point3 min;                         /* coordinates' lower bounds */
	point3 max;
}mesh;

typedef struct{

}material;
