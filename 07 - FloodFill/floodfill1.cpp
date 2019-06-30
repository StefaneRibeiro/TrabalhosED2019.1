#include <iostream>
#include <vector>
#include <queue>
#include "xmat.h"
#include "xpaint.h"

using namespace std;

struct Pos{
    int l;
    int c;
    Pos(int _linha = 0, int _coluna = 0){
        this->l = _linha;
        this->c = _coluna;
    }
};

vector<Pos> vizinhos(int l, int c){
    return vector<Pos> {Pos(l, c - 1), Pos(l, c + 1), Pos(l - 1, c), Pos(l + 1, c)};
}

bool encontra_valor(vector<string> &matriz, int l, int c, char valor){
    if(l < 0 || l >= (int) matriz.size() || c < 0 || c >= (int) matriz[0].size())
        return false;
    return matriz[l][c] == valor;
}

void pintar(vector<string> &matriz, int l, int c, char cor_base, char cor_final){
    if(!encontra_valor(matriz, l, c, cor_base)) //se essa posicao nao eh a cor base, nao pode pintar
        return;
    matriz[l][c] = cor_final;  //se eh a cor base, deve-se pintar
    xmat_draw(matriz);
    x_step("matriz");
    for(auto viz : vizinhos(l, c)) //para cada vizinho daquela posicao, deve-se pintar
        pintar(matriz, viz.l, viz.c, cor_base, cor_final);
}

void mostrar(vector<vector<int>> &matriz_int, vector<string> &matriz, queue<Pos> fila){
    xmat_draw(matriz);
    while(!fila.empty()){
        xmat_put_circle(fila.front().l, fila.front().c, RED);
        fila.pop();
    }
    for(int l = 0; l < (int) matriz.size(); l++){
        for(int c = 0; c < (int) matriz[0].size(); c++){
            xmat_put_number(l, c, WHITE, matriz_int[l][c]);
        }
    }
    x_step("matriz");
}

bool floodfill(vector<vector<int>> &matriz_int, vector<string> &matriz, Pos inicio, Pos fim, char cor_final){
    queue<Pos> fila; //cria fila
    char cor_base = matriz[inicio.l][inicio.c];
    fila.push(inicio); //coloca primeira posicao(l, c) na fila
    while(!fila.empty()){ //enquanto tiver alguem na fila
        Pos aux = fila.front(); //pos recebe primeira pos da fila
        int pos_atual = matriz_int[aux.l][aux.c];
        fila.pop();
        for(auto viz : vizinhos(aux.l, aux.c)){ //para cada vizinho 
            if(encontra_valor(matriz, inicio.l, inicio.c, cor_base)){ //se ele esta na matriz
                pintar(matriz, inicio.l, inicio.c, cor_base, cor_final); //pinta
                matriz_int[viz.l][viz.c] = pos_atual + 1;
                fila.push(viz); //coloco na fila, porque ja foi pintado
                mostrar(matriz_int, matriz, fila);
                if(viz.l == fim.l && viz.c == fim.c){ //encontrou posicao final
                    return true;
                }
            }
        }
    }
    return false;
}

void pathfind(vector<vector<int>> &matriz_int, vector<string> &matriz, Pos inicio, Pos fim, char cor_final){
    //char cor_final = matriz[fim.l][fim.c];
    vector<string> matriz_aux = matriz;
    bool caminho = floodfill(matriz_int, matriz, inicio, fim, cor_final);
    bool percorrido = false;
    if(caminho == true){
        queue<Pos> fila;
        fila.push(fim); //marcar caminho percorrido do fim ate o inicio
        while(!percorrido){
            Pos aux = fila.back(); //comeca a olhar do fim
            int pos_atual = matriz_int[fim.l][fim.c];
            for(auto viz : vizinhos(aux.l, aux.c)){
                if(encontra_valor(matriz, viz.l, viz.c, cor_final)){
                    if(matriz_int[viz.l][viz.c] == 0){ //cheguei no ponto inicial
                        fila.push(viz);
                        percorrido = true;
                        break;
                    }
                    if(matriz_int[viz.l][viz.c] == pos_atual - 1){
                        fila.push(viz);
                        break;
                    }
                }
            }
            if(percorrido)
                break;
        }
        matriz = matriz_aux;
        while(!fila.empty()){
            Pos aux = fila.front();
            matriz[aux.l][aux.c] = cor_final;
            fila.pop();
            //mostrar(matriz_int, matriz, fila);
        }
        mostrar(matriz_int, matriz, fila);
    }
    
}

int main(){
    int n_linhas = 20;
    int n_colunas = 20;
    xmat_init(n_linhas, n_colunas);
    vector<string> matriz(n_linhas, string(n_colunas, 'b'));
    vector<vector<int>> mat_int(n_linhas, vector<int>(n_colunas, 0));
    for(int l = 0; l < (int) matriz.size(); l++){
        for(int c = 0; c < (int) matriz[0].size(); c++){
            if(xm_rand(0, 100) < 30)
                matriz[l][c] = 'w'; 
        }
    }
    xmat_draw(matriz);
    x_save("matriz");
    Pos inicio, fim;
    puts("Digite o ponto inicial, l e c:");
    scanf("%d %d", &inicio.l, &inicio.c);
    getchar();
    puts("Digite o ponto final, l e c:");
    scanf("%d %d", &fim.l, &fim.c);
    pathfind(mat_int, matriz, inicio, fim, 'b');
    xmat_draw(matriz);
    x_save("matriz");
    x_close();
}