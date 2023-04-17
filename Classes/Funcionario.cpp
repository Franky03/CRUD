#include "Funcionario.h"

Funcionario::Funcionario() : Funcionario("", 0, "", "", "", "", 0.0){}

Funcionario::Funcionario(string nome, int idade, string cpf, string telefone, string codigo, string cargo, float salario)
: Pessoa(nome, idade, cpf, telefone){}

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

double Funcionario::calcularSalarioAnual()
{
    return this->salario * 12;
}

void Funcionario::trabalhar()
{
    this->funcionarioTrabalhando = true;
}

void Funcionario::descansar()
{
    this->funcionarioTrabalhando = false;
}

