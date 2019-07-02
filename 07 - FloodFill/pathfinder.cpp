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
    return vector<Pos> {Pos(l, c - 1), Pos(l - 1, c), Pos(l, c + 1), Pos(l + 1, c)};
}

bool existe_valor(vector<string> &matriz, int l, int c, char valor){
    if((l < 0) || (l >= (int) matriz.size()) || (c < 0) || (c >= (int)matriz[0].size()))
        return false;
    return matriz[l][c] == valor;
}

void pintar(vector<string> &matriz, int l, int c, char cor_base, char cor_final){
    if(!existe_valor(matriz, l, c, cor_base));
        return;
    matriz[l][c] = cor_final;
    xmat_draw(matriz);
    x_step("matriz");
    for(auto neibs : vizinhos(l, c))
        pintar(matriz, neibs.l, neibs.c, cor_base, cor_final);

}

void mostrar(vector<vector<int>> &matriz_int, vector<string> &matriz, queue<Pos> fila){
    xmat_draw(matriz);
    while(!fila.empty()){
        xmat_put_circle(fila.front().l, fila.front().c, WHITE);
        fila.pop();
    }
    for(int l = 0; l < (int)matriz.size(); l++){
        for(int c = 0; c < (int)matriz[0].size(); c++){
            xmat_put_number(l, c, BLACK, matriz_int[l][c]);
        }
    }
    x_step("matriz");
}

//Floodfill utilizando fila invez de recursao
void floodfill(vector<vector<int>>& matriz_int, vector<string>& matriz, Pos inicio, Pos fim, char cor_base, char cor_final){
    queue<Pos> fila;
    bool encontrou = false;
    int distancia = 0;
    fila.push(inicio);
    matriz[inicio.l][inicio.c] = cor_final;
    while(!fila.empty() && encontrou == false){
        Pos aux = fila.front();
        fila.pop();
        distancia = matriz_int[aux.l][aux.c];
        for(auto viz : vizinhos(aux.l, aux.c)){
            if(existe_valor(matriz, viz.l, viz.c, cor_base)){
                matriz[viz.l][viz.c] = cor_final;
		        matriz_int[viz.l][viz.c] = distancia + 1;
                fila.push(viz);
                mostrar(matriz_int, matriz, fila);
            }
            if(viz.l == fim.l && viz.c == fim.c)
                encontrou = true;
        }
    }
}

void pathfinder(vector<vector<int>> &matriz_int, vector<string> &matriz, Pos inicio, Pos fim, char cor_base, char cor_final){
    queue<Pos> fila; //cria fila para colocar os elementos que serao visitados
    queue<Pos> _fila; //cria fila para colocar elementos com a cor final
    vector<string> matriz_aux = matriz; //guarda matriz inicial 
    //char cor_base = matriz[inicio.l][inicio.c]; //pega a posicao inicial para saber qual sera a cor base
    bool encontrou = false; //variavel que sinalizara se o caminho foi encontrado
    int pos_atual = 0;
    fila.push(inicio);  //coloca posicao inicial na fila
    matriz[inicio.l][inicio.c] = cor_final; //pinta posicao inicial com cor final

    while(!fila.empty() && encontrou == false){
        Pos aux = fila.front();
        fila.pop();
        pos_atual = matriz_int[aux.l][aux.c] + 1; //conta distancia de posicao inicial ate seus vizinhos
        for(auto neibs : vizinhos(aux.l, aux.c)){
            if(existe_valor(matriz, neibs.l, neibs.c, cor_base)){
                matriz[neibs.l][neibs.c] = cor_final;
                matriz_int[neibs.l][neibs.c] = pos_atual;
                fila.push(neibs);
                mostrar(matriz_int, matriz, fila);
            }
            if(existe_valor(matriz, neibs.l, neibs.c, cor_final) && (neibs.l == fim.l) && (neibs.c == fim.c))
                encontrou = true;
        }
    }
    
    bool percorrido = false;
    if(encontrou){
        _fila.push(fim); //fila vai do fim ate o inicio
        
        while(!percorrido){
            Pos tmp = _fila.back();
            int distancia = matriz_int[tmp.l][tmp.c];
            for(auto neibs : vizinhos(tmp.l, tmp.c)){
                if(existe_valor(matriz, neibs.l, neibs.c, cor_final) && (matriz_int[neibs.l][neibs.c] == 0)){
                    _fila.push(Pos(neibs));
                    percorrido = true;
                }
                if(existe_valor(matriz, neibs.l, neibs.c, cor_final) && (matriz_int[neibs.l][neibs.c]) == distancia - 1){
                    _fila.push(Pos(neibs));
                    break;
                }
                
            }
        }
        matriz = matriz_aux;
        while(!_fila.empty()){
            Pos aux2 = _fila.front();
            matriz[aux2.l][aux2.c] = cor_final;
            _fila.pop();
        }
    }
    if(!encontrou){
        matriz = matriz_aux;
        cout << "Caminho invalido!" << endl;
    }
}

int main(){
    int n_linhas = 20;
    int n_colunas = 20;
    xmat_init(n_linhas, n_colunas);
    vector<string> matriz(n_linhas, string(n_colunas, 'm'));
    vector<vector<int>> matriz_int(n_linhas, vector<int>(n_colunas, 0));
    for(int l = 0; l < (int) matriz.size(); l++){
        for(int c = 0; c < (int) matriz[0].size(); c++){
            if(xm_rand(0, 100) < 30){
                matriz[l][c] = 'b'; 
            }
        }
    }
    xmat_draw(matriz);
    x_save("matriz");
    int l = 0; 
    int c = 0;
    puts("Digite o ponto inicial, linha e coluna:");
    scanf("%d %d", &l, &c);
    Pos inicio = Pos(l, c);
    //getchar();
    puts("Digite o ponto final, linha e coluna:");
    int l_f = 0;
    int c_f = 0;
    scanf("%d %d", &l_f, &c_f);
    Pos fim = Pos(l_f, c_f);
    getchar();
    //floodfill(matriz_int, matriz, inicio, fim, matriz[l][c], 'o');
    pathfinder(matriz_int, matriz, inicio, fim, matriz[l][c], 'o');
    xmat_draw(matriz);
    x_save("matriz");
    x_close();

}