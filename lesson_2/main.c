#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TRIES 10

void opening() {
  printf("*******************\n");
  printf("*  Jogo da Forca  *\n");
  printf("*******************\n");
  return;
}

char *createPlaceholders(char *word) {
  char *placeholders = malloc(sizeof(char) * strlen(word) + 1);
  int i;
  for (i = 0; word[i] != '\0'; i++) {
    placeholders[i] = '_';
  }
  placeholders[i] = '\0';
  return placeholders;
}

int checkQuick(char *placeholders, char *secret, char quick) {
  int changed = 0;
  for (int i = 0; i < strlen(secret); i++) {
    if (secret[i] == quick) {
      changed++;
      placeholders[i] = quick;
    }
  }
  return changed;
}

int checkWin(char *placeholders, char *word) {
  int equals = 0;
  for (int i = 0; i < strlen(word); i++) {
    if (word[i] == placeholders[i]) {
      equals++;
    }
  }
  return equals == strlen(word);
}

void drawForca(char *placeholders, char *secret, int *tries) {
  printf("%s\n", placeholders);
  char quick;
  printf("Type your quick:");
  scanf(" %c", &quick);
  printf("O seu chute foi: %c", quick);
  if (checkQuick(placeholders, secret, quick) == 0) {
    (*tries)++;
  }
}

char *readline(FILE *fp) {
  int bufferSize = 1024;
  char *buffer = malloc(sizeof(char) * bufferSize);
  int i = 0;
  char c;
  do {
    c = fgetc(fp);
    if (c == '\n') {
      break;
    }
    if (i >= bufferSize) {
      bufferSize *= 2;
      buffer = realloc(buffer, sizeof(char) * (bufferSize));
    }
    buffer[i++] = c;
  } while (c != EOF);
  char *str = realloc(buffer, sizeof(char) * (i + 1));
  str[i] = '\0';
  return str;
}

int generateRandomInt(int max) {
  srand(time(0));
  int r = rand() % (max + 1);
  return r == 0 ? 1 : r;
}

char *chooseSecretWord() {
  int qtd;
  char *secret;
  FILE *f = fopen("palavras.txt", "r");
  fscanf(f, " %d", &qtd);
  fseek(f, 1, SEEK_CUR);
  int selected = generateRandomInt(qtd);
  int i = 0;
  while (!feof(f) && i < selected) {
    char *line = readline(f);
    secret = line;
    i++;
  }
  fclose(f);
  return secret;
}

void writeNewWord() {
  char option;
  printf("Do You want to add a new Word? (S\\N)");
  scanf(" %c", &option);

  if (option == 'N') {
    return;
  }
  char newWord[20];
  printf("Type your word:\n");
  scanf("%s", newWord);
  FILE *fp = fopen("palavras.txt", "r+");
  if (fp == NULL) {
    printf("Could not open the database\n");
    exit(1);
  }
  int qtd;
  fscanf(fp, "%d", &qtd);
  qtd++;
  rewind(fp);
  fprintf(fp, "%d", qtd);
  fseek(fp, 0, SEEK_END);
  fprintf(fp, "%s\n", newWord);
  fclose(fp);
  return;
}

int main() {
  char *secret = chooseSecretWord();
  char *placeholders = createPlaceholders(secret);
  int right = 0;
  int killed = 0;
  int tries = 0;
  opening();
  do {
    drawForca(placeholders, secret, &tries);
    if (checkWin(placeholders, secret) > 0) {
      right = 1;
    }
    if (tries >= MAX_TRIES) {
      killed = 1;
    }
    printf("\n");
  } while (!killed && !right);
  if (right > 0 && killed == 0) {
    printf("You won!\n");
  } else {
    printf("You lose!\n");
  }
  writeNewWord();
  return 0;
}
