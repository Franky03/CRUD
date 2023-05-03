#include "Funcionario.h"

Funcionario::Funcionario() : Funcionario("", 0, "", "", "", "", 0.0){}

Funcionario::Funcionario(string nome, int idade, string cpf, string telefone, string codigo, string cargo, float salario)
: Pessoa(nome, idade, cpf, telefone){
    this->funcionarioTrabalhando = false;
    setCodigo(codigo);
    setCargo(cargo);
    setSalario(salario);
}

string Funcionario::getCodigo(){
    return codigo;
}

void Funcionario::setCodigo(string codigo){
    this->codigo = codigo;
}

string Funcionario::getCargo(){
    return cargo;
}

void Funcionario::setCargo(string cargo){
    this->cargo = cargo;
}

float Funcionario::getSalario(){
    return salario;
}

void Funcionario::setSalario(float salario){
    this->salario = salario;
}

double Funcionario::calcularSalarioAnual(){
    return this->salario * 12;
}

vector<string> Funcionario::getMethods(){
    return {"SalarioAnual", "Trabalhar", "Descansar", "Trabalhando?", "AumentarSalario"};
}

void Funcionario::trabalhar(){
    this->funcionarioTrabalhando = true;
}

void Funcionario::descansar(){
    this->funcionarioTrabalhando = false;
}

string Funcionario::isTrabalhando(){
    return this->funcionarioTrabalhando ? "Sim" : "Não";
}

void Funcionario::aumentarSalario(){
    float percentual;
    cout << "Digite o percentual de aumento: ";
    cin >> percentual;
    this->salario += this->salario * (percentual);
}

void Funcionario::aumentarSalario(float percentual){
    this->salario += this->salario * (percentual);
}