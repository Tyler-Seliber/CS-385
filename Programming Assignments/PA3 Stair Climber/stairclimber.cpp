/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Tyler Seliber
 * Date        : October 8, 2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector <vector<int>> get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector <vector<int>> solutions;
    if (num_stairs <= 0) {
        solutions.insert(solutions.begin(), vector<int>());
    }

    for (int i = 1; i < 4; i++) {
        if (num_stairs >= i) {
            vector <vector<int>> result = get_ways(num_stairs - i);
            // Prepending i to all solutions in result
            for (long unsigned int j = 0; j < result.size(); j++) {

                result.at(j).insert(result.at(j).begin(), i);
            }
            solutions.insert(solutions.end(), result.begin(), result.end());
        }
    }
    return solutions;
}

void display_ways(const vector <vector<int>> &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int count = 1;
    for (auto way = ways.begin(); way != ways.end(); way++) {
        cout << count << ". ";
        for (auto step = way->begin(); step != way->end(); step++) {
            cout << *step << ", ";
        }
        cout << endl;
        count++;
    }
}

int main(int argc, char *const argv[]) {
    // reads and parses command line arguments.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }
    istringstream iss;
    int num_stairs;
    iss.str(argv[1]);
    if (!(iss >> num_stairs) || num_stairs <= 0) {
        cerr << "Error: Number of stairs must be a positive integer" << endl;
        return 1;
    }
    iss.clear();
    display_ways(get_ways(num_stairs));
    return 0;

}
