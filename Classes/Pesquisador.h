#include "Funcionario.h"
#include "Projetos.h"
#include <vector>

using namespace std;

class Pesquisador : public Funcionario {
    public:
        Pesquisador(string nome, int idade, string codigo, string cargo, float salario, string area, string orientador);

        string getArea();
        void setArea(string area);
        void addProjeto(Projeto projeto);
        void removeProjeto(string nome);
        vector<Projeto> getProjetos();

    private:
        string area;
        vector<Projeto> projetos;
};