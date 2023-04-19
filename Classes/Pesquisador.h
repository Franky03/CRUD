#include "Funcionario.h"
#include "Projetos.h"

using namespace std;

class Pesquisador : public Funcionario {
    public:
        Pesquisador();
        Pesquisador(string nome, int idade, string cpf, string telefone,  string codigo, string cargo, float salario, string area);

        string getArea();
        void setArea(string area);
        void addProjeto(Projeto projeto);
        void removeProjeto(string titulo);
        vector<Projeto> getProjetos();
        vector<string> getMethods();

    private:
        string area;
        vector<Projeto> projetos;
};