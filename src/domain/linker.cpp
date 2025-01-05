#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include "../../include/domain/linker.hpp"

using namespace std;

// Linker implementation
vector<vector<string>> Linker::linker(const vector<vector<string>>& moduleA, const vector<vector<string>>& moduleB) {
    // Segments
    vector<vector<string>> finalExecutable;      // Final output
    vector<vector<string>> textSegment;          // Final text segment
    vector<vector<string>> dataSegment;          // Final data segment

    // Address offset trackers
    int textOffset = 0;  // Offset for text instructions
    int dataOffset = 0;  // Offset for data segment
    int currentAddress = 0; // Current address (incremented by 2 for each entry)

    // Table of symbol definitions
    unordered_map<string, int> globalSymbolTable;

    // Helper to process a module
    auto processModule = [&](const vector<vector<string>>& module) {
        for (const auto& line : module) {
            if (line.empty()) continue;

            if (line[0].back() == ':') { // Symbol definition
                string symbol = line[0].substr(0, line[0].size() - 1); // Remove the ':' from label
                if (line.size() == 1) { // Label in the text segment
                    globalSymbolTable[symbol] = textOffset * 2;
                } else if (line[1] == "CONST" || line[1] == "SPACE") { // Symbol in the data segment
                    globalSymbolTable[symbol] = currentAddress;
                    vector<string> dataEntry = {to_string(currentAddress)}; // Add address to the data entry
                    dataEntry.insert(dataEntry.end(), line.begin(), line.end());
                    dataSegment.push_back(dataEntry);

                    if (line[1] == "SPACE") {
                        dataOffset += stoi(line[2]); // Reserve multiple addresses
                    } else { // CONST
                        dataOffset++;
                    }
                    currentAddress += 2; // Increment address
                }
            } else if (line[0] == "BEGIN") { 
                continue; // Skip BEGIN line
            } else { // Regular instruction
                vector<string> instructionEntry = {to_string(currentAddress)}; // Add address to instruction
                instructionEntry.insert(instructionEntry.end(), line.begin(), line.end());
                textSegment.push_back(instructionEntry);

                textOffset++;
                currentAddress += 2; // Increment address
            }
        }
    };

    // Process modules
    processModule(moduleA);
    processModule(moduleB);

    // Replace external references with actual addresses in the text segment
    for (auto& line : textSegment) {
        for (auto& token : line) {
            if (globalSymbolTable.find(token) != globalSymbolTable.end()) {
                token = to_string(globalSymbolTable[token]); // Replace with correct address
            }
        }
    }

    // Combine text and data segments into the final executable
    finalExecutable.insert(finalExecutable.end(), textSegment.begin(), textSegment.end());
    finalExecutable.insert(finalExecutable.end(), dataSegment.begin(), dataSegment.end());

    return finalExecutable;
}

