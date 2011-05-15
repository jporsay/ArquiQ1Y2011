#include "../includes/defs.h"
#include "../includes/multiboot.h"

#ifndef boolean
#define boolean unsigned char
#endif


typedef struct{
	void* next;
	size_t size;
	void* memPtr;
	boolean reserverd;
} mallocStruct;

static mallocStruct* first_mallocStruct;

int setMemory(multiboot_info_t * mbd){
	if((mdb->flags >> 6) % 2 == 0)
		return 1;

	memory_map_t * mmap = mdb->mmap_addr;

	for(int i=0; i< mdb->mmap_length; i++){
		
	}
}
void* malloc(size_t size){
	
}



