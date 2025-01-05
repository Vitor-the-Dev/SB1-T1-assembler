#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <map>
#include "../../include/domain/lexer.hpp"


unordered_map<string, string> opcodes = {
    {"ADD", "01"}, {"SUB", "02"}, {"MUL", "03"}, {"DIV", "04"},
    {"JMP", "05"}, {"JMPN", "06"}, {"JMPP", "07"}, {"JMPZ", "08"},
    {"COPY", "09"}, {"LOAD", "10"}, {"STORE", "11"}, {"INPUT", "12"},
    {"OUTPUT", "13"}, {"STOP", "14"}
};


string toHex(const string& str) {
    stringstream ss;
    try {
        int value = stoi(str);
        ss << hex << uppercase << value;
    } catch (...) {
        return "00"; // Default for invalid numbers
    }
    return ss.str();
}

bool isValidLabel(const string& label) {
    if (label.empty() || (!isalpha(label[0]) && label[0] != '_')) return false;
    return all_of(label.begin() + 1, label.end(), [](char c) {
        return isalnum(c) || c == '_';
    });
}


    vector<vector<string>> Lexer::lexer(const vector<vector<string>>& finalOutput, vector<string>& errors) {
        vector<vector<string>> machineCode;
        unordered_map<string, int> labelAddresses;
        unordered_map<string, int> labelDefinitions;
        int currentAddress = 0;

        // First pass: Collect labels and detect redefined or invalid labels
        for (const auto& row : finalOutput) {
            if (row.empty()) continue;

            if (row[0].back() == ':') { // Label definition
                string label = row[0].substr(0, row[0].size() - 1);
                if (!isValidLabel(label)) {
                    errors.push_back("Lexical error in label '" + label + "' at address " + to_string(currentAddress));
                }
                if (labelDefinitions.count(label)) {
                    errors.push_back("Redefined label '" + label + "' at address " + to_string(currentAddress));
                } else {
                    labelDefinitions[label] = currentAddress;
                }
            }
            currentAddress += 2;
        }

        // Second pass: Process instructions
        currentAddress = 0;
        for (const auto& row : finalOutput) {
            if (row.empty()) continue;

            vector<string> processedRow;

            // Check for duplicate labels in the same row
            int labelCount = count_if(row.begin(), row.end(), [](const string& word) {
                return word.back() == ':';
            });
            if (labelCount > 1) {
                errors.push_back("Duplicated label in row at address " + to_string(currentAddress));
            }

            // Process each word in the row
            bool hasInstruction = false;
            for (size_t i = 0; i < row.size(); ++i) {
                const string& word = row[i];

                if (word.back() == ':') continue; // Skip label definitions

                if (opcodes.find(word) != opcodes.end()) { // Valid opcode
                    processedRow.push_back(opcodes[word]);
                    hasInstruction = true;
                } else if (labelDefinitions.find(word) != labelDefinitions.end()) { // Label reference
                    processedRow.push_back(toHex(to_string(labelDefinitions[word])));
                } else if (isdigit(word[0]) || (word[0] == '-' && isdigit(word[1]))) { // Literal number
                    processedRow.push_back(toHex(word));
                } else if (word == "CONST") { // Constant definition
                    processedRow.push_back(toHex(row[++i]));
                    hasInstruction = true;
                } else if (word == "SPACE") { // Space directive
                    if (i + 1 < row.size() && isdigit(row[i + 1][0])) {
                        int count = stoi(row[++i]);
                        for (int j = 0; j < count; ++j) {
                            processedRow.push_back("00");
                        }
                    } else {
                        processedRow.push_back("00");
                    }
                    hasInstruction = true;
                } else { // Unknown word
                    errors.push_back("Missing label or invalid instruction '" + word + "' at address " + to_string(currentAddress));
                }
            }

            if (!hasInstruction) {
                errors.push_back("Missing instruction at address " + to_string(currentAddress));
            }

            machineCode.push_back(processedRow);
            currentAddress += 2;
        }

        return machineCode;
    }