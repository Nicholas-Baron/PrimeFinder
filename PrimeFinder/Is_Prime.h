#ifndef _IS_PRIME
#define _IS_PRIME

#define LAST_DIGIT(x) x % 10
using PRIME_TYPE = unsigned long;

inline bool isMultipleOf3or5 ( const PRIME_TYPE &i ) { return (i % 5 == 0 && i != 5) || (i % 3 == 0 && i != 3); }

bool isPrime ( const PRIME_TYPE &val );

#endif // !_IS_PRIME

