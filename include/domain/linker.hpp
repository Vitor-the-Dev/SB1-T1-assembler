#ifndef LINKER_HPP_INCLUDED
#define LINKER_HPP_INCLUDED
#include <string>
#include <vector>
#include <map>

using namespace std;


/// Classe que representa uma Avaliação com um valor numérico.
/// Responsavel por armazenar, validar e gerenciar um valor associado a avaliação.
class Linker {
    private:
           
        
    public:
        // Read a a file line by line then returns string with all lines appended
        vector<vector<string>> linker(const vector<vector<string>>& moduleA, const vector<vector<string>>& moduleB);

};

/// Implementação inline de getValor.
/// @return O valor armazenado.


#endif 