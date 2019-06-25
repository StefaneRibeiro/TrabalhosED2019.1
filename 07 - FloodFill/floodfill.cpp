#include <iostream>
#include <vector>
#include <queue>
#include "xmat.h"
#include "xpaint.h"

using namespace std;

struct Pos{
    int linha;
    int coluna;
    Pos(int _linha, int _coluna){
        this->linha = _linha;
        this->coluna = _coluna;
    }
};

vector<Pos> vizinhos(int linha, int coluna){
    return vector<Pos> {Pos(linha, coluna - 1), Pos(linha, coluna + 1), Pos(linha - 1, coluna), Pos(linha + 1, coluna)};
}

bool encontra_valor(vector<string> &matriz, int linha, int coluna, char valor){
    if(linha < 0 || linha >= (int) matriz.size() || coluna < 0 || coluna >= (int) matriz[0].size())
        return false;
    return matriz[linha][coluna] == valor;
}

void pintar(vector<string> &matriz, int linha, int coluna, char cor_base, char cor_final){
    if(!encontra_valor(matriz, linha, coluna, cor_base)) //se essa posicao nao eh a cor base, nao pode pintar
        return;
    matriz[linha][coluna] = cor_final;  //se eh a cor base, deve-se pintar
    xmat_draw(matriz);
    x_step("matriz");
    for(auto viz : vizinhos(linha, coluna)) //para cada vizinho daquela posicao, deve-se pintar
        pintar(matriz, viz.linha, viz.coluna, cor_base, cor_final);
}

void mostrar(vector<vector<int>> &matriz_int, vector<string> &matriz, queue<Pos> fila){
    xmat_draw(matriz);
    while(!fila.empty()){
        xmat_put_circle(fila.front().linha, fila.front().coluna, RED);
        fila.pop();
    }
    for(int linha = 0; linha < (int) matriz.size(); linha++){
        for(int coluna = 0; coluna < (int) matriz[0].size(); coluna++){
            xmat_put_number(linha, coluna, WHITE, matriz_int[linha][coluna]);
        }
    }
    x_step("matriz");
}

bool floodfill(vector<vector<int>> &matriz_int, vector<string> &matriz, int linha, int coluna, int linha_f, int coluna_f, char cor_base, char cor_final){
    queue<Pos> fila; //cria fila
    fila.push(Pos(linha, coluna)); //coloca primeira posicao(linha, coluna) na fila
    bool encontrou = false;  //variavel para sera true qnd encontrar a posicao final
    while(!fila.empty()){ //enquanto tiver alguem na fila
        Pos aux = fila.front(); //pos recebe primeira pos da fila
        int pos_atual = matriz_int[aux.linha][aux.coluna];
        fila.pop();
        for(auto viz : vizinhos(aux.linha, aux.coluna)){ //para cada vizinho 
            if(encontra_valor(matriz, linha, coluna, cor_base)){ //se ele esta na matriz
                pintar(matriz, linha, coluna, cor_base, cor_final); //pinta
                matriz_int[viz.linha][viz.coluna] = pos_atual + 1;
                fila.push(viz); //coloco na fila, porque ja foi pintado
                mostrar(matriz_int, matriz, fila);
                if(viz.linha == linha_f && viz.coluna == coluna_f){ //encontrou posicao final
                    encontrou = true; //encontrou caminho
                    break;
                }
            }
        }
        if(encontrou == true){
            break;
            return true;
        }
    }
    return false;
}

void pathfind(vector<vector<int>> &matriz_int, vector<string> &matriz, int linha, int coluna, int linha_f, int coluna_f, char cor_base, char cor_final){
    matriz[linha][coluna] = cor_final;
    vector<string> matriz_aux = matriz;
    bool caminho = floodfill(matriz_int, matriz, linha, coluna, linha_f, coluna_f, cor_base, cor_final);
    bool percorrido = false;
    if(caminho == true){
        queue<Pos> fila;
        fila.push(Pos(linha_f, coluna_f)); //marcar caminho percorrido do fim ate o inicio
        while(!percorrido){
            Pos aux = fila.back(); //comeca a olhar do fim
            int pos_atual = matriz_int[linha_f][coluna_f];
            for(auto viz : vizinhos(aux.linha, aux.coluna)){
                if(encontra_valor(matriz, viz.linha, viz.coluna, cor_final)){
                    if(matriz_int[viz.linha][viz.coluna] == 0){ //cheguei no ponto inicial
                        fila.push(viz);
                        percorrido = true;
                        break;
                    }
                    if(matriz_int[viz.linha][viz.coluna] == pos_atual - 1){
                        fila.push(viz);
                        break;
                    }
                }
            }
        }
        matriz = matriz_aux;
        while(!fila.empty()){
            Pos aux = fila.front();
            matriz[aux.linha][aux.coluna] = cor_final;
            fila.pop();
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
    int l = 0, c = 0;
    puts("Digite o ponto inicial, l e c:");
    scanf("%d %d", &l, &c);
    getchar();
    puts("Digite o ponto final, l e c:");
    int linha_f;
    int coluna_f;
    scanf("%d %d", &linha_f, &coluna_f);
    pathfind(mat_int, matriz, l, c, matriz[l][c], 'b', linha_f, coluna_f);
    xmat_draw(matriz);
    x_save("matriz");
    x_close();
}