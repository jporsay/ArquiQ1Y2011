#include "../include/math.h"

int pow(int base, int power) {
	if (0 == power) {
		return 1;
	}
	return base * pow(base, power - 1);
}
