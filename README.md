# PrimeFinder
Finds Primes through a multithreaded brute force method.

## Options
- WRITE_TO_FILE: Whether to write a file of prime numbers formatted the same as the console output.
- WRITE_HEADER_TO_FILE: Whether to write the console header to the file. (Recommended to be 0 if ERROR_CHECK is 1)
- INCREMENT_TWO: Whether to increment by two in the threading (Recommended 1 if lower bound is odd, 0 if lower bound is even)
- ERROR_CHECK: Whether to check the result against a text of true primes
- STEPSIZE: How many threads to run at one time
