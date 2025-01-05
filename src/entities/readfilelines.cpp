// From https://www.geeksforgeeks.org/read-a-file-line-by-line-in-cpp/

// C++ Program to Read a file line by line using getline
#include <fstream>
#include <iostream>
#include <string>

#include "../../include/entities/readfilelines.hpp"

using namespace std;


    string readFileLines::readfile(const string& filename) {
    // Create an input file stream object named 'file' and
    // open the file "GFG.txt".
        ifstream file(filename);

        // String to store each line of the file.
        string line;
        string output;

        if (file.is_open()) {
            // Read each line from the file and store it in the
            // 'line' variable.
            while (getline(file, line)) {
                output += line + "\n";
            }

            // Close the file stream once all lines have been
            // read.
            file.close();
        }
        else {
            // Print an error message to the standard error
            // stream if the file cannot be opened.
            cerr << "Unable to open file!" << endl;
        }
        return line;
    }
    
