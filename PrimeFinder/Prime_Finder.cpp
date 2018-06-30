#include "Is_Prime.h"
//Output things
#include <iostream> //cout
#include <iomanip>  //formatting
#include <fstream>  //file_output
#include <string>   //to_string
//Multi-threading
#include <thread>
#include <future>
//Timing
#include <ctime>
//END INCLUDES

//Code pieces
#define CLOCKS_PER_MS (CLOCKS_PER_SEC/1000)
#define COLUMN_SET setw(7)

//Boolean Options
#define WRITE_TO_FILE 0
#define WRITE_HEADER_TO_FILE 0
#define INCREMENT_TWO 1
#define ERROR_CHECK 0
#define PRINT_AT_SECOND 0
#define PRINT_ROW_NUM 0

using namespace std;

const string myPrimeFile = "primes.txt";
const string truePrimeFile = "true_primes.txt";
const string printSize = "Using " + to_string(sizeof(PRIME_TYPE) * 8) + "-bit numbers";

constexpr PRIME_TYPE bounds[] = {3,  15'001};
constexpr auto amountOfNumbers = bounds[1] - bounds[0];

constexpr unsigned short STEPSIZE = 100;
constexpr auto numGroups = amountOfNumbers / STEPSIZE;

const string numToAnalyze = "Will analyze " + to_string(amountOfNumbers) + " numbers in " + to_string(numGroups) + " groups.";
const string header = printSize + " | " + numToAnalyze;

ofstream fileOutput (myPrimeFile.c_str ( ));

void printNum(const PRIME_TYPE &i) {

	static short column = 0;
	static short row = 1;

	cout << COLUMN_SET << i;

#if WRITE_TO_FILE
	fileOutput << COLUMN_SET << i;
#endif
	column++;

	if(column == 10) {
		
#if PRINT_ROW_NUM
		cout << setw(10) << "Row #" << setw(5) << right << row;
#endif
		cout << endl; 

#if WRITE_TO_FILE
		fileOutput << endl;
#endif
		column = 0;
		row++;
	}
}

void watch(const PRIME_TYPE &start) {

	const auto watching = new future<bool>[STEPSIZE];

	constexpr unsigned incre = 1 + INCREMENT_TWO;

	for(unsigned short i = 0; i < STEPSIZE; i += incre) {
		watching[i] = async(isPrime, start + i);
	}

	for(unsigned short i = 0; i < STEPSIZE; i += incre) {
		if(watching[i].get()) 
			printNum(start + i);
	}

	delete[ ] watching;
}

int main() {
	cout << header;

#if WRITE_HEADER_TO_FILE
		fileOutput << header << endl;
#else 
		cout << " | Did not print the header to the file!";
#endif

	cout << endl;

	const auto start = clock();
	auto lastSecond = start;

	for(PRIME_TYPE i = bounds[0]; i <= bounds[1]; i += STEPSIZE) {
		watch(i);

#if PRINT_AT_SECOND
		if(static_cast<double>(clock() - lastSecond) / CLOCKS_PER_SEC >= 1) {
			cout << " 1 second passed!";
			lastSecond = clock();
		}
#endif
	}

	cout << endl << "Milliseconds elapsed: " << (static_cast<double>(clock() - start) / CLOCKS_PER_MS) << endl;

	fileOutput.close();

#if WRITE_TO_FILE && ERROR_CHECK

		ifstream truePrimeStream(truePrimeFile.c_str());
		ifstream myPrimeStream(myPrimeFile.c_str());

		if(truePrimeStream && myPrimeStream) {

			cout << endl << "Error Search" << endl;
			cout << COLUMN_SET << right << "Mine" << COLUMN_SET << right << "True" << endl;

			PRIME_TYPE truePrime, myPrime;
			while(truePrimeStream >> truePrime && myPrimeStream >> myPrime) {

				if(myPrime != truePrime) {
					cout << COLUMN_SET << right << myPrime << COLUMN_SET << right << truePrime << endl;
				}
			}
		}

		truePrimeStream.close();
		myPrimeStream.close();
#endif

#ifdef _WIN32
	system ("pause");
#endif

	return 0;
}