#include <stdio.h>

int const ARVORE = '#';
int const FOGO = 'o';
int const VAZIO = '.';
int const PERCURSO = 'x';


void mostrarMatriz(int numL, int numC, char matriz[numL][numC]){
    for(int i = 0; i < numL; i++){
        for(int j = 0; j < numC; j++)
            printf("%c", matriz[i][j]);
        puts("");
    }
}

int tocarFogo(int numL, int numC, char matriz[numL][numC], int linhas, int colunas){
    if((linhas < 0) || (linhas >= numL) || (colunas < 0) || (colunas >= numC)) 
        return 0;
    if(matriz[linhas][colunas] != ARVORE)
        return 0;
    matriz[linhas][colunas] = FOGO;
    mostrarMatriz(numL, numC, matriz);
    getchar();

    int cont = 1;
    cont = cont + tocarFogo(numL, numC, matriz, linhas, colunas + 1);
    cont = cont + tocarFogo(numL, numC, matriz, linhas, colunas - 1);
    cont = cont + tocarFogo(numL, numC, matriz, linhas - 1, colunas);
    cont = cont + tocarFogo(numL, numC, matriz, linhas + 1, colunas);
   
    matriz[linhas][colunas] = PERCURSO;
    mostrarMatriz(numL, numC, matriz);
    getchar();
    
    return cont;
}
int main(){
    int numL = 0;
    int numC = 0;
    int linhas = 0;
    int colunas = 0;

    scanf("%d %d %d %d", &numL, &numC, &linhas, &colunas);

    char matriz[numL][numC];
    for(int i = 0; i < numL; i++){
        for(int j = 0; j < numC; j++)
            scanf(" %c", &matriz[i][j]);
    }
    int qtd_de_queimadas = tocarFogo(numL, numC, matriz, linhas, colunas); 
    //mostrarMatriz(numL, numC, matriz);
    printf("Quantidade de arvores queimadas:%d\n", qtd_de_queimadas);

}
