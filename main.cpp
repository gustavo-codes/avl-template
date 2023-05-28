#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cctype>
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

//Função de busca por cpf
void cpfSearch(avl_tree<unsigned long long int,Pessoa> &tree, string cpf){
    vector<Node<unsigned long long int,Pessoa>*>aux = tree.search(cpfFormat(cpf),cpfFormat(cpf));
    if(aux.size()==0){
        cout << "Pessoa não encontrada" << endl;
    }else{
            cout << "----------------- Pessoa -----------------" << endl;
            aux[0]->data->show();
            cout << "------------------------------------------" << endl;
    }
    
}

//Função de busca por primeiro nome
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

//Função de busca por data de nascimento
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

//Padroniza a string para o padrão correto ex: GUSTAVO -> Gustavo
string normalizeName(string &name){
    stringstream ss;
    if(name.empty()){
        return "";
    }
    if(islower(name[0])){
        ss << (char)toupper(name[0]);
    }else{
        ss << name[0];
    }
    if(name.size()>0){
        for(int i = 1; i<(int)name.size();i++){
            if(isupper(name[i])){
                ss << (char)tolower(name[i]);
            }else{
                ss << name[i];
            }
            
        }
    }

    return ss.str();
}

//Checa se a data passada contém algum caractere além dos aceitados 0..9 e '/'
bool dataCheck(string s){
    Date d;
    int barCount = 0;
    for(int i = 0;i<(int)s.size();i++){
        if(s[i]=='/'){
            barCount++;
        }
        if(s[i]>(char)57||s[i]<(char)47){
            cout << "Data inválida" << endl;
            return false;
        }
    }
    if(barCount!=2){
        cout << "O formato da data precisa estar separado por exatamente duas /(barra)" << endl;
        return false;
    }
    d.brToDate(s);
    if(d.dia<0 || d.dia>31){
        cout << "Digitar um dia valido" << endl;
        return false;
    }
    if(d.mes<1 || d.mes>12 ){
        cout << "Digitar um mes valido" << endl;
        return false;
    }
    return true;
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
    
    //Criação das árvores de ponteiros.
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

    //Menu com switch 
    unsigned int op = 9;
    string operation;
    while(op!=0){
        string temp;
        string temp2;
        cout << "--------------- Arvore AVL ---------------" << endl;
        cout << "1 - Buscar pessoa por CPF" << endl;
        cout << "2 - Buscar pessoa por Nome" << endl;
        cout << "3 - Buscar pessoa por Data de nascimento" << endl;
        cout << "0 - Sair do programa" << endl;
        cin >> operation;

        if(isdigit(operation[0])){
            op = stoi(operation);
            switch (op)
            {
            case 0:
                cout << "Saindo do programa..." << endl;
                cout << "Desalocando memoria..." << endl;
                break;
            case 1:
                cout << "Digite o CPF no formato xxx.xxx.xxx-xx: ";
                cin >> temp;
                cpfSearch(tree_cpf,temp);
                break;
            case 2:
                cout << "Digite o primeiro nome: ";
                cin >> temp;
                temp = normalizeName(temp);
                nameSearch(tree_name,temp);
                break;
            case 3:
                cout << "Deseja pesquisar por pessoas de DD/MM/AAAA: ";
                cin >> temp;
                cout << "de " << temp << " ate DD/MM/AAAA: " ;
                cin >> temp2;
                Date min;
                Date max;

                if(dataCheck(temp)&&dataCheck(temp2)){
                    min.brToDate(temp);
                    max.brToDate(temp2);

                    if(min>max){
                        cout << "Digite um intervalo de tempo valido" << endl;
                    }else{
                        dateSearch(tree_date,min,max);
                    }
                }
                break;
                
            default:
                cout << "Selecione uma opcao valida" << endl;
                break;
            }            
        }else{
            cout << "Selecione uma opcao valida" << endl;
            operation.clear();
        }
        

    }
    
    tree_cpf.clear();
    tree_name.clear();
    tree_date.clear();
    
    people.close();

}
