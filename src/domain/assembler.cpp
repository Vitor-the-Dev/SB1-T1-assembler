#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include "../../include/entities/scanner.hpp"
#include "../../include/entities/tokenizator.hpp"
#include "../../include/domain/linker.hpp"
#include "../../include/domain/lexer.hpp"
#include "../../include/entities/readfilelines.hpp"
#include "../../include/domain/assembler.hpp"


using namespace std;


void detectModules(const vector<vector<string>>& tokens, vector<string>& moduleNames) {
        for (const auto& row : tokens) {
            if (row.size() > 1 && row.back() == "EXTERN") {
                moduleNames.push_back(row[0] + ".txt"); // Assuming module filenames are 'LABEL.txt'
            }
        }
    }


vector<vector<string>> Assembler::assemble(const string& mainFile, vector<string>& errors) {
    vector<vector<string>> finalOutput;
    vector<string> moduleNames; // Detected external modules
    vector<vector<vector<string>>> modules; // Tokenized modules

    readFileLines filereader;
    // Step 1: Read and tokenize main input file
    try {
        string mainContent = filereader.readfile(mainFile);
        Tokenizator tokenizer;
        vector<vector<string>> mainTokens = tokenizer.tokenize(mainContent);
        modules.push_back(mainTokens);

        // Detect external modules in the main file
        detectModules(mainTokens, moduleNames);
    } catch (const exception& e) {
        errors.push_back("Error reading or tokenizing main file: " + string(e.what()));
        return {};
    }

    // Step 2: Read and tokenize external modules
    for (const string& moduleName : moduleNames) {
        try {
            string moduleContent = filereader.readfile(moduleName);
            Tokenizator tokenizer;
            modules.push_back(tokenizer.tokenize(moduleContent));
        } catch (const exception& e) {
            errors.push_back("Error reading or tokenizing module '" + moduleName + "': " + string(e.what()));
        }
    }

    // Step 3: Handle case with no external modules
    if (modules.size() == 1) {
        modules.push_back({}); // Add an empty module if none are found
    }

    // Step 4: Link all modules
    Linker linker;
    try {
        // Dynamically link all modules
        finalOutput = modules[0];
        for (size_t i = 1; i < modules.size(); ++i) {
            finalOutput = linker.linker(finalOutput, modules[i]);
        }
    } catch (const exception& e) {
        errors.push_back("Error linking modules: " + string(e.what()));
        return {};
    }

    // Step 5: Generate machine code using Lexer
    Lexer lexer;
    std::vector<std::string> errors; // Error messages array

    try {
        finalOutput = lexer.lexer(finalOutput, errors);

        // Write errors to errorlogs.txt
        if (!errors.empty()) {
            std::ofstream errorFile("errorlogs.txt");
            if (errorFile.is_open()) {
                for (const auto& error : errors) {
                    errorFile << error << std::endl;
                }
                errorFile.close();
            } else {
                std::cerr << "Error: Unable to open errorlogs.txt for writing." << std::endl;
            }
        }
    } catch (const std::exception& e) {
        errors.push_back("Error during final assembly with Lexer: " + std::string(e.what()));
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    return finalOutput;
}


    



