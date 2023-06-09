#include "Pessoa.h"
#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

using namespace std;

class Funcionario : public Pessoa {
    public:
        Funcionario();
        Funcionario(string nome, int idade, string cpf, string telefone, string codigo, string cargo, float salario);

        string getCodigo();
        void setCodigo(string codigo);
        string getCargo();
        void setCargo(string cargo);
        float getSalario();
        void setSalario(float salario);
        
        double calcularSalarioAnual();
        void aumentarSalario();
        void aumentarSalario(float percentual);
        virtual vector<string> getMethods();
        void trabalhar();
        void descansar();
        int isTrabalhando();
            
    private:
        string codigo;
        string cargo;
        float salario;
        bool funcionarioTrabalhando;
};

#endif