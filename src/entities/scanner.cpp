#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "../../include/entities/scanner.hpp"

using namespace std;

// This divides lines into tokenized lines, 

// https://www.geeksforgeeks.org/how-to-split-string-into-an-array-in-cpp/ modified

vector<string>  Scanner::splitString(const string& input, char delimiter) {
    vector<string> tokens;
    istringstream stream(input);
    string token;

    while (getline(stream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}


    // Tokenizes the input into lines and then further into tokens
    vector<vector<string>>  Scanner::scanner(const string& input) {
        char delimiterLine = '\n';
        char delimiterSpace = ' ';

        vector<vector<string>> allTokens; // 2D vector to store results

        
        vector<string> lines = splitString(input, delimiterLine); // Dividines into lines

        
        for (const string& line : lines) { // Divides lines into tokens
            vector<string> tokens = splitString(line, delimiterSpace);
            allTokens.push_back(tokens); // Add this line's tokens to the result
        }

        return allTokens;
    }

// return tokens