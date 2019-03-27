#include "xpaint.h"

void arvore(int x, int y, int tamanho, int angulo){
    if(tamanho < 30){
        xs_color(MAGENTA);
        xd_filled_circle(x, y, 10);
    }
    if(tamanho < 10)
        return;
    int xFinal = x + tamanho * xm_cos(angulo);
    int yFinal = y - tamanho * xm_sin(angulo);
    //xs_color((XColor){120, 50, 20});
    //if(tamanho < 90)
    xs_color(WHITE);
    xd_thick_line(x, y, xFinal, yFinal, 5);
    //x_step("arvore");
    int aux = xm_rand(2, 3);
    int z[] = {30, -30, xm_rand(-4, 4)};
    for(int s = 0; s < aux; s++)
        arvore(xFinal, yFinal, tamanho - xm_rand(5, 15), angulo + z[s]);
}

int main(){
    int altura = 1500;
    int largura = 1500;
    x_open(altura, largura);
    arvore(largura / 2, altura - 60, 100, 90);
    x_save("arvore");
    x_close();

}