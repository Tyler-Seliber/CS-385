/*******************************************************************************
 * Name        : sieve.cpp
 * Author      :
 * Date        :
 * Description : Sieve of Eratosthenes
 * Pledge      :
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    // in C++, you can move the code for functions outside the class.
    // Usually, you only define the types in the class or very small methods (like getters/setters)
    // This is standard convention for C++
    PrimesSieve(int limit);

    // ~ signifies destructor. This is automatically called by C++ every time an object disappears/is removed from memory
    ~PrimesSieve() {
        delete[] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool *const is_prime_; // dynamically allocated array determined by limit inputted by user
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;

    void sieve();

    static int num_digits(int num);
};

// Constructor for the PrimesSieve class
PrimesSieve::PrimesSieve(int limit) :
// object is separate in memory from the array, so if the object is deleted it wont delete the array. -> somewhere in the code, we also need to delete the array (for every 'new' there must be a 'delete') - in the destructor
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

// display_primes() method for the PrimesSieve class
void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    return 0;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // initialize the array
    // run the loops
    // find the number of primes (num_primes_, max_prime_)
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    return 0;
}

int main() {
    cout << "**************************** " << "Sieve of Eratosthenes" <<
         " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if (!(iss >> limit)) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    // create ONE object here (either using local variable or 'new')
    return 0;
}
