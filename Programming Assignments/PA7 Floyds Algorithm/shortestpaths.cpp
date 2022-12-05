/*******************************************************************************
 * Filename: shortestpaths.cpp
 * Author  : Hyeonu Ju & Tyler Seliber
 * Version : 1.0
 * Date    : December 7, 2022
 * Description: Solves the all-pairs shortest paths problem with Floyd's algorithm.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>

using namespace std;

// /**
//  * Displays the matrix on the screen formatted as a table. */
// void display_table(long **const matrix, const string &label, const bool use_letters = false)
// {
//     // ** CHANGE THESE PLACEHOLDER VALUES **
//     const int num_vertices = 5;


//     cout << label << endl;
//     long max_val = 0;
//     for (int i = 0; i < num_vertices; i++)
//     {
//         for (int j = 0; j < num_vertices; j++)
//         {
//             long cell = matrix[i][j];
//             if (cell < INF && cell > max_val)
//             {
//                 max_val = matrix[i][j];
//             }
//         }
//     }
//     int max_cell_width = use_letters ? len(max_val) : len(max(static_cast<long>(num_vertices), max_val));
//     cout << ' ';
//     for (int j = 0; j < num_vertices; j++)
//     {
//         cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
//     }
//     cout << endl;
//     for (int i = 0; i < num_vertices; i++)
//     {
//         cout << static_cast<char>(i + 'A');
//         for (int j = 0; j < num_vertices; j++)
//         {
//             cout << " " << setw(max_cell_width);
//             if (matrix[i][j] == INF)
//             {
//                 cout << "-";
//             }
//             else if (use_letters)
//             {
//                 cout << static_cast<char>(matrix[i][j] + 'A');
//             }
//             else
//             {
//                 cout << matrix[i][j];
//             }
//         }
//         cout << endl;
//     }
//     cout << endl;
// }

int main(int argc, const char *argv[])
{
    // Make sure the right number of command line arguments exist.
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file)
    {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try
    {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line))
        {
            cout << line_number << ":\t" << line << endl;
            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();
    }
    catch (const ifstream::failure &f)
    {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}
