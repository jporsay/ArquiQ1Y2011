#include "../include/routines.h"

void echo(char * args) {
	printf(args);
}

void restart(char * args) {
	_reset();
}

void help(char * args) {
	
	while(*args == " "){
		args++;
	}
	
	if(*args == '\0'){
		routine r = routines->head;
		while(r->next != null){
			printf("%s: %s\n", r->name, r->help);
			r = r->next;
		}
	}else{
		routine r = routines->head;
		
		while(r->next != NULL){
			if (!strcmp(args, r->name)){
				printf("%s: %s", r->name, r->help);
				return
			}				
		}
		
		if(r->next == NULL && !strcmp(r->name, args))
			printf("%s: %s\n", r->name, r->help);
		else
			printf("Command not found.\n");
	}
}



