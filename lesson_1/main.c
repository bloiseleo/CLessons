#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIES 3

int random_number(int max) {
	int seconds = time(0);
	srand(seconds);
	return rand() % max;
}

void welcomeMessage() {
	for(int i = 0; i < 31; i++) {
		printf("*");
	}
	printf("\n");
	printf("Bem Vindo ao Jogo de Advinhação\n");
	for(int i = 0; i < 31; i++) {
		printf("*");
	}
	printf("\n");
}

int* inputChute() {
	int* chute = malloc(sizeof(int));
	printf("Digite o seu chute:\n");
	fflush(stdout);	
	scanf("%d", chute);
	return chute;
}

int main() {
	welcomeMessage();
	int score = 1000;
	int number = random_number(100); 
	int tentativas = 0;
	int acertou;
	while(tentativas < MAX_TRIES) {
		int* chute = inputChute();
		if((*chute) < 0) {
			printf("Você não pode chutar números negativos. Por causa da brincadeira, você perdeu 100 pontos\n");
			score -= 100;	
			continue;
		}
		acertou = (*chute) == number;
		if(acertou) {
			break;
		}
		printf("O chute é %d e está incorreto! Você perdeu 10 pontos \n", *chute);
		if((*chute) > number) {
			printf("O chute é maior que o número\n");
		} else {
			printf("O chute é menor que o número\n");
		}
		score -= 10;
		tentativas++;	
	}
	if(acertou) {
		printf("Você acertou! Parabéns!\n");
		printf("Score total %d", score);
		return 0;
	}
	printf("Você não conseguiu advinhar. Contudo, não desista! Tente denovo mais tarde!\n");
	return 0;
}
