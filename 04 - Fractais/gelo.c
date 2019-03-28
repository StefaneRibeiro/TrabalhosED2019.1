#include <stdio.h>
#include "xpaint.h"

//Funcao para construir um floco de neve
void floco_de_neve(int x, int y, int tamanho, int angulo){
    //Condicao de parada
    if(tamanho < 1) 
        return;    
    //Loop para desenhar as 5 retas iniciais 
    for(int i = 0; i < 5; i++){
        int xFinal = x + tamanho * xm_cos(angulo);
        int yFinal = y - tamanho * xm_sin(angulo);
        xd_thick_line(x, y, xFinal, yFinal, 2);
        //Chama a recursao
        floco_de_neve(xFinal, yFinal, tamanho/3, angulo - 70);
        //Aumento do angulo para desenhar as proximas linhas
        angulo += 70;    
    }
}
int main(){
    int altura = 800;
    int largura = 800;
    x_open(altura, largura);
    //x_clear(BLACK);
    floco_de_neve(largura / 2, altura / 2, 265, 270);
    x_save("gelo");
    x_close();
}