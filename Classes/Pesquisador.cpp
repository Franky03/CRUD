#include "Pesquisador.h"

Pesquisador::Pesquisador() : Pesquisador("", 0, "", "", "", "Pesquisador", 0, ""){}

Pesquisador::Pesquisador(string nome, int idade, string cpf, string telefone,  string codigo, string cargo, float salario, string area="Pesquisa")
: Funcionario(nome, idade, cpf, telefone, codigo, cargo, salario){
    setArea(area);
}

string Pesquisador::getArea(){
    return area;
}

void Pesquisador::setArea(string area){
    this->area = area;
}

void Pesquisador::addProjeto(Projeto projeto){
    projetos.push_back(projeto);
}

void Pesquisador::removeProjeto(string nome){
    for(int i; i<projetos.size(); i++){
        if(projetos[i].getNome() == nome){
            projetos.erase(projetos.begin() + i);
            projetos.shrink_to_fit();
        }
    }
}

vector<Projeto> Pesquisador::getProjetos(){
    return projetos;
}

vector<string> Pesquisador::getMethods()
{
    return {"Area","Projetos", "AddProjeto", "RemoveProjeto"};
}