#include <stdio.h>

#include "../src/interpreter.c"

void echo(char * params){
	printf(params);
}

void restart(char * params){
	printf("restarting\n");
}

int main(void){

	setRoutineSpace();

	if(!addNewRoutine("echo", echo))
		printf("añadió echo\n");
	else
		printf("error al añadir echo\n");
		
	if(!addNewRoutine("restart", restart))
		printf("añadió restart\n");
	else
		printf("error al añadir restart\n");
	
	if(parse("     echo con mucho espacio al principio\n"))
		printf("test1 failed\n");
	else
		printf("test1 ok!\n");
	
	if(parse("restart"))
		printf("test2 failed\n");
	else
		printf("test2 ok!\n");
		
	if(parse("asdf"))
		printf("test3 ok!\n");
	else
		printf("test3 failed\n");
	
	if(parse("              "))
		printf("test4 ok!\n");
	else
		printf("test4 failed\n");
	
	
}

