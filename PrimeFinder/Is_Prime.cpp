#include "Is_Prime.h"

bool isPrime(const PRIME_TYPE &val) {

	//Single digit
	if(val <= 10) {

		if(val == 2) {
			return true;
		} else if(val % 2 == 0) {
			return false;
		} else if(val == 9) {
			return false;
		} else {
			return true;
		}
	}

	if( LAST_DIGIT (val) % 2 == 0 || LAST_DIGIT (val) == 5) { return false; }

	for(PRIME_TYPE i = 3; i <= val / 3; i += 2) {
		if(!isMultipleOf3or5(i) && val % i == 0) { return false; }
	}

	return true;
}