#include <stdio.h>
#include <stdlib.h>

#define MEM_LENGHT 8388608
#define FALSE 0
#define TRUE !FALSE

typedef struct memoryHeader_t{
	struct memoryHeader_t * next;
	int size;
	int reserved;
} memoryHeader_t;

typedef memoryHeader_t * memoryNode;

void* FMN;

void setMemory(void * mem_start){

	memoryNode firstMemoryNode = mem_start;
	
	firstMemoryNode->next = firstMemoryNode;
	firstMemoryNode->size = MEM_LENGHT;
	firstMemoryNode->reserved = FALSE;
	
}

void * myMalloc(size_t neededMem){
	
	memoryNode node, firstNode;
	
	int chunkFound = FALSE;
	
	node = firstNode = FMN;
	
	do{
		if(node->reserved == FALSE && node->size >= neededMem){
			chunkFound = TRUE;
			node->reserved = TRUE;
			printf("reservo memoria\n");
			if(node->size > neededMem){
				memoryNode newNode = (memoryNode)(node + sizeof(memoryHeader_t)
					 + neededMem);
				
				newNode->next = node->next;
				newNode->size = node->size - neededMem - sizeof(memoryHeader_t);
				newNode->reserved = FALSE;
				
				node->next = newNode;
				node->size = neededMem;
				printf("cree nuevo zodape\n");
			}
		
		}else{
			node = node->next;
			printf("este no me sirve\n");
		}
	}while(!chunkFound && node != firstNode);
	
	if(chunkFound)
		return (void *)(node + 1);
	
	return NULL;
}

void myFree(void * pointer){
	
	memoryNode node = (memoryNode)(pointer - sizeof(memoryHeader_t));
	
	node->reserved = FALSE;
	printf("liberé el bloque\n");
	memoryNode startingNode = node;
	
	while(node->next != startingNode && node->next->reserved == FALSE){
		node->size = node->size + node->next->size + sizeof(memoryHeader_t);
		node->next = node->next->next;
	}
	
}

int main(void){
	
	setMemory(FMN = malloc(MEM_LENGHT + sizeof(memoryHeader_t)));
	
	int * firstVector = myMalloc(5*sizeof(int));
	
	int i = 0;
	for(i = 0; i<5; i++){
		firstVector[i] = i;
	}
	
	for(i = 0; i<5; i++){
		printf("%d\n", firstVector[i]);
	}
	
	myFree(firstVector);
	
	void * allMem = myMalloc(MEM_LENGHT);
	printf("reservo toda la memoria\n");
	if(myMalloc(1) == NULL)
		printf("malloc tira null\n");
		
	myFree(allMem);
	
	return 0;
}
