#ifndef _IS_PRIME
#define _IS_PRIME

#define LAST_DIGIT(x) x % 10

typedef unsigned long int bigNum;

inline bool isMultipleOf3or5 ( const bigNum &i ) { return (i % 5 == 0 && i != 5) || (i % 3 == 0 && i != 3); }

bool isPrime ( const bigNum &val );

#endif // !_IS_PRIME

