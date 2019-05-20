#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Client{
    string id;
    int docs;
    int pac;

    Client(string id, int docs, int pac){
        this->id = id;
        this->docs = docs;
        this->pac = pac;
    }
};

struct Banco{
    vector<Client*> caixas;
    list<Client*> fila_entrada;
    queue<Client*> fila_saida;

    void show_bank(){
        //mostra vector de caixas
        for(int i = 0; i < this->caixas.size(); i++){
            if(this->caixas[i] != NULL){
                cout << "[" << this->caixas[i]->id << ":" << this->caixas[i]->docs << ":" << this->caixas[i]->pac << "]";
            }else{
                cout << "[]";
            }
        }
        cout << endl;
        cout << "in :{ ";
        auto it = this->fila_entrada.begin();
        for(it != this->fila_entrada.end(); ++it){
            cout << (*it)->id << ":" << (*it)->docs << ":" << (*it)->pac;
        }
        cout << " }" << endl;
        
        cout << "out :{ ";
        while(!this->fila_saida.empty()){
            cout << this->fila_saida.front()->id << ":" << this->fila_saida.front()->docs << ":" << this->fila_saida.front()->pac;
            this->fila_saida.pop();
        }
        cout << "}" << endl;
    }
};

int main(){
    Banco banco;
    string opcao;
    string id;
    int docs = 0;
    int pac = 0;
    int qtd_caixas = 0;
    int tempo = 0;
    int docs_processados = 0;
    int docs_perdidos = 0;
    
    while(true){
        getline(cin, opcao);
        stringstream in(opcao);
        in >> opcao;

        if(opcao == "init"){
            in >> qtd_caixas; 
            for(int i = 0; i < qtd_caixas; i++){
                banco.caixas.push_back(NULL);
            }
        }else if(opcao == "show"){
            banco.show_bank();
            cout << endl;
        }else if(opcao == "in"){
            in >> id >> docs >> pac;
            Client* elem = new Client(id, docs, pac);
            banco.fila_entrada.push_back(elem);
            cout << endl;
        }else if(opcao == "tic"){
            tempo++;
            cout << endl; 
        }else if(opcao == "finish"){
            cout << "received: " << docs_processados << endl;
            cout << "lost: " << docs_perdidos << endl;
            cout << "tic: " << tempo << endl;
        }else if(opcao == "end"){
            break;
        }else{
            cout << "opcao invalida." << endl;
        }
    }
}