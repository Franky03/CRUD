#include "Funcionario.h"
#include "Projetos.h"
#include <vector>

class Pesquisador : public Funcionario {
    private:
        std::string area;
        std::vector<Projeto> projetos;
    public:
        Pesquisador(std::string nome, int idade, std::string codigo, std::string cargo, float salario, std::string area, std::string orientador);
        std::string getArea();
        void setArea(std::string area);
        void addProjeto(Projeto projeto);
        void removeProjeto(std::string nome);
        vector<Projeto> getProjetos();
       
};