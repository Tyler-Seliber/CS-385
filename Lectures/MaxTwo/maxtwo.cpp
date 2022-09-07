// Lecture 9/7/22
#include <iostream>
// sstream = string stream
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

/*
 * Computes the max of two integers m and n.
 */
//int max(int m, int n) {
//	return m > n ? m : n;
//}
// argc tells you how many args have been inputted (including the main command). So for this program, argc = 3
// length of argv = argc; each element is a string and contains everything the user entered in the command line
//int main(int argc, char* argv[]) {
//	int m, n;
//	istringstream iss; // input string stream variable
//
//	if(argc != 3) {
//		cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
//		return 1;
//	}
//	iss.str(argv[1]);
//	if(!(iss >> m)) { // Read one integer from iss and check for failure too.
//		cerr << "Error: the first argument is not a valid integer" << endl;
//		return 1;
//	}
//	iss.clear(); // Remember to clear iss before using it with another string!
//	iss.str(argv[2]);
//	if(!(iss >> n)) {
//		cerr << "Error: the second argument is not a valid integer" << endl;
//		return 1;
//	}
//	cout << "m is: " << m << endl;
//	cout << "n is: " << n << endl;
//	cout << "max(" << m << ", " << n << ") is: " << max(m, n) << endl;
//	return 0;
//}

// functions must be defined before their use

// don't need if you #include<algorithm>
int max(int a, int b) {
//    if (a > b) {
//        return a;
//    } else {
//        return b;
//    }
    return (a > b) ? a : b;
    // condition ? return if true : return if false
}

int main(int argc, char* argv[]) {
    //input string stream - object from which we can read from a string
    istringstream iss;
    int m;
    int n;

    // check for two arguments
    if(argc != 3) {
        // cerr is used for giving errors. May not appear different to user, but can depend on compilers
        // argv[0] is guaranteed to be name of program
        cerr << "Usage: " << argv[0] << " <integer m>  <integer n>" << endl;
        // return something other than 0 for error
        return 1;
    }

    // need to transform arguments into integers
    // initialize iss object with first argument
    iss.str(argv[1]);
    // read the int from iss, store in m. m is already defined as an int, so don't need to specify for iss. iss does all the processing
    // >> is the reading operator
    // << is the writing operator
    if(!(iss >> m)) {
        // ^ >> returns a result, so can wrap in if to test
        // (iss >> m) will return true if conversion succeeds
        // !(iss >> m) will return true if conversion fails so we can print an error message
        cerr << "first argument must be an integer" << endl;
        return 1;
    }

    // **MUST** reset iss object before processing further strings, otherwise program will be wonky
    iss.clear();

    // do same for argv[2]
    iss.str(argv[2]);
    if(!(iss >> n)) {
        cerr << "second argument must be an integer" << endl;
        return 1;
    }
    cout << "m: " << m << endl;
    cout << "n: " << n << endl;

    // compute max
    cout << "max(" << m << ", " << n << ") is " << max(m,n) << endl;

//    return 0;

    // how to format floating point numbers
    cout << 1 / 3 << endl; // should be 0.33333, but is 0 because of integer division
    // for floating point result, one number must be floating point
    cout << 1.0 / 3 << endl;
    cout << 1.0 / 300000.0 << endl; // will result in scientific notation
    // if you dont want that, must tell cout how to format numbers
    cout << fixed; // need to include <iomanip>
    cout << 1.0 / 300000.0 << endl;
    // need to tell cout how many digits after decimal
    cout << setprecision(20);
    cout << 1.0 / 300000.0 << endl;

    // could also do: cout << fixed << setprecision(20) << 1.0 / 3000000.0 << endl;

    return 0;

}