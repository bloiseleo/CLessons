#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void checkQuick(char* placeholders, char* secret, char quick) {
	for(int i = 0; i < strlen(secret); i++) {
		if(secret[i] == quick) {
			placeholders[i] = quick;
		}
	}
}

int main() {
	char secret[] = "SECRET_WORD";
	char* placeholders = createPlaceholders(secret);
	int right = 0;
	int killed = 0;
	opening();
	do {
		printf("%s\n", placeholders);
		char quick;
		printf("Type your quick:");
		fflush(stdout);
		scanf(" %c", &quick);
		printf("O seu chute foi: %c", quick);
		checkQuick(placeholders, secret, quick);	
		printf("\n");
	} while(!killed && !right);
	return 0;
}

