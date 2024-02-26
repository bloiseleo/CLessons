#include <stdio.h>
#include <stdlib.h>
#include "filereading.h"

int main() {
    char mapa[5][11];
    FILE* f = fopen("./mapa.txt", "r");

    if(f == NULL) {
        printf("Erro ao ler o Mapa\n");
        exit(1);
    }

    for (int i = 0; i < 5; i++) {
        char* line = readline(f);
        if(line == NULL) {
            printf("Erro ao ler linha do Mapa\n");
            exit(1);
        }
        sprintf(mapa[i], "%s", line);
    }
    
    for (int i = 0; i < 5; i++) {
        printf("%s\n", mapa[i]);
    }
    

    return 0;
}