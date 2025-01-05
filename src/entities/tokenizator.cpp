#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include "../../include/entities/scanner.hpp"
#include "../../include/entities/tokenizator.hpp"

using namespace std;

bool contains(const vector<string>& row, const string& word) {
    return find(row.begin(), row.end(), word) != row.end();
}

string toUpperCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

void processMacros(vector<vector<string>>& tokens){
    unordered_map<string, vector<string>> macros; // Macro storage
    vector<vector<string>> result;               // Processed data
    bool inMacro = false;
    string currentMacro;
    vector<string> macroContent;

    // Step 1: Parse and store macros
    for (const auto& row : tokens) {
        if (!row.empty()) {
            if (row.back() == "startmacro") {
                inMacro = true;
                currentMacro = row[1];
                macroContent.clear();
            } else if (row.back() == "endmacro") {
                inMacro = false;
                macros[currentMacro] = macroContent;
            } else if (inMacro) {
                macroContent.insert(macroContent.end(), row.begin(), row.end());
            } else {
                result.push_back(row);
            }
        }
    }

    // Step 2: Flatten all macros
    for (auto& [macroName, macroContent] : macros) {
        vector<string> expanded;
        for (const auto& word : macroContent) {
            if (macros.find(word) != macros.end()) {
                expanded.insert(expanded.end(), macros[word].begin(), macros[word].end());
            } else {
                expanded.push_back(word);
            }
        }
        macroContent = expanded;
    }

     // Step 3: Replace macros in rows
    for (auto& row : result) {
        vector<string> expandedRow;
        for (const auto& word : row) {
            if (macros.find(word) != macros.end()) {
                expandedRow.insert(expandedRow.end(), macros[word].begin(), macros[word].end());
            } else {
                expandedRow.push_back(word);
            }
        }
        row = expandedRow;
    }

}

void preProcess(vector<vector<string>>& tokens) {
    // sets vectors for data, text 


    // data and text
    vector<vector<string>> text;
    vector<vector<string>> data;


    // Unified output
    vector<vector<string>> finalOut;

    // Determine the current mode
    string currentMode = "TEXT";
    int semicolonIndex;

    for (size_t i = 0; i < tokens.size(); ++i) {
        auto row = tokens[i]; // Copy the row to modify it

        if (row.empty()) continue;

        // Check the first word of the row for "Potatoe" or "Apple"
        if (contains(row, "DATA")) {
            currentMode = "DATA";
        } else if (contains(row, "TEXT")) {
            currentMode = "TEXT";
        }

        for (auto& word : row) {
            word = toUpperCase(word);
        }
        

        // removes comments

        for (size_t j = 0; j < row.size(); ++j) {
            if (row[j] == ";") {
                semicolonIndex = j;
                break;
            }
        }

        // Remove all elements after and including ';' in the current row
        if (semicolonIndex != row.size()) {
            row.erase(row.begin() + semicolonIndex, row.end());
        }

        // adds it all into respective table
        if (currentMode == "DATA") {
            data.push_back(row);
        } else if (currentMode == "TEXT") {
            text.push_back(row);
        }
    

    finalOut = text; // Start with text
    finalOut.insert(finalOut.end(), data.begin(), data.end()); // Append data to the end
    
    tokens = finalOut;
    }


}



        vector<vector<string>> Tokenizator::tokenize(const string& input) {
            Scanner scanner;

            vector<vector<string>> tokens = scanner.scanner(input);
        
            // Pre-process the tokens, including macros
            processMacros(tokens); // Expand macros before processing

            // pre processes the tokens
            preProcess(tokens);

            return tokens;
        }
    
