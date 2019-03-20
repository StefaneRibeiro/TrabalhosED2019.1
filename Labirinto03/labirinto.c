#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int const PAREDE = '#';
int const FURADO = ' ';

typedef struct Posicao{
    int linha;
    int coluna;
}Pos;

#define Vizinhos(linha, coluna) {{linha, coluna + 1}, {linha, coluna - 1}, {linha + 1, coluna}, {linha - 1, coluna}}

bool esta_contido(int nlinhas, int ncolunas, char matriz[nlinhas][ncolunas], int linha, int coluna, char valor){
    if((linha < 0) || (linha >= nlinhas) || (coluna < 0) || (coluna >= ncolunas))
        return false;
    return matriz[linha][coluna] == valor;
}
void embaralhar(Pos viz[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        int posicao = rand() % tamanho;
        Pos temp = viz[i];
        viz[i] = viz[posicao];
        viz[posicao] = temp; 
    }
}

bool permitido_furar(int nlinhas, int ncolunas, char matriz[nlinhas][ncolunas], int linha, int coluna){
    if(!esta_contido(nlinhas, ncolunas, matriz, linha, coluna, PAREDE))
        return false;
    int contador = 0;
    Pos vizinhos[4] = Vizinhos(linha, coluna);
    for(int i = 0; i < 4; i++){
        if(permitido_furar(nlinhas, ncolunas, matriz, vizinhos[i].linha, vizinhos[i].coluna))
            contador++;
    }
    if(contador < 3)
        return false;
    return true;
}

void furar(int nlinhas, int ncolunas, char matriz[nlinhas][ncolunas], int linha, int coluna){
    if(!permitido_furar(nlinhas, ncolunas, matriz, linha, coluna))
        return;
    matriz[linha][coluna] = FURADO;
    Pos vizinhos = Vizinhos(linha, coluna);
    embaralhar(vizinhos, 4);
    for(int i = 0; i < 4; i++){
        furar(nlinhas, ncolunas, matriz, vizinhos[i].linha, vizinhos[i].coluna);
    }
}

void mostrar(int nlinhas, int ncolunas, char matriz[nlinhas][ncolunas]){
    for(int i = 0; i < nlinhas; i++){
        for(int i = 0; i < ncolunas; i++){
            printf("%c", matriz[i][j]);
        }
        puts("");
    }
}


int main(){
   int nlinhas = 0;
   int ncolunas = 0;
   printf("Digite as dimensoes da matriz:\n");
   scanf("%d %d", &nlinhas, &ncolunas);

   for(int i = 0; i < nlinhas; i++){
       for(int j = 0; j <= ncolunas; j++){
           printf('#');
       }
   } 
   furar(nlinhas, ncolunas, matriz, 1, 1);
   mostrar(nlinhas, ncolunas, matriz);

}