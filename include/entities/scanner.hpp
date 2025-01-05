#ifndef SCANNER_HPP_INCLUDED
#define SCANNER_HPP_INCLUDED
#include <string>
#include <vector>

using namespace std;


/// Classe que representa uma Avaliação com um valor numérico.
/// Responsavel por armazenar, validar e gerenciar um valor associado a avaliação.
class Scanner {
    private:
           
        vector<string> splitString(const string& input, char delimiter);
    public:
        /// Atribui um valor inteiro a avaliacao após valida-lo.
        vector<vector<string>> scanner(const string& input);

};

/// Implementação inline de getValor.
/// @return O valor armazenado.


#endif 