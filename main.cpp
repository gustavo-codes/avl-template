#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Pessoa.h"
#include "avl.h"

using namespace std;

//Sobrecarga do operador << para funcinar com tipo pessoa
std::ostream& operator<<(std::ostream& os, Pessoa& p)
{
    p.show();
    return os;
}
//Função que recebe cpf em formato de string e retorna o cpf em formato de um ull 
unsigned long long int cpfFormat(string init){
    stringstream final;
    int size = init.size();
    for(int i = 0; i < size; i++){
        if(init[i]!='.' && init[i]!='-'){
            final << init[i];
        }
    }

    return strtoll(final.str().c_str(),NULL, 10);
};

/*
int dataFormat(string init){
    stringstream final;
    int size = init.size();
    for(int i = 0; i < size; i++){
        if(init[i]!='/'){
            final << init[i];
        }
    }

    return stoi(final.str());
};
*/

int main(){
    system("chcp 65001 > nul");

    //Parte de leitura do arquivo
    string path = "data.csv";
    ifstream people;
    vector<Pessoa> lista;
    string line = "";

    people.open(path);

    if(people.fail()){
        cerr << "Error: file or path dont exist or is not csv type -> "<< path << endl;
    }

    //Limpar o cabeçalho do arquivo csv
    getline(people,line);
    line = "";

//Insere todas as pessoas no vector lista
    while(getline(people, line)){
        unsigned long long int cpf;
        string nome;
        string sobrenome;
        string nascimento;
        string cidade;
        string temp;
        string temp2;
    
        stringstream tempLine(line);

        getline(tempLine, temp, ',');
        cpf = cpfFormat(temp);
        getline(tempLine, nome,',');
        getline(tempLine, sobrenome,',');
        getline(tempLine, nascimento,',');
        getline(tempLine, cidade,',');
        
        Pessoa aux(cpf, nome, sobrenome, nascimento,cidade);
        lista.push_back(aux);
        line = "";

        
    }
    
    avl_tree<unsigned long long int, Pessoa> tree_cpf;

    for(int i = 0; i<(int)lista.size();i++){
        Pessoa* aux = &lista[i];
        tree_cpf.add(lista[i].getCpf(),aux);
    }

    //Protótipo da função pesquisar por cpf
    Node<unsigned long long int,Pessoa> *aux = tree_cpf.search(cpfFormat("313.955.318-89"));
    cout << *aux->data << endl;


    people.close();

}
