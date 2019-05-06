#include "xmat.h"
#include "xpaint.h"
#include <list>
#include <iostream>
#include <vector>
#include <queue>

using namespace std; 

struct Pos{
    int linha;
    int coluna;
    Pos(int _linha = 0, int _coluna = 0){
        this->linha = _linha;
        this->coluna = _coluna;
    }
};

vector<Pos> vizinhos(int linha, int coluna){
    return vector<Pos> { Pos(linha, coluna - 1), Pos(linha - 1, coluna), Pos(linha, coluna + 1), Pos(linha + 1, coluna) };
}

void mostrar(vector<vector<int> >& matriz, vector<string>& mat, queue<Pos> fila){
    xmat_draw(mat);
    while(!fila.empty()){
        xmat_put_circle(fila.front().linha, fila.front().coluna, WHITE);
        fila.pop();
    }
    for(int linha = 0; linha < (int) matriz.size(); linha++){
        for(int coluna = 0; coluna < (int) matriz[0].size(); coluna++){
            xmat_put_number(linha, coluna, BLACK, matriz[linha][coluna]);
        }
    }
}

bool esta_contido(vector<string> &matriz, int linha, int coluna, char valor){
    if((linha < 0) || (linha >= (int) matriz.size()) || (coluna < 0) || coluna >= (int) matriz[0].size())
        return false;
    return matriz[linha][coluna] == valor;
}

void floodfill(vector<vector <int> >& matriz, vector<string>& cores, int linha, int coluna, char cor_inicial, char cor_final){
    //criar fila
    queue<Pos> fila;
    //enfilera a posicao escolhida
    fila.push(Pos(linha, coluna));
    //pinta essa posicao com a cor escolhida
    cores[linha][coluna] = cor_final;
    //enquanto a fila nao estiver vazia:
    while(!fila.empty()){
        //nova posicao recebe o primeiro da fila
        Pos ref = fila.front();
        //Desenfilera essa posicao
        fila.pop();
        //Percorre as demais posicoes da matriz, pinta e coloca no final da fila
        for(Pos viz : vizinhos(ref.linha, ref.coluna)){
            if(esta_contido(cores, viz.linha, viz.coluna, cor_inicial)){
            cores[viz.linha][viz.coluna] = cor_final;
            fila.push(viz);
            mostrar(matriz, cores, fila);
            }
        }
    }
    
}

int main(){
    int nl = 20;
    int nc = 20;
    //desenha a matriz
    xmat_init(nl, nc);
    vector<string> mat(nl, string(nc, 'g'));
    vector<vector <int> > matriz(nl, vector<int>(nc, -1));
    for(int l = 0; l < (int) mat.size(); l++){
        for(int c = 0; c < (int) mat[0].size(); c++){
            //if(xm_rand(0, 100) < 30)
                mat[l][c] = 'r'; 
        }
    }
    xmat_draw(mat);
    x_save("matriz");
    int l = 0, c = 0;
    puts("Digite a posicao inicial:");
    scanf("%d %d", &l, &c);
    getchar();
    floodfill(matriz, mat, l, c, matriz[l][c], 'b');
    xmat_draw(mat);
    x_save("mat");
    x_close();
}