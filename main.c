#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIES 10

void opening() {
	printf("*******************\n");
	printf("*  Jogo da Forca  *\n");
	printf("*******************\n");
	return;
}

char* createPlaceholders(char* word) {
	char* placeholders = malloc(sizeof(char) * (strlen(word) + 1));
	for(int i = 0; i < strlen(word); i++) {
		placeholders[i] = '_';
	}
	placeholders[strlen(word) + 1] = '\0';
	return placeholders;
}

int checkQuick(char* placeholders, char* secret, char quick) {
	int changed = 0;
	for(int i = 0; i < strlen(secret); i++) {
		if(secret[i] == quick) {
			changed++;
			placeholders[i] = quick;
		}
	}
	return changed;
}

int checkWin(char* placeholders, char* word) {
	int equals = 0;
	for(int i = 0; i < strlen(word); i++) {
		if(word[i] == placeholders[i]) {
			equals++;	
		}
	}
	return equals == strlen(word);
}

void drawForca(char* placeholders, char * secret, int* tries) {
	printf("%s\n", placeholders);
	char quick;
	printf("Type your quick:");
	scanf(" %c", &quick);
	printf("O seu chute foi: %c", quick);
	if(checkQuick(placeholders, secret, quick) == 0) {
		(*tries)++;
	}
}

char* chooseSecretWord() {
	int qtd;	
	char* secret = malloc(sizeof(char));
	FILE* f = fopen("palavras.txt", "r");
	fscanf(f, "%d", &qtd);
	qtd++;
	srand(time(0));
	int random = rand() % qtd;
	if(random == 0) random = 1;
	for(int i = 0; i < random; i++) {
		fscanf(f, "%s", secret);
	}
	fclose(f);
	return secret;
}	

int main() {
	char* secret = chooseSecretWord();
	char* placeholders = createPlaceholders(secret);
	int right = 0;
	int killed = 0;
	int tries = 0;
	opening();
	do {
		drawForca(placeholders, secret, &tries);
		if(checkWin(placeholders, secret) > 0) {
			right = 1;
		}
		if(tries >= MAX_TRIES) {
			killed = 1;
		}
		printf("\n");
	} while(!killed && !right);
	if(right > 0 && killed == 0) {
		printf("You won!\n");
	} else {
		printf("You lose!\n");
	}
	return 0;
}

