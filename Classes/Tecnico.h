#include "Funcionario.h"
#include "Equipamento.h"
#include <vector>

using namespace std;

class Tecnico : public Funcionario {
    public:
        Tecnico();
        Tecnico(string nome, int idade, string cpf, string telefone, string codigo, string cargo, float salario, string area);
        
        string getArea();
        void setArea(string area);
        vector<Equipamento> getEquipamentos();
        void addEquipamento(Equipamento equipamento);
        void removeEquipamento(int num_serie);
        vector<string> getMethods();
    
    private:
        string area;
        vector<Equipamento> equipamentos;
};