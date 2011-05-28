#include "defs.h"
#include "stdlib.h"
#include "routines.h"
#include "string.h"

#define NO_ROUTINE 1
#define ROUTINE_NOT_FOUND 2


typedef struct routine {
	char * name;
	char * help;
	void (*fnc)(char *);
	//void (*fnc)(char ** params);
} routine;

typedef routine * routine_p;

typedef struct routineNode {
	routine_p myRoutine;
	struct routineNode * next;
} routineNode;

typedef routineNode * routineNode_p;

typedef struct {
	routineNode_p head;
} routineList;
	
typedef routineList * routineList_p;

routineList_p routines;


