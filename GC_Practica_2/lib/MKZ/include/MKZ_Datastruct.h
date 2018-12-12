#ifndef __MKZ_DATASTRUCT_IMPORTED__
#define __MKZ_DATASTRUCT_IMPORTED__

typedef struct MKZ_linkedList MKZ_linkedList;
struct MKZ_linkedList{
	void * content;
	MKZ_linkedList * ll;
};


MKZ_linkedList * MKZ_DATASTRUCT_create_linkedList();

#endif
