#include "Funcionario.h"
#include "Equipamento.h"
#include <vector>


class Tecnico : public Funcionario {
    private:
        std::string area;
        std::vector<Equipamento> equipamentos;
    public:
        Tecnico(std::string nome, int idade, std::string codigo, std::string cargo, float salario, std::string area);
        std::string getArea();
        void setArea(std::string area);
        std::vector<Equipamento> getEquipamentos();
        void addEquipamento(Equipamento equipamento);
        void removeEquipamento(std::string nome);
};