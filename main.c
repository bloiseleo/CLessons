#include <stdio.h>
#include "filereading.h"

int main() {
    FILE* f = fopen("./exemplo.txt", "r");
    char* line;
    while ((line = readline(f)) != NULL) {
        printf("Linha: %s\n", line);
    }
    return 0;
}