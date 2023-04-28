#include "Tecnico.h"

Tecnico::Tecnico() : Tecnico("", 0, "", "", "", "", 0.0, ""){}

Tecnico::Tecnico(string nome, int idade, string cpf, string telefone, string codigo, string cargo, float salario, string area)
: Funcionario(nome, idade, cpf, telefone, codigo, cargo, salario){
    setArea(area);
}

string Tecnico::getArea(){
    return area;
}

void Tecnico::setArea(string area){
    this->area = area;
}

vector<Equipamento> Tecnico::getEquipamentos(){
    return equipamentos;
}

void Tecnico::addEquipamento(Equipamento equipamento){
    equipamentos.push_back(equipamento);
}

void Tecnico::removeEquipamento(int num_serie){
    for(int i; i<equipamentos.size(); i++){
        if(equipamentos[i].getNumSerie() == num_serie){
            equipamentos.erase(equipamentos.begin() + i);
            equipamentos.shrink_to_fit();
        }
    }
}

vector<string> Tecnico::getMethods()
{
    return {"Area", "Equipamentos", "AddEquipamento", "RemoveEquipamento"};
}