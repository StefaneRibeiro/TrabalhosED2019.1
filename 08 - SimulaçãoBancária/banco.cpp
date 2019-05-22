#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <sstream>

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
        //mostrar fila de entrada
        cout << "in :{ ";
        list<Client*>::iterator it;
        for(it = this->fila_entrada.begin(); it != this->fila_entrada.end(); ++it){
            cout << (*it)->id << ":" << (*it)->docs << ":" << (*it)->pac << " ";
        }
        cout << "}" << endl;
        //mostrar fila de saida
        cout << "out :{ ";
        while(!this->fila_saida.empty()){
            cout << this->fila_saida.front()->id << ":" << this->fila_saida.front()->docs << ":" << this->fila_saida.front()->pac << " ";
            this->fila_saida.pop();
        }
        cout << "}" << endl;
    }

   void bank_simulation(int &docs_processados, int &docs_perdidos){
       while(!this->fila_saida.empty()){
           this->fila_saida.pop();
       }
       for(int i = 0; i < this->caixas.size(); i++){
           if(this->caixas[i] != NULL){
               if(this->caixas[i]->docs > 0){
                   this->caixas[i]->docs--;
                   docs_processados++;
               }else{
                   this->fila_saida.push(this->caixas[i]);
                   this->caixas[i] = NULL;
               }
           }else{
               if(!this->fila_entrada.empty()){
                   this->caixas[i] = this->fila_entrada.front();
                   this->fila_entrada.pop_front();
               }
           }
       }
       list<Client*>::iterator it;
       for(it = this->fila_entrada.begin(); it != this->fila_entrada.end(); ++it){
           if((*it)->pac > 0){
               (*it)->pac--;
           }
           if((*it)->pac == 0 || (*it)->docs == 0){
               this->fila_saida.push(*it);
               docs_perdidos = docs_perdidos + (*it)->docs;
               it = this->fila_entrada.erase(it);
               it--;
           }
        }
   }

   int maximizar_lucro(int &docs_processados, int &qtd_caixas){
       int qtd_ideal_caixas = (docs_processados - (qtd_caixas * 100));
       return qtd_ideal_caixas;
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
        }else if(opcao == "in"){
            in >> id >> docs >> pac;
            Client* elem = new Client(id, docs, pac);
            banco.fila_entrada.push_back(elem);
        }else if(opcao == "tic"){
            banco.bank_simulation(docs_processados, docs_perdidos);
            tempo++;
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
    int lucro = banco.maximizar_lucro(docs_perdidos, qtd_caixas);
    cout << "Quantidade ideal de caixas: " << lucro << " " << "caixas." << endl;
}