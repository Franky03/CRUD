#include <iostream>
#ifndef PESSOA_H
#define PESSOA_H

using namespace std;

class Pessoa {
    public:
        Pessoa();
        Pessoa(string nome, int idade, string cpf, string telefone);

        string getNome();
        void setNome(string nome);
        int getIdade();
        void setIdade(int idade);
        string getCpf();
        void setCpf(string cpf);
        string getTelefone();
        void setTelefone(string telefone);

    private:
        string nome;
        int idade;
        string cpf;
        string telefone;
};

#endif