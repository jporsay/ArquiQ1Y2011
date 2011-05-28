#include "../include/defs.h"
#include "../include/stdlib.h"

void putc(char c) {
	__write(STDOUT, &c, 1);
}

#define MEM_START (void *)0x1FFE0 //A partir de los 2 MB
#define MEM_LENGTH 8388608 //8 MB de RAM

typedef struct memoryHeader_t{
	struct memoryHeader_t * next;
	int size;
	int reserved;
} memoryHeader_t;

typedef memoryHeader_t * memoryNode;



void setMemory(){

	memoryNode firstMemoryNode = MEM_START;
	
	firstMemoryNode->next = firstMemoryNode;
	firstMemoryNode->size = MEM_LENGTH;
	firstMemoryNode->reserved = FALSE;
	
}

void * malloc(size_t neededMem){
	
	memoryNode node, firstNode;
	
	int chunkFound = FALSE;
	
	node = firstNode = MEM_START;
	
	do{
		if(node->reserved == FALSE && node->size >= neededMem){
			chunkFound = TRUE;
			node->reserved = TRUE;
			if(node->size > neededMem){
				memoryNode newNode = (memoryNode)(node + sizeof(memoryHeader_t)
					 + neededMem);
				
				newNode->next = node->next;
				newNode->size = node->size - neededMem - sizeof(memoryHeader_t);
				newNode->reserved = FALSE;
				
				node->next = newNode;
				node->size = neededMem;
			}
		
		}else{
			node = node->next;
		}
	}while(!chunkFound && node != firstNode);
	
	if(chunkFound)
		return (void *)(node + 1);
	
	return NULL;
}

void free(void * pointer){
	
	memoryNode node = (memoryNode)(pointer - sizeof(memoryHeader_t));
	
	node->reserved = FALSE;

	memoryNode startingNode = node;
	
	while(node->next != startingNode && node->next->reserved == FALSE){
		node->size = node->size + node->next->size + sizeof(memoryHeader_t);
		node->next = node->next->next;
	}
	
}

