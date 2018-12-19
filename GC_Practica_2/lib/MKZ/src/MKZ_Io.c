#include "MKZ_Geometry.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 200



static int sreadint2(char * lerroa, int * zenbakiak) {
    char *s = lerroa;
    int i, zbk, kont = 0;

    while (sscanf(s, " %d%n", &zbk, &i) > 0) {
        s += i;
	while ((*s != ' ')&&(*s !='\0')) s++;  // jump vector normal information
        zenbakiak[kont++] = zbk;
    }
//printf("%d numbers in the line\n",kont);
    return (kont);
}


int MKZ_IO_read_objFile(char * file_name, MKZ_point3 ** vertex_table, MKZ_face ** face_table , int * vertex_count , int * face_count){



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
		if ((obj_file = fopen(file_name, "r")) == NULL)
			return -1;
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
			//printf("WARNING: full file format: (%s)\n", file_name);
			return -2;
		}
		if (num_vertices == 0 || count_vertices == 0) {
			//printf("No vertex found: (%s)\n", file_name);
			return -3;
		}
		if (num_faces == 0 || count_faces == 0) {
			//printf("No faces found: (%s)\n", file_name);
			return -4;
		}

		num_vertices = count_vertices;
		num_faces = count_faces;

		*(vertex_table) = (MKZ_point3 *) malloc(num_vertices * sizeof (MKZ_point3));
		*(face_table) = (MKZ_face *) malloc(num_faces * sizeof (MKZ_face));

		MKZ_point3 * vt = *(vertex_table);
		MKZ_face * ft = *(face_table);
		obj_file = fopen(file_name, "r");
		k = 0;
		j = 0;


		while (fscanf(obj_file, "\n%[^\n]", line) > 0) {
			switch (line[0]) {
				case 'v':
				if (line[1] == ' ')  // vn not interested
			{
					sscanf(line + 2, "%f%f%f", &(vt[k].x),
							&(vt[k].y), &(vt[k].z));
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
					ft[j].num_vertices = face_num_vertices;
					ft[j].vertex_table = (int*) malloc(sizeof(int)*face_num_vertices);

	//printf("f %d vertices\n",face_table[j].num_vertices);
					for (i = 0; i < ft[j].num_vertices; i++) {
						ft[j].vertex_table[i] =   values[i] - 1;
	//printf(" %d ",values[i] - 1);

						}
	//printf("\n");
					j++;
					}
				  break;
			}
		}

		fclose(obj_file);

		*(vertex_count) = num_vertices;
		*(face_count) = num_faces;

		return 0;


}
