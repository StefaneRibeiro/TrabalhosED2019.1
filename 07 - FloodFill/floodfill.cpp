#include <iostream>
#include <vector>
#include <queue>
#include "xmat.h"
#include "xpaint.h"

using namespace std;

struct Pos{
    int l;
    int c;
    Pos(int linha = 0, int coluna = 0){
        this->l = linha;
        this->c = coluna;
    }
};

vector<Pos> vizinhos(int l, int c){
    return vector<Pos> {Pos(l, c - 1), Pos(l, c + 1), Pos(l - 1, c), Pos(l + 1, c)};
}

bool existe_valor(vector<string> &matriz, int l, int c, char valor){
    if((l < 0) || (l >= matriz.size()) || (c < 0) || (c >= matriz[0].size()))
        return false;
    return matriz[l][c] = valor; 
}

void pintar(vector<string> matriz, int l, int c, char cor_base, char cor_final){
    if(!existe_valor(matriz, l, c, cor_base));
        return;
    matriz[l][c] = cor_final;
    xmat_draw(matriz);
    x_step("matriz");
    for(auto neibs : vizinhos(l, c))
        pintar(matriz, neibs.l, neibs.c, cor_base, cor_final);

}

bool floodfill()
