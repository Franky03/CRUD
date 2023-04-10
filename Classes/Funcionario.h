#include "Pessoa.h"

class Funcionario : public Pessoa {
    private:
        std::string codigo;
        std::string cargo;
        float salario;
    public:
        Funcionario(std::string nome, int idade, std::string codigo, std::string cargo, float salario);
        std::string getCodigo();
        std::string getCargo();
        float getSalario();
        void setCodigo(std::string codigo);
        void setCargo(std::string cargo);
        void setSalario(float salario);
};