#include "../include/command.h"

int echo_cmd(int argc, char *argv[]) {
	int i;
	if (argc > 0) {
		for( i = 0; i < argc; i++) {
			printf("%s ", argv[i]);
		}
	}
}

int restart_cmd(int argc, char *argv[]) {
	_reset();
}

int clear_cmd(int argc, char *argv[]) {
	cls();
}

int help_cmd(int argc, char *argv[]) {
	int cmdIndex;
	if (argc == 1) {
		cmdIndex = getCmdIndex(argv[0]);
		if (cmdIndex != -1) {
			printf("\n%s\n", getCmdsTable()[cmdIndex].help);
		} else {
			printf("\nCommand not found\n");
		}
	} else if (argc == 0) {
		int i;
		printf("\nAvailable commands:\n\n");
		for( i=0; getCmdsTable()[i].func != NULL; i++) {
			printf("\t%s\n", getCmdsTable()[i].name);
		}
		printf("\nType in help \"cmdName\" to see the help menu for that \
command.\n");
	}
}

int calculateCpuSpeed(int (*method)()) {
	int cpuspeed;
	int iterations = 10;
	int i = iterations;
	int total = 0;
	printf("Calculating CPU speed, please wait...\n");
	while (i-- > 0) {
		cpuspeed = (*method)();
		total += cpuspeed / iterations;
	}
	return total;
}

int getCPUspeed_cmd(int argc, char *argv[]) {
	int speed;
	if (_cpuIdTest() != 1) {
		printf("error: cpuid instruction is not supported.\n");
		return FALSE;
	}
	printf("Detected cpuid instruction...\n");
	if (_rdtscTest() > 0) {
		printf("Using rdtsc to perform measurement...\n");
		speed = calculateCpuSpeed(_tscGetCpuSpeed);
	} else if (_rdmsrTest() > 0) {
		printf("Using rdmsr to perform measurement...\n");
		speed = calculateCpuSpeed(_msrGetCpuSpeed);
	} else {
		printf("error: rdtsc or rdmsr should be available to \
			perform this command\n");
			return FALSE;
	}
	
	printf("Detected CPU speed: %iMHz\n", speed);
}


int random_cmd(int argc, char *argv[]) {
	printf("%d", random());
}

int test_cmd(int argc, char *argv[]) {
	printf("Hola hola %f", (double)3.1234);
}

int asd_cmd(int argc, char *argv[]) {
/*    int n;
    while (scanf("%d", & n))
        printf("%d\n", n);	
	
	return;*/
	char ans[10];
	float n;
	printf("IGNORING\n");
	scanf("%f", &n);
	printf("\nIngrese un texto: ");
	scanf("%f", &n);
	printf("\nTexto leido: %f\n", n);
}

int setAppearance_cmd(int argc, char *argv[]) {
	if (argc != 2) {
		printf("You need to call this function with 2 colors\n");
	} else {
		char* foreGround = argv[0];
		char* backGround = argv[1];
		
		int fg = parseHexa(foreGround[0]);
		int bg = parseHexa(backGround[0]);
		printf("%d  %d\n", fg, bg);
		if (strlen(foreGround) != 1 || strlen(backGround) != 1 || fg == -1
			|| bg == -1) {
			printf("Both arguments must be a hexadecimal number between 0 \
				and F\n");
			return;
		}
		setVideoColor(bg, fg);
	}
}

