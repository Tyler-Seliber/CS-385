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
#include <vector>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

/*
 * Recursive function to display the path taken to get from vertex v1 to vertex v2 by inspecting the intermediate matrix.
 */
void compute_paths(long **const path_matrix, long **const intermediate_matrix, long v1, long v2)
{
    char v1_char = (char)v1 + 65;
    // If the vertices are the same, do nothing.
    if (v1 == v2)
    {
        return;
    }
    // If the vertices are the same, do nothing.
    else if (intermediate_matrix[v1][v2] == LLONG_MAX)
    {
        cout << v1_char << " -> ";
    }
    else
    {
        compute_paths(path_matrix, intermediate_matrix, v1, intermediate_matrix[v1][v2]);
        compute_paths(path_matrix, intermediate_matrix, intermediate_matrix[v1][v2], v2);
    }
}

/*
 * Computes the length (number of digits) of a value.
 */
int length_of_value(long value)
{
    int length = 0;
    while (value != 0)
    {
        value /= 10;
        length++;
    }
    return length;
}

/*
 * Displays the matrix on the screen formatted as a table.
 */

void display_table(long **const matrix, const string &label, int num_vertices, const bool use_letters = false)
{
    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            long cell = matrix[i][j];
            if (cell < LLONG_MAX && cell > max_val)
            {
                max_val = matrix[i][j];
            }
        }
    }

    int max_cell_width = use_letters ? length_of_value(max_val) : length_of_value(max(static_cast<long>(num_vertices), max_val));
    if (max_cell_width < 1)
    {
        max_cell_width++;
    }
    cout << ' ';
    for (int j = 0; j < num_vertices; j++)
    {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++)
    {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++)
        {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == LLONG_MAX)
            {
                cout << "-";
            }
            else if (use_letters)
            {
                cout << static_cast<char>(matrix[i][j] + 'A');
            }
            else
            {
                cout << matrix[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}

void floyd_algorithm(vector<string> values, long num_vertices)
{
    // Create the distance, path, and intermediate matrices.
    long **disMatrix = new long *[num_vertices];
    for (int i = 0; i < num_vertices; ++i)
    {
        disMatrix[i] = new long[num_vertices];
    }

    long **pathMatrix = new long *[num_vertices];
    for (int i = 0; i < num_vertices; ++i)
    {
        pathMatrix[i] = new long[num_vertices];
    }

    long **interMatrix = new long *[num_vertices];
    for (int i = 0; i < num_vertices; ++i)
    {
        interMatrix[i] = new long[num_vertices];
    }

    // initialize distance, path, and intermediate matrix
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            if (i == j)
            {
                disMatrix[i][j] = 0;
                pathMatrix[i][j] = 0;
            }
            else
            {
                disMatrix[i][j] = LLONG_MAX;
                pathMatrix[i][j] = LLONG_MAX;
            }
            interMatrix[i][j] = LLONG_MAX;
        }
    }

    // filling distance and path matrix
    for (auto it = values.begin(); it != values.end(); it++)
    {
        disMatrix[(*it).substr(0, 1)[0] - 65][(*it).substr(2, 1)[0] - 65] = stoi((*it).substr(4));
        pathMatrix[(*it).substr(0, 1)[0] - 65][(*it).substr(2, 1)[0] - 65] = stoi((*it).substr(4));
    }

    // Floyd's Algorithm
    for (int k = 0; k < num_vertices; k++)
    {
        for (int i = 0; i < num_vertices; i++)
        {
            for (int j = 0; j < num_vertices; j++)
            {
                if (pathMatrix[i][k] != LLONG_MAX && pathMatrix[k][j] != LLONG_MAX && pathMatrix[i][k] + pathMatrix[k][j] < pathMatrix[i][j])
                {

                    pathMatrix[i][j] = pathMatrix[i][k] + pathMatrix[k][j];
                    interMatrix[i][j] = k;
                }
            }
        }
    }
    // Print out the matrices
    display_table(disMatrix, "Distance matrix:", num_vertices);
    display_table(pathMatrix, "Path lengths:", num_vertices);
    display_table(interMatrix, "Intermediate vertices:", num_vertices, true);

    // Print out the paths and distances
    for (long i = 0; i < num_vertices; i++)
    {
        char v1 = (char)i + 65;
        for (long j = 0; j < num_vertices; j++)
        {
            char v2 = (char)j + 65;
            long distance = pathMatrix[i][j];
            if (distance == LLONG_MAX)
            {
                cout << v1 << " -> " << v2 << ", distance: infinity, path: none" << endl;
            }
            else
            {
                string distance_str = to_string(distance);
                cout << v1 << " -> " << v2 << ", distance: " << distance_str << ", path: ";
                compute_paths(pathMatrix, interMatrix, i, j);
                cout << v2 << endl;
            }
        }
    }
    // Delete the matrices from memory
    for (int i = 0; i < num_vertices; i++)
    {
        delete[] disMatrix[i];
        delete[] pathMatrix[i];
        delete[] interMatrix[i];
    }
    delete[] disMatrix;
    delete[] pathMatrix;
    delete[] interMatrix;
}

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

    int num_vertices = 0;
    vector<string> values;

    try
    {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line))
        {
            string full_line = line;
            if (line_number == 1) // First line -> number of vertices
            {
                try
                {
                    num_vertices = stoi(line);
                    // First line -> number of vertices
                    if (num_vertices < 1 || num_vertices > 26)
                    {
                        cerr << "Error: Invalid number of vertices '" << full_line << "' on line 1." << endl;
                        return 1;
                    }
                }
                catch (invalid_argument &e) // If the number of vertices is not a number
                {
                    cerr << "Error: Invalid number of vertices '" << full_line << "' on line 1." << endl;
                    return 1;
                }
            }
            else // The rest of the lines are two vertices and the distances between them
            {
                static const size_t npos = -1;
                string delimiter = " ";
                string from, to, dist;
                if (line.find(delimiter) == npos)
                {
                    cerr << "Error: Invalid edge data '" << full_line << "' on line " << line_number << "." << endl;
                    return 1;
                }
                from = line.substr(0, line.find(delimiter));
                // Check if the starting vertex is valid.
                // If the number of vertices is not a number
                if (from.size() != 1)
                {
                    cerr << "Error: Starting vertex '" << from << "' on line " << line_number << " is not among valid values A-" << (char)(num_vertices + 64) << "." << endl;
                    return 1;
                }
                // Verify that the vertex is between A and the the highest possible vertex value.
                if (from[0] < 'A' || from[0] > (char)(num_vertices + 64))
                {
                    cerr << "Error: Starting vertex '" << from << "' on line " << line_number << " is not among valid values A-" << (char)(num_vertices + 64) << "." << endl;
                    return 1;
                }
                line = line.substr(line.find(delimiter) + 1);
                // Verify that there are extra data points on the line.
                if (line.find(delimiter) == npos)
                {
                    cerr << "Error: Invalid edge data '" << full_line << "' on line " << line_number << "." << endl;
                    return 1;
                }
                // Remove the starting vertex from the line.
                to = line.substr(0, line.find(delimiter));

                // Check if the ending vertex is valid.
                // Verify that the vertex is a single character.
                if (to == " " || to.size() != 1)
                {
                    cerr << "Error: Ending vertex '" << to << "' on line " << line_number << " is not among valid values A-" << (char)(num_vertices + 64) << "." << endl;
                    return 1;
                }
                // Verify that the vertex is between A and the the highest possible vertex value.
                if (to[0] < 'A' || to[0] > (char)(num_vertices + 64))
                {
                    cerr << "Error: Ending vertex '" << to << "' on line " << line_number << " is not among valid values A-" << (char)(num_vertices + 64) << "." << endl;
                    return 1;
                }
                // Verify that there are extra data points on the line.
                if (line.find(delimiter) == npos)
                {
                    cerr << "Error: Invalid edge data '" << full_line << "' on line " << line_number << "." << endl;
                    return 1;
                }
                // Remove the ending vertex from the line.
                line = line.substr(line.find(delimiter) + 1);
                dist = line;

                // Check if the distance is valid.
                // Verify that the distance exists.
                if (dist == " " || dist.size() == 0)
                {
                    cerr << "Error: Invalid edge data '" << full_line << "' on line " << line_number << "." << endl;
                    return 1;
                }
                // Verify that the distance is a number.
                try
                {
                    long numeric_distance = stol(dist);
                    if (numeric_distance <= 0)
                    {
                        cerr << "Error: Invalid edge weight '" << dist << "' on line " << line_number << "." << endl;
                        return 1;
                    }
                }
                catch (invalid_argument &e) // If the distance is not a number
                {
                    cerr << "Error: Invalid edge weight '" << dist << "' on line " << line_number << "." << endl;
                    return 1;
                }
                // Add the line to the vector
                values.push_back(full_line);
            }
            line_number++;
        }
        // Don't forget to close the file.
        input_file.close();
    }
    catch (const ifstream::failure &f)
    {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    // Run Floyd's algorithm on the input.
    floyd_algorithm(values, num_vertices);

    return 0;
}