#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Funcao para encontrar o menor valor
int lower_value(int array[], int size, int index){
    int ind_lower = index;
    for(int i = index + 1; i < size; i++){
        if(array[ind_lower] > array[i])
            ind_lower = i; 
    }
    return ind_lower;
}

void selection_sort(int array[], int size){
    int menor = 0;
    for(int i = 0; i < size; i++){
        menor = lower_value(array, size, i);
        int aux = array[i];
        array[i] = array[menor];
        array[menor] = aux;
    }
}

void show(int array[], int size){
    for(int i = 0; i < size; i++)
        printf("%d ", array[i]);
}

int main(){
    srand(100);
    int size = 0;
    printf("Digite o tamanho do vetor:\n");
    scanf("%d", &size);
    int array[size];
    for(int i = 0; i < size; i++)
        array[i] = rand() %  100;
    show(array, size);
    selection_sort(array, size);
    printf("\nVetor ordenado:\n");
    show(array, size);
}