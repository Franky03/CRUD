#include <iostream>

template <class T>

class Relatorio {
    public:
        float getSalarioTotal(vector<T> vec){
            float total = 0;
            for (int i = 0; i < vec.size(); i++){
                total += vec[i].getSalario();
            }
            return total;
        };

        void diaDeFolga(vector<T> vec){
            for (int i = 0; i < vec.size(); i++){
                vec[i].descansar();
            }
        };

        void diaDeTrabalho(vector<T> vec){
            for (int i = 0; i < vec.size(); i++){
                vec[i].trabalhar();
            }
        };

        void aumentarSalario(vector<T> vec, float percentual){
            for (int i = 0; i < vec.size(); i++){
                vec[i].aumentarSalario(percentual);
            }
        };

        void toFile(vector<T> objetos, ofstream &arquivo, string classe, float *totalSalario){
            arquivo << classe << endl;
            arquivo << "------------------------" << endl;
            arquivo << "Total: " << objetos.size() << endl;
            
            float salarioTotal = 0;

            for(int i = 0; i < objetos.size(); i++){
                salarioTotal += objetos[i].getSalario();
            }

            arquivo << "Total Gasto por Ano: R$ " << salarioTotal*12 << endl;
            arquivo << "Total Gasto por Mês: R$ " << salarioTotal << endl;

            *totalSalario += salarioTotal;

            arquivo << "------------------------" << endl;
        }
};
