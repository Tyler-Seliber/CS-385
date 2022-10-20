/*******************************************************************************
 * Filename: waterjugpuzzle.cpp
 * Author  : Hyeonu Ju & Tyler Seliber
 * Version : 1.0
 * Date    : October 22, 2022
 * Description: C++ code to solve the water jug puzzle.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    // tells user what to do - how you went from the parent to the current state
    string directions;
    // pointer of where you came from for each state (the state used to reach current state)
    // parent pointer of start state will be null
    State *parent;

    State(int _a, int _b, int _c, string _directions) :
            a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} {}

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

int main(int argc, char *argv[]) {
    // Get input
    istringstream iss;
    int A = -1, B = -1, C = -1, a = -1, b = -1, c = -1;
    int *pA = &A, *pB = &B, *pC = &C, *pa = &a, *pb = &b, *pc = &c;
    // Create an array of pointers for the above integers (reduce lines of code for passing data into the variables)
    int *args[6] = {pA, pB, pC, pa, pb, pc};

    if (argc != 7) {
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        iss.str(argv[i]);
        // check for invalid capacities
        if (i < 4 && (!(iss >> *args[i - 1]) || *args[i - 1] <= 0)) {
            cerr << "Error: Invalid capacity '" << argv[i] << "' for jug " << static_cast<char>(i + 64) << "." << endl;
            return 1;
        }
        // check for invalid goals
        if (i >= 4 && (!(iss >> *args[i - 1]) || *args[i - 1] < 0)) {
            cerr << "Error: Invalid goal '" << argv[i] << "' for jug " << static_cast<char>(i - 3 + 64) << "." << endl;
            return 1;
        }
        iss.clear();
    }
    // check if goals exceed capacities of the jugs
    for (int i = 3; i < 6; i++) {
        if (*args[i] > *args[i - 3]) {
            cerr << "Error: Goal cannot exceed capacity of jug " << static_cast<char>(i - 2 + 64) << "." << endl;
            return 1;
        }
    }

    // check if goal exceeds capacity of C
    int sum_goals = a + b + c;
    if (sum_goals != C) {
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }

    cout << A << " " << B << " " << C << " " << a << " " << b << " " << c << endl;


    State s(0, 0, 8, "Initial state.");
    cout << s.to_string() << endl;
    s.a += 3;
    s.c -= 3;
    cout << s.to_string() << endl;
    return 0;
}
