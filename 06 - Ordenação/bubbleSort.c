#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int array[], int size){
    int i, j, aux;
    for( i = 0; i < size; i++ ){
        for( j = i + 1; j < size; j++ ){
            if( array[i] > array[j]) {
                aux = array[i];
                array[i] = array[j];
                array[j] = aux;
            }
        }
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
    bubble_sort(array, size);
    printf("\nVetor ordenado:\n");
    show(array, size);
}