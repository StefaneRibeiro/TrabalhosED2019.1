
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

int moverLinha[] = {0, 0, -1, 1};
int moverColuna[] = {-1, 1, 0, 0};

int const PAREDE = '#';
int const CAMINHO = ' ';
int const PERCORRIDO = '.';

void mostrar_labirinto(int nLinhas, int nColunas, char matriz[nLinhas][nColunas]){
    for(int i = 0; i < nLinhas; i++){
        for(int j = 0; j < nColunas; j++){
            if(matriz[i][j] == PAREDE)
                printf("█");
            else
                printf("%c", matriz[i][j]);
        }
        puts("");
    }
    puts("");
} 

void embaralhar(int vetor[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        int posicao = rand() % tamanho;
        int aux = vetor[i];
        vetor[i] = vetor[posicao];
        vetor[posicao] = aux; 
    }
}

void furar(int nLinhas, int nColunas, char matriz[nLinhas][nColunas], int linha, int coluna){
    if((linha < 1) || (linha > nLinhas - 2) || (coluna < 1) || (coluna > nColunas -2))
        return;
    if(matriz[linha][coluna] != PAREDE)
        return;
    int contador = 0;
    for(int i = 0; i < 4; i++){
        int aux = linha + moverLinha[i];
        int tmp = coluna + moverColuna[i];
        if(matriz[aux][tmp] == CAMINHO)
            contador++; 
    }
    if(contador > 1)
        return;
    matriz[linha][coluna] = CAMINHO;
    //mostrar_labirinto(nLinhas, nColunas, matriz);
    int vizinhos[] = {0, 1, 2, 3};
    embaralhar(vizinhos, 4);
    for(int pos = 0; pos < 4; pos++){
        int i = vizinhos[pos];
        furar(nLinhas, nColunas, matriz, linha + moverLinha[i], coluna + moverColuna[i]);
    }

}

bool procurar_saida(int nLinhas, int nColunas, char matriz[nLinhas][nColunas], bool mvis[nLinhas][nColunas], int linha, int coluna, int lsaida, int csaida){
    bool trajeto = 0;
    if(matriz[linha][coluna] == PAREDE)
        return false;
    if(mvis[linha][coluna] == true)
        return false;
    mvis[linha][coluna] = true;
    matriz[linha][coluna] = PERCORRIDO; 
    if(linha == lsaida && coluna == csaida)
        return true;
    for(int i = 0; i < 4; i++){
        trajeto = procurar_saida(nLinhas, nColunas, matriz, mvis, linha + moverLinha[i], coluna + moverColuna[i], lsaida, csaida);
        if(trajeto)
            return true;
    }
    matriz[linha][coluna] = CAMINHO;
    //mostrar_labirinto(nLinhas, nColunas, matriz);
    return false;
}
int main(){
    srand(time(NULL));
    int nLinhas = 0;
    int nColunas = 0;
    printf("Digite as dimensoes do labirinto:\n");
    scanf("%d %d", &nLinhas, &nColunas);
    char matriz[nLinhas][nColunas];
    bool mvis[nLinhas][nColunas];

    for(int i = 0; i < nLinhas; i++){
        for(int j = 0; j < nColunas; j++){
            matriz[i][j] = PAREDE;
            mvis[i][j] = false;
        }
    }
    printf("%d %d\n", nLinhas, nColunas);
    furar(nLinhas, nColunas, matriz, 1, 1);
    mostrar_labirinto(nLinhas, nColunas, matriz);
    int linhaI = 0;
    int colunaI = 0;
    int linhaF = 0;
    int colunaF = 0;
    printf("Digite a posicao inicial:\n");
    scanf("%d %d", &linhaI, &colunaI);
    printf("Digite a posicao final:\n");
    scanf("%d %d", &linhaF, &colunaF);
    
    bool trajeto = procurar_saida(nLinhas, nColunas, matriz, mvis, linhaI, colunaI, linhaF, colunaF);
    mostrar_labirinto(nLinhas, nColunas, matriz);
}

