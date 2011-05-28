#include "defs.h"
#include "stdlib.h"
#include "routines.h"
#include "string.h"

#define NO_ROUTINE 1
#define ROUTINE_NOT_FOUND 2

typedef struct routine_t {
	char * name;
	char * help;
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

