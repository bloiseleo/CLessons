#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "filereading.h"

int lines;
int columns;

char** createMapArr(FILE* mapFile) {
    fscanf(mapFile, "%d %d", &lines, &columns);
    char** map = malloc(sizeof(char*) * lines);
    for(int i = 0; i < lines; i++) {
        map[i] = malloc(sizeof(char) * (columns + 1));
    }
    rewind(mapFile);
    return map;
}

char** Map_new(char* pathToMap) {
    if(pathToMap == NULL) return NULL;
    FILE* fmap = fopen(pathToMap, "r");
    if(fmap == NULL) {
        return NULL;
    }
    char** map = createMapArr(fmap);
    readline(fmap); // Ignore the first line since it's the dimensions.
    for (int i = 0; i < lines; i++) {
        char* line = readline(fmap);
        if(line == NULL) {
            printf("Erro ao ler linha do Mapa\n");
            exit(1);
        }
        sprintf(map[i], "%s", line);
    }
    fclose(fmap);
    return map;
}

#endif