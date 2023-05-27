#include <iostream>
#include <sstream>
#include <string>

//Struct date para trabalhar com as datas corretamente
struct Date{
public:
    int dia;
    int mes;
    int ano;

    void toDate(std::string s){
        std::string dia, mes ,ano;
        std::stringstream date;
        date << s;
        getline(date, mes,'/');
        getline(date, dia,'/');
        getline(date, ano);

        this->mes = stoi(mes);
        this->dia = stoi(dia);
        this->ano = stoi(ano);

    };

    std::string toStr(){
        std::stringstream date;
        date << dia;
        date<< '/';
        date<< mes;
        date<< '/';
        date<< ano;

        return date.str();
    };

    bool operator<(Date const& other){
        if(this->ano < other.ano){
            return true;
        }else if(this->ano > other.ano){
            return false;
        }else{
            if(this->mes < other.mes){
                return true;
            }else if(this->mes > other.mes){
                return false;
            }else{
                if(this->dia < other.dia){
                    return true;
                }else{
                    return false;
                }
            }
        }
    }
//10/03/2003 > 10/02/2003
    bool operator>(Date const& other){
        if(this->ano > other.ano){
            return true;
        }else if(this->ano < other.ano){
            return false;
        }else{
            if(this->mes > other.mes){
                return true;
            }else if(this->mes < other.mes){
                return false;
            }else{
                if(this->dia > other.dia){
                    return true;
                }else{
                    return false;
                }
            }
        }
    }

    bool operator>=(Date const& other){
        return !(*this<other);
    }

    bool operator<=(Date const& other){
        return !(*this>other);;
    }

    
    bool operator==(Date const& other){
        if(this->ano == other.ano && this->mes == other.mes && this->dia == other.dia){
            return true;
        }else{
            return false;
        }
    }
};

class Pessoa{
private:
    unsigned long long int cpf = 0;
    std::string nome;
    std::string sobrenome;
    Date nascimento;
    std::string cidade;

public:
    Pessoa() = default;
    Pessoa(unsigned long long int cpf, std::string nome,std::string sobrenome,std::string nascimento,std::string cidade){
        this->cpf = cpf;
        this->nome = nome;
        this->sobrenome = sobrenome;
        this->nascimento.toDate(nascimento);
        this->cidade = cidade;
    }
    friend std::ostream& operator<<(std::ostream& os, const Pessoa& p);



    unsigned long long int getCpf(){
        return this->cpf;
    }


    void setCpf(unsigned long long int cpf){
        this->cpf = cpf;
    }


    std::string getNome(){
        return this->nome;
    }


    void setNome(std::string nome){
        this->nome = nome;
    }


    std::string getSobrenome(){
        return this->sobrenome;
    }


    void setSobrenome(std::string sobrenome){
        this->sobrenome = sobrenome;
    }


    Date getNascimento(){
        return this->nascimento;
    }


    void setNascimento(std::string nascimento){
        this->nascimento.toDate(nascimento);
    }


    std::string getCidade(){
        return this->cidade;
    }


    void setCidade(std::string cidade){
        this->cidade = cidade;
    }

    void show(){
        std::cout << "Cpf: " << getCpf() << std::endl;
        std::cout << "Nome: " << getNome() << std::endl;
        std::cout << "Sobrenome: " << getSobrenome() << std::endl;
        std::cout << "Data nasimento: " << nascimento.toStr() << std::endl;
        std::cout << "Cidade: " << getCidade() << std::endl;
    }
};
