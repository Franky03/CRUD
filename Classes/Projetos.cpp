#include "Projetos.h"

Projeto::Projeto() : Projeto("", "", 0){}

Projeto::Projeto(string nome, string descricao, int duracao){
    setNome(nome);
    setDescricao(descricao);
    setDuracao(duracao);
}

string Projeto::getNome(){
    return nome;
}

string Projeto::getDescricao(){
    return descricao;
}

int Projeto::getDuracao(){
    return duracao;
}

void Projeto::setNome(string nome){
    this->nome = nome;
}

void Projeto::setDescricao(string descricao){
    this->descricao = descricao;
}

void Projeto::setDuracao(int duracao){
    this->duracao = duracao;
}