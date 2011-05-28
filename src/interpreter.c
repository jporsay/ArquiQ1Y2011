#include "../include/interpreter.h"

void setRoutineSpace(){
//	routines = malloc(sizeof(routineList));
	
	routines->head = NULL;
}

int addNewRoutine(char* routineName, void (*routineFnc)(char *)) {
	/*void* (*routineFnc)(char ** params)*/
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
	

/*	if (routineName == NULL || routineFnc == NULL) {
		return 1;
	}
		
	routine_p r = malloc(sizeof(routine));
	routineNode_p rn = malloc(sizeof(routineNode));
	
	r->name = routineName;
	r->fnc = routineFnc;
	
	rn->myRoutine = r;
	rn->next = NULL;
	
	if (routines->head == NULL) {
		routines->head = rn;
		return 0;
	}
	routineNode_p tempRN = routines->head;
	
	while(tempRN->next != NULL)
		tempRN = tempRN->next;
	
	tempRN->next = rn;
	*/
	return 0;	
}
	
int parse(char * feedLine){
	/*
	while(*feedLine == ' ')
		feedLine++;
		
	if(*feedLine == '\0')
		return NO_ROUTINE;
		
	char * firstWordStart = feedLine;
	
	unsigned int firstWordEnd = 0;
	
	while(firstWordEnd != ' ')
		firstWordEnd++;
	
	//int routineID = 0; //viejo código sin malloc
	
	routineNode_p tempRN = routines->head;
	
	while(tempRN->next != NULL && strncmp(firstWordStart, 
		tempRN->myRoutine->name, firstWordEnd))
		tempRN = tempRN->next;
		
	if(strncmp(firstWordStart, tempRN->myRoutine->name, firstWordEnd))
		return ROUTINE_NOT_FOUND;
	
	while(*feedLine == ' ')
		feedLine++;
	
	tempRN->myRoutine->fnc(feedLine);
	*/
	return 0;
}

