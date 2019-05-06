#include <iostream>
#include <queue>
#include <list>
#include <vector>

using namespace std;

struct Client{
    string id;
    int docs;
    int pac; 
};

struct Banco{
    vector<Client*> caixas;
    list<Client*> fila_entrada;
    queue<Client*> fila_saida;
};

void show_bank(Banco banco){
    // for(Client* elem : banco.caixas){
    //     cout << elem->id << elem->docs << elem->pac << endl;
    // }
    for(Client* elem: banco.fila_entrada){
        cout << elem->id << elem->docs << elem->pac << endl;
    }
}

int main(){
    Banco *banco;
    int tempo_func = 0;
    cout << "Digite o tempo que o Banco permanecera em funcionamento:";
    cin >> tempo_func;
    string opcao = "hehe";
    string id = "maria";
    int docs = 0;
    int paciencia = 0;
    int qtd_caixas = 0;

    while(true){
        cout << "Digite a opcao: " << endl;
        cin >> opcao;
        if(opcao == "init"){
            cout << "Digite a quantidade de caixas disponiveis:" << endl;
            cin >> qtd_caixas;
        }else if(opcao == "show")
            show_bank(*banco);   
        else if(opcao == "tic")
            tempo_func--;
        else if(opcao == "in"){
            cout << "Digite Id, quantidade de documentos e paciencia do cliente, respectivamente:" << endl;
            cin >> id >> docs >> paciencia;
        }else{
            cout << "Opcao invalida." << endl;
        }
    }
}