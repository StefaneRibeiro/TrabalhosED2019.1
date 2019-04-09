#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int array[], int size){
    int value = 0; 
    int j = 0;
    for(int i = 0; i < size; i++){
        value = array[i+1];
        j = i;
        while(j >= 0 && array[j] > value){
            array[j+1] = array[j];
            j--;
        }
        array[j+1] = value;

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
    insertion_sort(array, size);
    printf("\nVetor ordenado:\n");
    show(array, size);
}