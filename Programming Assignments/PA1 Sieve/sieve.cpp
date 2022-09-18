/*******************************************************************************
 * Filename: sieve.cpp
 * Author  : Tyler Seliber
 * Version : 1.0
 * Date    : September 21, 2022
 * Description: Find prime numbers using the sieve of Eratosthenes.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cmath>
#include <iomanip>
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
PrimesSieve::PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
    // object is separate in memory from the array, so if the object is deleted it wont delete the array. -> somewhere in the code, we also need to delete the array (for every 'new' there must be a 'delete') - in the destructor
    sieve();
}

// display_primes() method for the PrimesSieve class
void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the requirements document.
    const int max_prime_width = num_digits(max_prime_);
    const int max_char = 80;
    const int primes_per_row = max_char / (max_prime_width + 1);
    if (primes_per_row > num_primes_) {
        for (int i = 2; i < limit_ + 1; i++) {
            if (is_prime_[i] == true) {
                cout << i;
                if (i != max_prime_) {
                    cout << " ";
                }
            }

        }
    } else {
        int char_count = 0;
        for (int i = 2; i <= limit_ + 1; i++) {
            if (is_prime_[i] == true) {
                if (char_count >= max_char - max_prime_width) {
                    cout << "" << endl;
                    char_count = 0;
                }
                cout << setw(max_prime_width);
                cout << i;
                char_count += max_prime_width;
                if (i == max_prime_) {
                    return;
                } else if (char_count < max_char - max_prime_width) {
                    cout << " ";
                    char_count += 1;
                }
            }
        }
    }
//    cout << endl;
}

// count the number of primes found
int PrimesSieve::count_num_primes() const {
    int num_primes = 0;
    for (int i = 2; i <= limit_; i++) {
        if (is_prime_[i] == true) {
            num_primes++;
        }
    }
    return num_primes;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // initialize the array
    for (int i = 2; i <= limit_ + 1; i++) {
        is_prime_[i] = true;
    }
    // run the loops
    for (int i = 2; i < sqrt(limit_ + 1); i++) {
        if (is_prime_[i] == true) {
            for (int j = pow(i, 2); j <= limit_ + 1; j += i) {
                is_prime_[j] = false;
            }
        }
    }
    // find the number of primes (num_primes_, max_prime_)
    num_primes_ = count_num_primes();

    // determine max_prime_
    for (int i = limit_; i > 0; i--) {
        if (is_prime_[i] == true) {
            max_prime_ = i;
            break;
        }
    }

}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count = 0;
    while (num > 0) {
        num /= 10;
        count++;
    }
    return count;
}

int main() {
    cout << "**************************** " << "Sieve of Eratosthenes" <<
         " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
//    cout << endl;
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
    PrimesSieve *primes = new PrimesSieve(limit);
    cout << endl;
    cout << "Number of primes found: " << primes->num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    primes->display_primes();
    delete primes;
    return 0;
}
