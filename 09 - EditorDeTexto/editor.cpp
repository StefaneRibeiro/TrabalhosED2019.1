#include<iostream>
#include<list>
#include <sstream>

using namespace std;

struct Ambient{
    list<char> texto;
    list<char>::iterator cursor;

    Ambient(){
        this->cursor = texto.begin();
    }

    void mostrar(){
        for(list<char>::iterator it = this->texto.begin(); it != this->texto.end(); ++it){
            if(it == this->cursor)
                cout << '|';
            cout << (*it);
        }
        if(this->cursor == this->texto.end())
            cout << '|';
        cout << endl;
    }

    //insere caracteres que não são opcoes
    void inserir(char letra){
        this->texto.insert(cursor, letra);
        this->cursor = this->cursor++;
    }

    void backspace(){
        if(this->cursor != this->texto.begin()){
            this->cursor--;
            this->cursor = this->texto.erase(this->cursor);
        }
    }

    void deletar(){
        if(this->cursor != this->texto.end()){
            this->cursor = this->texto.erase(this->cursor);
        }
    }

    void move_direita(){
        if(this->cursor != this->texto.end())
            this->cursor++;
    }

    void move_esquerda(){
        if(this->cursor != this->texto.begin())
            this->cursor--;
    }
   
};

struct Editor{
    list<Ambient> linha_temporal;
    list<Ambient>::iterator estado_atual;

};

int main(){
    Ambient * editor = new Ambient();
    string opcao;
    char letra;
    while(true){
        getline(cin, opcao);
        stringstream in(opcao);
        while(in >> letra){
            if(letra == 'R'){
               editor->inserir('\n'); 
            }else if(letra == 'B'){
                editor->backspace();
            }else if(letra == 'D'){
                editor->deletar();
            }else if(letra == '>'){
                editor->move_direita();
            }else if(letra == '<'){
                editor->move_esquerda();
            }else{
                editor->inserir(letra);    
            }
        }
        editor->mostrar();
    }
}

