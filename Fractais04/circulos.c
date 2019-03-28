#include <stdio.h>
#include "xpaint.h"

//Funcao para construir os circulos
void circulos(int x, int y, int raio, int angulo){
    //Condicao de parada
    if(raio < 1)
        return;
    //Loop para construir os circulos
    for(int i = 0; i < 6; i++){
        //Faz o circulo maior
        xd_circle(x, y, raio);
        //Faz os 6 circulos menores
        int xFinal = x + raio * xm_cos(angulo);
        int yFinal = y + raio * xm_sin(angulo);
        xd_circle(xFinal, yFinal, raio / 3);
        //Chama a recursao
        circulos(xFinal, yFinal, raio / 3, angulo);
        angulo += 60;

    }
}
int main(){
    int altura = 900;
    int largura = 900;
    x_open(altura, largura);
    circulos(largura / 2, altura / 2, 200, 0);
    x_save("circulos");
    x_close();
}