#include "Is_Prime.h"

bool isPrime ( const PRIME_TYPE &val ) {

	//Single digit
	if ( val <= 10 ) {

		if ( val == 2 ) {
			return true;
		} else if ( val % 2 == 0 ) {
			return false;
		} else if ( val == 9 ) {
			return false;
		} else {
			return true;
		}
	}

	const auto last = LAST_DIGIT ( val );

	if ( last % 2 == 0 || last == 5 ) { return false; }

	for (PRIME_TYPE i = 3; i <= val / 3; i += 2 ) {
		if ( isMultipleOf3or5 ( i ) ) { } else if ( val % i == 0 ) { return false; }
	}

	return true;
}