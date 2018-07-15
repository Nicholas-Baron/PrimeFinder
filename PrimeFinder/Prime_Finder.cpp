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
#include <chrono>
//END INCLUDES

//Boolean Options
#define WRITE_TO_FILE 0
#define WRITE_HEADER_TO_FILE 0
#define INCREMENT_TWO 1
#define ERROR_CHECK 0
#define PRINT_AT_SECOND 0
#define PRINT_ROW_NUM 0

const std::string myPrimeFile = "primes.txt";
const std::string truePrimeFile = "true_primes.txt";
const std::string printSize = "Using " + std::to_string (sizeof (PRIME_TYPE) * 8) + "-bit numbers";

constexpr PRIME_TYPE bounds[ ] = { 3,  9'999 };
constexpr auto amountOfNumbers = bounds[1] - bounds[0];

constexpr unsigned short STEPSIZE = 100;
constexpr auto numGroups = amountOfNumbers / STEPSIZE;

constexpr unsigned short NUM_COLUMNS = 20;
constexpr unsigned short COLUMN_WIDTH = 10;
#define COLUMN_SET std::setw(COLUMN_WIDTH)

const std::string numToAnalyze = "Will analyze " + std::to_string (amountOfNumbers) + " numbers in " + std::to_string (numGroups) + " groups.";
const std::string header = printSize + " | " + numToAnalyze;

std::ofstream fileOutput (myPrimeFile.c_str ( ));

void printNum (const PRIME_TYPE &i) {

	static short column = 0;
	static short row = 1;

	std::cout << COLUMN_SET << i;

	if constexpr (WRITE_TO_FILE)
		fileOutput << COLUMN_SET << i;

	column++;

	if (column == NUM_COLUMNS) {

		using namespace std;

		if constexpr (PRINT_ROW_NUM){
			cout << setw (10) << "Row #" << setw (5) << right << row;
		}
		cout << endl;
		
		if constexpr ( WRITE_TO_FILE ) {
			fileOutput << endl;
		}
		
		column = 0;
		row++;
	}
}

void watch (const PRIME_TYPE &start) {

	using namespace std;

	constexpr unsigned short incre = 1 + INCREMENT_TWO;
	const auto watching = new future<bool>[STEPSIZE];

	for (unsigned short i = 0; i < STEPSIZE; i += incre) {
		watching[i] = async (isPrime, start + i);
	}

	for (unsigned short i = 0; i < STEPSIZE; i += incre) {
		if (watching[i].get())
			printNum (start + i);
	}

	delete[ ] watching;
}

int main ( ) {

	using namespace std;
	cout << header;

	if constexpr ( WRITE_HEADER_TO_FILE ) {
		fileOutput << header << endl;
	} else {
		cout << " | Did not print the header to the file!";
	}

	cout << endl;

	using namespace std::chrono;
	const auto start = high_resolution_clock::now ( );

	if constexpr ( PRINT_AT_SECOND ){
		auto lastSecond = start;
	}

	for (PRIME_TYPE i = bounds[0]; i <= bounds[1]; i += STEPSIZE) {
		watch (i);

		//This is needed as lastSecond is in a different scope
#if PRINT_AT_SECOND
		if (high_resolution_clock::now ( ) - lastSecond >= 1s) {
			cout << " 1 second passed!";
			lastSecond = high_resolution_clock::now ( );
		}
#endif
	}

	cout << endl << "Milliseconds elapsed: " << duration_cast<milliseconds>( high_resolution_clock::now ( ) - start ).count ( ) << endl;

	fileOutput.close ( );

	if constexpr ( WRITE_TO_FILE && ERROR_CHECK ) {

		ifstream truePrimeStream (truePrimeFile.c_str ( ));
		ifstream myPrimeStream (myPrimeFile.c_str ( ));

		if (truePrimeStream && myPrimeStream) {

			cout << endl << "Error Search" << endl;
			cout << COLUMN_SET << right << "Mine" << COLUMN_SET << right << "True" << endl;

			PRIME_TYPE truePrime, myPrime;
			while (truePrimeStream >> truePrime && myPrimeStream >> myPrime) {

				if (myPrime != truePrime) {
					cout << COLUMN_SET << right << myPrime << COLUMN_SET << right << truePrime << endl;
				}
			}
		} else { 
			cout << "Failed to find file(s) ";
			if (!truePrimeStream) {
				cout << truePrimeFile << " ";
			}
			if (!myPrimeStream) {
				cout << myPrimeFile;
			}
			cout << endl;
		}

		truePrimeStream.close ( );
		myPrimeStream.close ( );
	}

#ifdef _WIN32
	system ("pause");
#endif

	return 0;
}