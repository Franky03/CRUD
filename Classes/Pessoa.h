#include <iostream>

class Pessoa {
    private:
        std::string nome;
        int idade;
        std::string cpf;
        std::string telefone;
        
    public:
        Pessoa();
        Pessoa(std::string nome, int idade);
        std::string getNome();
        int getIdade();
        void setNome(std::string nome);
        void setIdade(int idade);
        void setCpf(std::string cpf);
        void setTelefone(std::string telefone);
        std::string getCpf();
        std::string getTelefone();
};