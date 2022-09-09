#include <iostream>

using namespace std;

void pass_by_value(int k) {
    k = 10;
}

void pass_by_pointer(int *k) {
    *k = 10;
    // does not modify k
}

// & is not the "address of" operator here, it is just a notation
// to indicate that k is passed by reference.
// pass by reference is meant for convenience to not need *k everywhere in the code (convenient alternative to pass by pointer - the compiler will automatically convert it)
void pass_by_reference(int &k) {
    k = 10;
}

// The array parameter is in fact a pointer but we can use it
// as if it were the name of the array itself.
void display_array(int array[], int length) {
    for (int i = 0; i < length; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

// The array parameter is a pointer and we use pointer arithmetic.
void display_array_ptr(int *array, int length) {
    for (int *p = array; p < array + length; p++) {
        cout << *p << " ";
    }
    cout << endl;
}

int main() {
    int x;  // Type: integer
    x = 5;  // Store the integer 5 into x.
    int *z; // Type: pointer to integer
    z = &x; // Store the address of integer x into z. - hexadecimal address
    // int x = 5, *z = &x; // Shorter version of the above.
    cout << x << " " << &x << " " << z << " " << &z << endl;
    // Pointer dereference: if z == &x then *z is the same as x itself.
    // Do not confuse the * dereference operator and the * pointer type.
    cout << "*z is: " << *z << endl;
    // ^ would be the same as replacing *z with x
    *z = 7; // Same as: x = 7, changes the value of x, z does not change though (still points to x)
    cout << x << " " << &x << " " << z << " " << &z << endl;
    // ^ z still points to x, so it is still the same address
    cout << "*z is: " << *z << endl;
    // Do not do this:
    // z += 30000;
    // ^ z is now pointing to a random address, so it is not pointing to x anymore. Could be anything
    // This is allowed by c++ compiler, but should not be done
    // cout << "*z is: " << *z << endl;
    // ^ this will NOT work, you can't dereference a random address. Might crash, work, or give garbage
    // Note: when you get a segmentation fault, you can use gdb from
    // the command line to find the source of the problem.

    // why use pointers?
    // 1) function calls - change data of one variable in another function
    x = 5;
    // k (see the function definition) is a copy of x; changing k
    // does not change x; this function call is useless.
    pass_by_value(x);
    cout << "x is: " << x << endl;

    // k (see the function definition) is a copy of &x, so k points
    // at x; *k is then the same as x, so changing *k changes x.
    pass_by_pointer(&x);
    cout << "x is: " << x << endl;

    x = 5;
    // k (see the function definition) is an alias (another name) for x,
    // so changing k changes x.  Internally the compiler implements pass
    // by reference by rewriting your code to use a pointer (the way pass
    // by pointer works) so pass by reference is just for the convenience
    // of the C++ programmer because it makes the code easier to write.
    pass_by_reference(x);
    cout << "x is: " << x << endl;

    // 2) "un-initialized" variables

    /*
      * Arrays in C++
      * int A[10]; creates an array of 10 integers called 'A' (sized of array is fixed)
      * A[3] = 7; sets value
    */

    // Pointer to an anonymous variable-length array which is dynamically
    // allocated on the heap (as variable-length arrays must be):

    int *values = new int[x]; // size is decided at runtime
    /*
     * same as
     * int *values;
     * values = new int[x]; values points to first element
     */
    // loop over every element in the array using the pointer (since array doesn't have a name)
    // in c++, you can use the name of the pointer as if it was the name of the array
    for (int i = 0; i < x; i++) {
        // Using the pointer as if it were the name of the array:
        values[i] = i;
        // or using pointer arithmetic (which is what the CPU really does):
        *(values + i) = i;
    }
    // Using the pointer as if it were the name of the array:
    display_array(values, x);
    display_array_ptr(values, x);

    // MUST delete the array in C++ once you are done with it since there is no garbage collection. This frees up memory
    // Deleting the array (the pointer is not modified):
    delete[] values;
    // ^ need to include [] to tell c++ that this is pointing to an array

    // after deleting, you can't use the pointer anymore
    // values[3] may or may not result in weird behavior
    return 0;
}
