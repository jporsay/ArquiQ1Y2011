#include "../include/math.h"

long seed = 213131;

int pow(int base, int power) {
	if (0 == power) {
		return 1;
	}
	return base * pow(base, power - 1);
}

int random() {
	seed = (71 * seed + 13) % 101;
	return seed;
}

void setSeed(long s) {
	seed = s;
}

