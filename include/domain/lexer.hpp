#ifndef LEXER_HPP_INCLUDED
#define LEXER_HPP_INCLUDED
#include <string>
#include <vector>
#include <map>

using namespace std;


/// Classe que representa uma Avaliação com um valor numérico.
/// Responsavel por armazenar, validar e gerenciar um valor associado a avaliação.
class Lexer {
    private:
           
        
    public:
        // Read a a file line by line then returns string with all lines appended
        vector<vector<string>> lexer(const vector<vector<string>>& finalOutput, vector<string>& errors);

};

/// Implementação inline de getValor.
/// @return O valor armazenado.


#endif 