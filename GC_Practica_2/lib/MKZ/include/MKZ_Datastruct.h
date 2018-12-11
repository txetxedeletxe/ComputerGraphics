struct linkedList{
	void * content;
	int id;
	struct linkedList * ll;
};

typedef struct linkedList linkedList;
linkedList * DScreateLinkedList(void* element,int id);
