#include "Is_Prime.h"

bool isPrime (const PRIME_TYPE &val) {

	//Numbers 14 or smaller
	if (val == 2) {
		return true;
	} else if (val == 9) {
		return false;
	} else if (val <= 14) {
		return val % 2 == 1;
	}

	//The most common factors (2, 3, 5)
	if (val % 2 == 0 || LAST_DIGIT (val) == 5 || val % 3 == 0) { return false; }

	//All other prime factors
	for (PRIME_TYPE i = 7; i <= val / 3; i += 2) {
		if (!isMultipleOf3or5 (i) && val % i == 0) { return false; }
	}

	return true;
}