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

void cpfSearch(avl_tree<unsigned long long int,Pessoa> &tree, string cpf){
    vector<Node<unsigned long long int,Pessoa>*>aux = tree.search(cpfFormat(cpf),cpfFormat(cpf));
    if(aux.size()==0){
        cout << "Pessoa não encontrada" << endl;
    }else{
        aux[0]->data->show();
    }
    
}

void nameSearch(avl_tree<string,Pessoa> &tree, string nome){
    vector<Node<string,Pessoa>*>aux = tree.search(nome,nome);
    if(aux.size()==0){
        cout << "Pessoa não encontrada" << endl;
    }else{   
        for(int i = 0; i< (int)aux.size();i++){
            cout << "---------------- Pessoa " << i+1 << " ----------------" << endl;
            aux[i]->data->show();
            cout << "------------------------------------------" << endl;
        }
    }
}

void dateSearch(avl_tree<Date,Pessoa> &tree, Date dataMin, Date dataMax){
    vector<Node<Date,Pessoa>*>aux = tree.search(dataMin,dataMax);
    if(aux.size()==0){
        cout << "Pessoa não encontrada" << endl;
    }else{   
        for(int i = 0; i< (int)aux.size();i++){
            cout << "---------------- Pessoa " << i+1 << " ----------------" << endl;
            aux[i]->data->show();
            cout << "------------------------------------------" << endl;
        }
    }
}


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
    avl_tree<string, Pessoa> tree_name;
    avl_tree<Date, Pessoa> tree_date;

    for(int i = 0; i<(int)lista.size();i++){
        Pessoa* aux = &lista[i];
        tree_cpf.add(lista[i].getCpf(),aux);
    }
    for(int i = 0; i<(int)lista.size();i++){
        Pessoa* aux = &lista[i];
        tree_name.add(lista[i].getNome(),aux);
    }
    for(int i = 0; i<(int)lista.size();i++){
        Pessoa* aux = &lista[i];
        tree_date.add(lista[i].getNascimento(),aux);
    }

    unsigned int op = 9;
    while(op!=0){
        string temp;
        string temp2;
        cout << "-------------------- Arvore AVL --------------------" << endl;
        cout << "1 - Buscar pessoa por CPF" << endl;
        cout << "2 - Buscar pessoa por Nome" << endl;
        cout << "3 - Buscar pessoa por Data de nascimento" << endl;
        cout << "0 - Sair do programa" << endl;
        cin >> op;

        switch (op)
        {
        case 1:
            cout << "Digite o CPF no formato xxx.xxx.xxx-xx: ";
            cin >> temp;
            cpfSearch(tree_cpf,temp);
            break;
        case 2:
            cout << "Digite o primeiro nome: ";
            cin >> temp;
            nameSearch(tree_name,temp);
            break;
        case 3:
            cout << "Deseja pesquisar por pessoas de MM/DD/AAAA: ";
            cin >> temp;
            cout << "de " << temp << " ate MM/DD/AAAA: " ;
            cin >> temp2;
            Date min;
            Date max;
            Date test;

            min.toDate(temp);
            max.toDate(temp2);

            if(min>max){
                cout << "Digite um intervalo de tempo válido" << endl;
            }else{
                dateSearch(tree_date,min,max);
            }
            
        default:
            break;
        }
    }
    

    
    people.close();

}
