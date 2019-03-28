#include <stdio.h>
#include "xpaint.h"

//Funcao que construe um trigo
void trigo(int x, int y, int tamanho, int angulo){
    //Condicao de parada
    if(tamanho < 1)
        return;
    //Construindo o trigo
    for(int i = 0; i < 4; i++){
        int xFinal = x + tamanho * xm_cos(angulo);
        int yFinal = y - tamanho * xm_sin(angulo);
        xs_color(YELLOW);
        //Faz o ramo central
        xd_thick_line(x, y, xFinal, yFinal, 2);
        //Faz os ramos laterais
        trigo(xFinal, yFinal, tamanho / 3, angulo - 30);
        trigo(xFinal, yFinal, tamanho / 3, angulo + 30);
        //Atualiza as variaveis para nao desenhar no mesmo lugar
        x = xFinal;
        y = yFinal;
        
    }
}
int main(){
    int largura = 900;
    int altura = 900;
    x_open(largura, altura);
    trigo(largura / 2, altura - 20, 150, 90);
    x_save("trigo");
    x_close();
    return 0;
}