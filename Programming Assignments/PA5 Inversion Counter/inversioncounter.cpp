/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Tyler Seliber
 * Version     : 1.0
 * Date        : November 5, 2022
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long count = 0;
    for (long i = 0; i < length; i++) {
        for (long j = i + 1; j < length; j++) {
            if (array[i] > array[j]) {
                count++;
            }
        }
    }
    return count;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    int *scratch = new int[length];
    long count = mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return count;
}

static long merge(int a[], int b[], int low, int mid, int high) {
    // TODO
    long count = 0;
    int i1 = low, i2 = mid + 1, i = low;
    while (i1 <= mid && i2 <= high) {
        if (a[i1] <= a[i2]) {
            b[i++] = a[i1++];
        } else {
            b[i++] = a[i2++];
            count += mid - i1 + 1;
        }
    }
    for (; i1 <= mid;) {
        b[i++] = a[i1++];
    }
    for (; i2 <= high;) {
        b[i++] = a[i2++];
        count += mid - i1 + 1;
    }
    for (i = low; i <= high; i++) {
        a[i] = b[i];
    }
    return count;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long count = 0;
    if (low < high) {
        int mid = (high + low) / 2;
        count += mergesort(array, scratch, low, mid);
        count += mergesort(array, scratch, mid + 1, high);
        count += merge(array, scratch, low, mid, high);
    }
    return count;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    } else if (argc == 2) {
        string arg = argv[1];
        if (arg != "slow") {
            cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
            return 1;
        }
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;


    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if (values.size() == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    // TODO: produce output

    if (argc == 2) {
        cout << "Number of inversions: " << count_inversions_slow(values.data(), values.size()) << endl;
    } else {
        cout << "Number of inversions: " << count_inversions_fast(values.data(), values.size()) << endl;
    }

    return 0;
}
