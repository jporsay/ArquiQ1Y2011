#include "../include/defs.h"
#include "../include/stdlib.h"
#include "./string.c"

#define NO_ROUTINE 1
#define ROUTINE_NOT_FOUND 2
#define ROUTINEQTY 10

typedef struct routine_t {
	char * name;
	void (*fnc)(char *);
	//void (*fnc)(char ** params);
	} routine_t;
	

typedef routine_t * routine;

typedef struct routineNode_t {
	routine myRoutine;
	struct routineNode_t * next;
	} routineNode_t;
	
typedef routineNode_t * routineNode;


typedef struct{
	routineNode head;
	} routineList_t;
	
typedef routineList_t * routineList;

static routineList routines;

void setRoutineSpace(){
	routines = malloc(sizeof(routineList_t));
	
	routines->head = NULL;
}

int addNewRoutine(char* routineName, void (*routineFnc)(char *)
	/*void* (*routineFnc)(char ** params)*/){
/* Ya hay malloc, pero tal vez sirva todavía.	
	if(uglyRoutineCounter == ROUTINEQTY)
		return 1;
		
	routines[uglyRoutineCounter].myRoutine->name = routineName;
	routines[uglyRoutineCounter].myRoutine->fnc = routineFnc;
	routines[uglyRoutineCounter].next = NULL;
	
	routines[uglyRoutineCounter-1].next = (routineNode)1;
	
	uglyRoutineCounter++;
	
	return 0;
*/
	

	if(routineName == NULL || routineFnc == NULL)
		return 1;
		
	routine r = malloc(sizeof(routine_t));
	routineNode rn = malloc(sizeof(routineNode_t));
	
	r->name = routineName;
	r->fnc = routineFnc;
	
	rn->myRoutine = r;
	rn->next = NULL;
	
	if(routines->head == NULL){
		routines->head = rn;
		return 0;
	}
	routineNode tempRN = routines->head;
	
	while(tempRN->next != NULL)
		tempRN = tempRN->next;
	
	tempRN->next = rn;
	
	return 0;	
}
	
int parse(char * feedLine){
	
	while(*feedLine == ' ')
		feedLine++;
		
	if(*feedLine == '\0')
		return NO_ROUTINE;
		
	char * firstWordStart = feedLine;
	
	unsigned int firstWordEnd = 0;
	
	while(firstWordEnd != ' ')
		firstWordEnd++;
	
	//int routineID = 0; //viejo código sin malloc
	
	routineNode tempRN = routines->head;
	
	while(tempRN->next != NULL && strncmp(firstWordStart, 
		tempRN->myRoutine->name, firstWordEnd))
		tempRN = tempRN->next;
		
	if(strncmp(firstWordStart, tempRN->myRoutine->name, firstWordEnd))
		return ROUTINE_NOT_FOUND;
	
	while(*feedLine == ' ')
		feedLine++;
	
	tempRN->myRoutine->fnc(feedLine);
	
	return 0;
}
