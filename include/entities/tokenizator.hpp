#ifndef TOKENIZER_HPP_INCLUDED
#define TOKENIZER_HPP_INCLUDED
#include <string>
#include <vector>

using namespace std;


/// Classe que representa uma Avaliação com um valor numérico.
/// Responsavel por armazenar, validar e gerenciar um valor associado a avaliação.
class Tokenizator {
    private:
            /// Valida valor para 
            /// @param valor O valor a ser validado.
            
            //void tokenize(string&); //Metodo para transformar em token
    public:
            /// Atribui um valor inteiro a avaliacao após valida-lo.
            vector<vector<string>> tokenize(const string& input);
};

/// Implementação inline de getValor.
/// @return O valor armazenado.


#endif // AVALIACAO_HPP_INCLUDED
