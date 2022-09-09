// Lecture 9/3/22
// iostream = input/output stream - contains definitions for std and therefore cout
#include <iostream>
// using namespace std - allows us to use cout without std::cout
using namespace std;

// main function **must** return integer. 0 is the convention for success.
int main()
{
    // Print
    // cout is an object - output stream. it represents the screen of your computer
    // << is the insertion operator for sending data to an object
    cout << "hello world" << endl;
    cout << 345 << "oiewrgowerg" << endl;
    cout << "enter a string: ";
    string s;
    cin >> s;
    cout << "s is: " << s << endl;
    return 0;
}