//Output things
#include <iostream> //cout
#include <iomanip>  //formatting
#include <fstream>  //file_output
#include <string>	//to_string
//Multi-threading
#include <thread>
#include <future>
//Timing
#include <time.h>
//END INCLUDES

//Code pieces
#define CLOCKS_PER_MS (CLOCKS_PER_SEC/1000)
#define COLUMN_SET setw(7)
#define LAST_DIGIT(x) x % 10

//Boolean Options
#define WRITE_TO_FILE 0
#define WRITE_HEADER_TO_FILE 0
#define USE_EVENS 0

// Numerical Option
#define STEPSIZE 100

using namespace std;

typedef unsigned char smallNum;
typedef unsigned long int bigNum;

const string myPrimeFile = "primes.txt";
const string truePrimeFile = "true_primes.txt";

const auto printSize = "Using " + to_string (sizeof (bigNum) * 8) + "-bit numbers";

const bigNum bounds[ ] = { 2,  99'000 };
const bigNum amountOfNumbers = bounds[1] - bounds[0];

const auto numToAnalyze = "Will analyze " + to_string (amountOfNumbers) + " numbers in " + to_string (amountOfNumbers / static_cast<double>( STEPSIZE )) + " groups.";

const string header = printSize + " | " + numToAnalyze;

void printNum (ofstream &output, const bigNum &i) {

	static int column = 0;

	cout << COLUMN_SET << i;
	output << COLUMN_SET << i;

	column++;

	if (column == 10) {
		cout << endl;
		output << endl;
		column = 0;
	}
}

inline bool isMultipleOf3or5 (const bigNum &i) { return ( i % 5 == 0 && i != 5 ) || ( i % 3 == 0 && i != 3 ); }

bool isPrime (const bigNum &val) {

	//Single digit
	if (val < 10) {

		if (val == 2) {
			return true;
		} else if (val % 2 == 0) {
			return false;
		} else if (val == 9) {
			return false;
		} else {
			return true;
		}
	}

	const auto last = LAST_DIGIT(val);

	if (last % 2 == 0 || last == 5) { return false; }

	for (bigNum i = 3; i <= val / 3; i += 2) {
		if (isMultipleOf3or5 (i)) { } else if (val % i == 0) { return false; }
	}

	return true;
}

ofstream output;

void watch (const bigNum &start) {

	future<bool> watching[STEPSIZE];

	for (smallNum i = 0; i < STEPSIZE; i += 1 + USE_EVENS) {
		watching[i] = async (isPrime, start + i);
	}

	for (smallNum i = 0; i < STEPSIZE; i += 1 + USE_EVENS) {
		if (watching[i].get ( )) {
			printNum (output, start + i);
		}

	}
}

int main ( ) {

	output.open (myPrimeFile.c_str ( ));

	cout << header;

	if (WRITE_HEADER_TO_FILE) {
		output << header << endl;
	} else {
		cout << " | Did not print the header to the file!" << endl;
	}

	const auto start = clock ( );

	for (bigNum i = bounds[0]; i <= bounds[1]; i += STEPSIZE) {
		auto task = new thread (watch, i);
		task->join ( );
	}

	cout << endl << "Seconds elapsed: " << ( static_cast<double>( clock ( ) - start ) / CLOCKS_PER_SEC ) << endl;

	output.close ( );

	ifstream truePrimeStream;
	ifstream myPrimeStream;

	truePrimeStream.open (truePrimeFile.c_str ( ));
	myPrimeStream.open (myPrimeFile.c_str ( ));


	if (truePrimeStream && myPrimeStream && WRITE_TO_FILE) {

		cout << endl << "Error Search" << endl;
		cout << COLUMN_SET << right << "Mine" << COLUMN_SET << right << "True" << endl;

		unsigned int truePrime, myPrime;

		while (truePrimeStream >> truePrime && myPrimeStream >> myPrime) {

			if (myPrime != truePrime) {
				cout << COLUMN_SET << right << myPrime << COLUMN_SET << right << truePrime << endl;
			}
		}
	}

	cin.get ( );
}