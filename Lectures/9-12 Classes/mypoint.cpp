#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class MyPoint {
    // write public/private section by section
    // typically instance variables are private, constructors and methods are public
public:
    // Constructor that uses an initializer list.
    // Constructor shares same name as class
    MyPoint(int x, int y, float z) : x_{x}, y_{y}, z_{z} {};
    // : is the initializer list, so no code is necessary
    // x -> x_, and so on
    // good for simple constructors, could also use x_ = x or using 'this' pointer

    // Methods that do not modify member variables should be declared const.
    // const methods do not change any data in the object. it's optional, but good to include for compiler to give more detailed error messages
    void print_coords() const {
        cout << "(x, y, z) = (" << x_ << ", " << y_ << ", " << fixed
             << setprecision(2) << z_ << ")" << endl;
    }

    // Mutator (setter).
    void set_x(int x) {
        x_ = x;
    }

    // Accessor (getter), declared const.
    int get_x() const {
        return x_;
    }

private:
    // Member (instance) variables (fields). Use the trailing _ for these variables.
    int x_, y_;
    float z_;
}; // semicolon is required!

// Pass by reference, and using an iterator (which is an object
// that can be used essentially as if it were a pointer):
void display_points(const vector<MyPoint> &points) {
    // loop using iterator
    for (auto it = points.cbegin(); it != points.cend(); it++) {
        // ^ cbegin() method creates a new object, which is the iterator. iterator object automatically knows how to iterate
        // ^ as long as iterator hasn't reached cend, it will keep going
        it->print_coords(); // Same as: (*it).print_coords(); - dereferencing on iterators get current element in the vector - () is mandatory
        // inside the loop, use iterators as if they were pointers
    }
}

void display_points_v2(const vector<MyPoint> &points) {
    // for loop with index
    for (size_t i = 0; i < points.size(); i++) {
        // ^ size_t: size() method doesn't return integers by default because it might be too small. size() returns a type size_t
        // it is a type just for size built in to C++, but it will work.
        // using 'int' will not usually work
        points[i].print_coords();
    }
}

int main() {
    int x, y;

    // Objects allocated on the stack:
    // these are local variables, exist only as long as the function they are in is running.
    // C++ doesn't require using 'new' keyword for objects.
    // the local variables can't be manually deleted. it automatically deletes once the function finishes.
    MyPoint point1(5, 7, 1.9823412);
    MyPoint point2(1, 2, 3);
    MyPoint point3(4, 5, 6);
    point2.print_coords();

    // add points to end of the vector
    vector<MyPoint> points;
    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);

    // find all points with x above 2, put them in another vector
    vector<MyPoint> points_above_two;
    // For-each/enhanced for loop (using a reference so there is no copy):
    for (const auto &point: points) {
        // ^ const = not going change elements of vector, just read them.
        // ^ auto = compiler automatically determines the type of the variable based on the type of the vector
        // ^ & is part of the TYPE -> point is not a separate variable or memory address/pointer, just a reference. This prevents copying
        if (point.get_x() > 2) {
            points_above_two.push_back(point);
        }
    }
    // only points 1 and 3 should be in this vector
    display_points(points_above_two);

    // Practice using standard in (STDIN)
    cout << "Input x: ";
    cin >> x;

    cout << "Input y: ";
    cin >> y;

    /*
     * creating objects using 'new'.
     * created when you use 'new' and will stay in memory until you call delete. (doesn't only exist as long as the function is running).
     * it doesn't have a name (anonymous in memory).
     * for new object, it returns the start address in memory of where the object is.
     * it's not a local variable (it's dynamically allocated).
     */
    // Object allocated on the heap:
    MyPoint *point4 = new MyPoint(x, y, 7);
    // point4 itself is a local variable, but what it's pointing to isn't
    // Calling the method using the pointer to the object.
    point4->print_coords(); // Same as: (*point4).print_coords();
    // ^ dereference the pointer


    // can't delete local variables (point1), they automatically disappear when the function ends. can only delete something that was created with 'new'.
    // can't directly delete the pointer since it's a local variable.
    // But, this code will delete the object the pointer points to
    delete point4;
    // the pointer will still contain the address of where the object used to be before it was deleted. But you can't try to dereference it since nothing is there (gets unexpected behavior)

    // delete [] would be for deleting arrays
    return 0;
}
