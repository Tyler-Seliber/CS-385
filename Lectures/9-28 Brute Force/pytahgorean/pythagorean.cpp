#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/**
 * Struct to represent a Pythagorean triple: three positive
 * integers a, b, and c such that a^2 + b^2 = c^2.
 */
struct Triple {
    int a, b, c;

    Triple(int a_, int b_, int c_) : a{a_}, b{b_}, c{c_} {}

    // define the << operator for the Triple struct
    // two arguments
    //      t is the triple (use a reference to avoid copying). const because it isn't modified
    //      cout is of the type ostream (output stream). MUST use a reference, otherwise os would be a copy of cout, meaning two objects point to the same thing and results in garbage

    // operator<< needs to be a 'friend' of the Triple struct so that the operator can access the information within (such as t.a and t.b), even though it is public
    // a friend of a class is an unrelated class that is allowed (trusted) to view private info of the class
    friend ostream &operator<<(ostream &os, const Triple &t) {
        os << t.a << "^2 + " << t.b << "^2 = " << t.c << "^2";
        // ^ the << are the regular ones that would be used by C++ since these are just integers and strings
        return os;
        // ^ return cout because the next operator needs to work on cout
        // this is how you can chain cout statements with multiple << operators
        // - the endl will need to apply to a cout, which will have to be on the left of <<
        // need to return a reference!
    }
};

/**
 * Returns a vector of Pythagorean triples where all values (a, b, c) are
 * less than or equal to the limit.
 */
vector <Triple> find_pyth_triples(const int limit) {
    vector <Triple> result;

    for (int a = 1; a <= limit; a++) {
        for (int b = a + 1; b <= limit; b++) { // make b > a to avoid duplicate solutions
            for (int c = b + 1; c <= limit; c++) { // make c > b because a is greater than 1 - reduces run time
                if (a * a + b * b == c * c) {
                    result.push_back(Triple(a, b, c));
                }
            }
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <limit>" << endl;
        return 1;
    }
    int limit;
    // convert input to integar
    istringstream iss;

    iss.str(argv[1]);
    if (!(iss >> limit) || limit < 3) {
        cerr << "Error: limit must be an integer >= 3." << endl;
        return 1;
    }
    vector <Triple> triples = find_pyth_triples(limit);
    for (const auto &triple: triples) { // use a reference to avoid copying
        cout << triple << endl;
        // why can we print the triple nicely automatically?
        /*
         * inside the triple is just a, b, and c.
         * there is a similar concept to toString()
         *
         * << is a binary operation
         * C++ allows you to take existing operators and extend them to your own data types
         */
    }
    return 0;
}
