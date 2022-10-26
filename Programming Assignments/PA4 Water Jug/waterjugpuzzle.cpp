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
#include <queue>
#include <bits/stdc++.h>
#include <stack>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    // tells user what to do - how you went from the parent to the current state
    string directions;
    // pointer of where you came from for each state (the state used to reach current state)
    // parent pointer of start state will be null
    State *parent;

    State() :
            a{-1}, b{-1}, c{-1}, directions{""}, parent{nullptr} {}

    State(int _a, int _b, int _c, string _directions) :
            a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} {}

    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

void bfs(int a, int b, int c, int ga, int gb, int gc) {
    State **array = new State *[a + 1];
    queue <State> bfsq;
    for (int i = 0; i < a + 1; i++) {
        array[i] = new State[b + 1];
        // Initialize the new row.
        fill(array[i], array[i] + (b + 1), State());
    }

    State s(0, 0, c, "Initial state.");
    bfsq.push(s);
    State curr;
    while (bfsq.size() != 0) {
        curr = bfsq.front();
        bfsq.pop();
        if (curr.a == ga && curr.b == gb && curr.c == gc) {
            stack <string> result;
            while (curr.parent != nullptr) {
                result.push(curr.directions + " " + curr.to_string());
                curr = *curr.parent;
            }
            result.push(curr.directions + " " + curr.to_string());
            while (result.empty() == false) {
                cout << result.top() << endl;
                result.pop();
            }
            for (int i = 0; i < a + 1; i++) {
                delete[] array[i];
            }
            delete[] array;
            return;
        }
        if (curr.a == array[curr.a][curr.b].a && curr.b == array[curr.a][curr.b].b &&
            curr.c == array[curr.a][curr.b].c) {
            continue;
        }
        array[curr.a][curr.b] = curr;

        // From C to A
        if (curr.c != 0 && curr.a != a) {
            string gal = "gallons";
            if (curr.c + curr.a > a) {
                if (a - curr.a == 1) {
                    gal = "gallon";
                }
                State ca(a, curr.b, curr.c + curr.a - a, "Pour " + to_string(a - curr.a) + " " + gal + " from C to A.");
                ca.parent = &array[curr.a][curr.b];
                bfsq.push(ca);
            } else {
                if (curr.c == 1) {
                    gal = "gallon";
                }
                State ca(curr.c + curr.a, curr.b, 0, "Pour " + to_string(curr.c) + " " + gal + " from C to A.");
                ca.parent = &array[curr.a][curr.b];
                bfsq.push(ca);
            }
        }

        // From B to A
        if (curr.b != 0 && curr.a != a) {
            string gal = "gallons";
            if (curr.b + curr.a > a) {
                if (a - curr.a == 1) {
                    gal = "gallon";
                }
                State ba(a, curr.b + curr.a - a, curr.c, "Pour " + to_string(a - curr.a) + " " + gal + " from B to A.");
                ba.parent = &array[curr.a][curr.b];
                bfsq.push(ba);
            } else {
                if (curr.b == 1) {
                    gal = "gallon";
                }
                State ba(curr.b + curr.a, 0, curr.c, "Pour " + to_string(curr.b) + " " + gal + " from B to A.");
                ba.parent = &array[curr.a][curr.b];
                bfsq.push(ba);
            }
        }

        // From C to B
        if (curr.c != 0 && curr.b != b) {
            string gal = "gallons";
            if (curr.c + curr.b > b) {
                if (b - curr.b == 1) {
                    gal = "gallon";
                }
                State cb(curr.a, b, curr.c + curr.b - b, "Pour " + to_string(b - curr.b) + " " + gal + " from C to B.");
                cb.parent = &array[curr.a][curr.b];
                bfsq.push(cb);
            } else {
                if (curr.c == 1) {
                    gal = "gallon";
                }
                State cb(curr.a, curr.b + curr.c, 0, "Pour " + to_string(curr.c) + " " + gal + " from C to B.");
                cb.parent = &array[curr.a][curr.b];
                bfsq.push(cb);
            }
        }

        // From A to B
        if (curr.a != 0 && curr.b != b) {
            string gal = "gallons";
            if (curr.a + curr.b > b) {
                if (b - curr.b == 1) {
                    gal = "gallon";
                }
                State ab(curr.a + curr.b - b, b, curr.c, "Pour " + to_string(b - curr.b) + " " + gal + " from A to B.");
                ab.parent = &array[curr.a][curr.b];
                bfsq.push(ab);
            } else {
                if (curr.a == 1) {
                    gal = "gallon";
                }
                State ab(0, curr.b + curr.a, curr.c, "Pour " + to_string(curr.a) + " " + gal + " from A to B.");
                ab.parent = &array[curr.a][curr.b];
                bfsq.push(ab);
            }
        }

        // From B to C
        if (curr.b != 0 && curr.c != c) {
            string gal = "gallons";
            if (curr.b + curr.c > c) {
                if (c - curr.c == 1) {
                    gal = "gallon";
                }
                State bc(curr.a, curr.b + curr.c - c, c, "Pour " + to_string(c - curr.c) + " " + gal + " from B to C.");
                bc.parent = &array[curr.a][curr.b];
                bfsq.push(bc);
            } else {
                if (curr.b == 1) {
                    gal = "gallon";
                }
                State bc(curr.a, 0, curr.b + curr.c, "Pour " + to_string(curr.b) + " " + gal + " from B to C.");
                bc.parent = &array[curr.a][curr.b];
                bfsq.push(bc);
            }
        }

        // From A to C
        if (curr.a != 0 && curr.c != c) {
            string gal = "gallons";
            if (curr.a + curr.c > c) {
                if (c - curr.c == 1) {
                    gal = "gallon";
                }
                State ac(curr.a + curr.c - c, curr.b, c, "Pour " + to_string(c - curr.c) + " " + gal + " from A to C.");
                ac.parent = &array[curr.a][curr.b];
                bfsq.push(ac);
            } else {
                if (curr.a == 1) {
                    gal = "gallon";
                }
                State ac(0, curr.b, curr.a + curr.c, "Pour " + to_string(curr.a) + " " + gal + " from A to C.");
                ac.parent = &array[curr.a][curr.b];
                bfsq.push(ac);
            }
        }
    }

    // Clear the 2D array from memory
    for (int i = 0; i < a + 1; i++) {
        delete[] array[i];
    }
    delete[] array;
    cout << "No solution." << endl;
}

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

    // solve the water jug puzzle
    bfs(A, B, C, a, b, c);
    return 0;
}
