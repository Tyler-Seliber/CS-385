/*******************************************************************************
 * Filename: sqrt.cpp
 * Author  : Tyler Seliber
 * Version : 1.0
 * Date    : September 8, 2022
 * Description: Computes the square root of a double using Newton's method.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>

using namespace std;

// estimate the square root using Newton's method
double sqrtRecur(double num, double lastGuess, double epsilon) {

    double nextGuess = (lastGuess + num / lastGuess) / 2;
    if (abs(nextGuess - lastGuess) < epsilon) {
        return nextGuess;
    }
    return sqrtRecur(num, nextGuess, epsilon);
}

double sqrt(double num, double epsilon) {
    if (num < 0) {
        return numeric_limits<double>::quiet_NaN();
    } else if (num == 0 || num == 1) {
        return num;
    }
    return sqrtRecur(num, num, epsilon);
}

int main(int argc, char *argv[]) {

    istringstream iss;
    double val;
    double eps;

    // check arguments
    if (!(argc == 2 || argc == 3)) {
        cout << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }

    // read first argument <value>
    iss.str(argv[1]);
    if (!(iss >> val)) {
        cout << "Error: Value argument must be a double." << endl;
        return 1;
    }

    iss.clear();
    // determine if epsilon was provided as argument
    if (argc == 3) {
        // read second argument <epsilon>
        iss.str(argv[2]);
        if (!(iss >> eps) || eps <= 0) {
            cout << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
    } else {
        // set default epsilon
        eps = 1e-7;
    }

    // format the output
    cout << fixed;
    cout << setprecision(8);
    cout << sqrt(val, eps) << endl;

    return 0;
}