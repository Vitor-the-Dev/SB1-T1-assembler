#include <iostream>
#include <string>
#include <vector>
#include "Assembler.hpp" 

using namespace std;

// Note: Montador means assembler in portuguese, this was done as per specifications of TP1

int main(int argc, char* argv[]) {
    string mainFile = argv[1];
    Assembler assembler;
    vector<string> errors;

    if (argc != 2) {
        cerr << "Usage: ./montador <mainFile>" << endl;
        return 1; // Exit with error code
    }

    vector<vector<string>> finalOutput = assembler.assemble(mainFile, errors);

    
    cout << "Assembly complete. Output:" << endl;
    for (const auto& row : finalOutput) {
        for (const auto& col : row) {
            cout << col << " ";
        }
        cout << endl;
    }

    
    if (!errors.empty()) {
        cout << "Errors encountered during assembly:" << endl;
        for (const auto& error : errors) {
            cout << error << endl;
        }
        return 1;
    }

    return 0; 
}
