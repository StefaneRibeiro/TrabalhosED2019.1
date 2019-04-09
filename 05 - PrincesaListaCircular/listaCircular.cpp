#include <iostream>

using namespace std;

struct Node{
    int value;
    Node * next;
    Node * prev;
    Node(int value = 0){
        this->value = value;
        this->next = this;
        this->prev = this;
    }
};

void insert_right(Node * ref, int value){
    Node * node = new Node(value);
    node->next = ref->next;
    node->prev = ref;
    ref->next = node;
    node->next->prev = node;
}

void insert_left(Node * ref, int value){
    insert_right(ref->prev, value);
}

void remove(Node * node){
    node->next->prev = node->prev;
    node->prev->next = node->next;
}

void remove_right(Node * node){
    remove(node->next);
}

void remove_left(Node * node){
    remove(node->prev);
}

void show(Node * node, Node * chosen){
        cout << "[";
        Node * aux = node;
        do{
            cout << " " << aux->value;
            if((aux->value) == (chosen->value))
                cout << ">";
            aux = aux->next;
        }while(aux != node);
        cout << " ]\n";
}

void show_ord(Node * node, Node * chosen){
    Node * menor = node;
    Node * aux = node;
    do{
        if((aux->value) < (menor->value))
            menor = aux;
        aux = aux->next;
    }while(aux != node);
    show(menor, chosen);
}

int main(){
    Node * circular_list = new Node(1);
    int participants = 0;
    int chosen = 0;

    cout << "Digite o numero de participantes  e o escolhido:" << endl;
    cin >> participants >> chosen;

    for(int i = 1; i < participants; i++)
        insert_left(circular_list, i + 1);
    Node * tmp = circular_list;
    while(tmp->next->value != chosen + 1)
        tmp = tmp->next;

    show(circular_list, tmp);

    while(tmp->next != tmp){
        remove_right(tmp);
        tmp = tmp->next;
        show_ord(tmp, tmp);
    }

}