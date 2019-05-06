#include <stdio.h>
#include <stdbool.h>
const int MORTO = 0;
//Conta a quantidade de vivos no vetor e retorna 1 se a qtd de vivos for 1 senão 0.
int vivos(int v[], int size){
	int cont = 0;
	for(int i = 0; i < size; i++){
		if(v[i] == 0){
			cont++;
		}
	}
	if(cont == size - 1){
		return 1;
	}
	else{
		return 0;
	}
}

int achar_vivo_direita(int vet[], int size, int inicio){
    int pos = (inicio + 1) % size;
    while(vet[pos] == MORTO){
        pos = (pos + 1) % size;
    }
    return pos;
}

int achar_vivo_esquerda(int vet[], int size, int inicio){
  int pos = 0;
	pos = (inicio - 1);
	if(pos < 0){
		pos = size -1 ;
	}
  while(vet[pos] == MORTO){
		if(pos == 0 && vet[pos] == 0){//Verifica se inicio - 1(pos) está morto
			if(vet[size - 1] != 0){//Encontrar vivo a esquerda
				pos = size -1;
				break;
			}
			else{//fazer voltar para posicao final
				pos = size - 1;
			}
		}
		pos = (pos - 1);//enquanto não encontrar vivo fazer isso
  }
  return pos;
}

void mostrarVetor(int vetor[], int tamanho, int escolhido){
  printf("[");
  bool firstElem = true;
  for(int i = 0; i < tamanho; i++){
  if(vetor[i] != MORTO){
    if(firstElem){
      firstElem = false;
    } 
    else{
			printf(" ");
		}
    if(i == escolhido && vetor[i] < 0){
			printf("<");
		}
    printf("%d", vetor[i]);
    if(i == escolhido && vetor[i] > 0) 
			printf(">");
    }
  }
  printf("]\n");
}


int main(){
  int participantes = 0;
  scanf("%d", &participantes);
  int escolhido = 0;
  scanf("%d", &escolhido);
  escolhido = escolhido - 1;
  int fase = 0;
  scanf("%d",&fase );
  int vetor[participantes];
  vetor[0] = fase;// 
  for(int i = 1; i < participantes; i++){
    if(vetor[i-1] < 0){
      vetor[i] = (vetor[i-1] * (-1)) + 1;
    } 
    else{
      vetor[i] = (vetor[i-1] + 1) * (-1);
    }
  }
  int qtd = participantes;
	mostrarVetor(vetor, participantes, escolhido);
  while(qtd--){
		if(vivos(vetor, participantes)) break; //Se a qtd de vivos for 1 ele para
		int andar = vetor[escolhido];
		if(andar < 0) andar = (andar * (-1)); 
    if(vetor[escolhido] < 0){//Andar para esquerda
			int vai_morrer = achar_vivo_esquerda(vetor, participantes, escolhido);
			vetor[vai_morrer] = 0;
			while(andar > 0){//Andar "E" vezes para esquerda
				escolhido = escolhido - 1;
				if(escolhido == -1){
					escolhido = participantes - 1;
				}
				if(escolhido == 0){
					if (vetor[escolhido] == 0){//Se escolhido for 0 ele continua procurando vivo
						escolhido = participantes - 1;
					}
				else{//Se for diferente 0, anda para esquerda
					escolhido = participantes - 1;
					andar--;
				}
			}
			if(vetor[escolhido] != 0){ //Se o escolhido for diferente de 0, anda para a esquerda
				andar--;
			}
		}
		
		mostrarVetor(vetor, participantes, escolhido);
    }
		else if(vetor[escolhido] > 0){//Andar para direita
			int vai_morrer = achar_vivo_direita(vetor, participantes, escolhido);
			vetor[vai_morrer] = 0;
			while(andar > 0){
			//if(vivos(vetor, participantes)) break; 
				escolhido = (escolhido + 1) % participantes;
				if(vetor[escolhido] != 0){
					andar--;
				}
			}
		mostrarVetor(vetor, participantes, escolhido); 
    }
      
  }
  
}

