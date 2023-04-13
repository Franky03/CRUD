#include "Pessoa.h"

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
    
    private:
        string codigo;
        string cargo;
        float salario;
};