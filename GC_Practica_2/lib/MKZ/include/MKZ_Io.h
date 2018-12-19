#ifndef LIB_MKZ_INCLUDE_MKZ_IO_H_
#define LIB_MKZ_INCLUDE_MKZ_IO_H_

#include "MKZ_Objects.h"
int MKZ_IO_read_objFile(char * file_name, MKZ_point3 ** p3, MKZ_face ** v3 , int * vertex_count , int * face_count);


#endif /* LIB_MKZ_INCLUDE_MKZ_IO_H_ */
