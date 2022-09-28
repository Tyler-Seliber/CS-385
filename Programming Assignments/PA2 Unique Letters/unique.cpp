/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Tyler Seliber
 * Date        : October 1, 2022
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    return false;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only a single int for storage and work with bitwise
    // and bitshifting operators.  Using any other kind of solution will
    // automatically result in a grade of ZERO for the whole assignment.

    return false;
}

int main(int argc, char *const argv[]) {
    // reads and parses command line arguments.

    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    }

    // Check if string contains only lowercase letters
    string str = argv[1];
    bool hasUpper = false;
    bool hasNum = false;
    for (char c: str) {
        hasUpper = !islower(c);
        hasNum = isdigit(c);
        if (hasUpper || hasNum) {
            break;
        }
    }
    if (hasUpper || hasNum) {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }


    // Calls other functions to produce correct output.

    cout << str << endl;
    return 0;
}
