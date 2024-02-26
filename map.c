#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "filereading.h"

typedef struct {
    char** map;
    int lines;
    int columns;
} Map;

Map* createMapArr(FILE* mapFile) {
    Map* map = malloc(sizeof(Map));
    fscanf(mapFile, "%d %d", &(map->lines), &(map->columns));
    map->map = malloc(sizeof(char*) * map->lines);
    for(int i = 0; i < map->lines; i++) {
        map->map[i] = malloc(sizeof(char) * (map->columns + 1));
    }
    rewind(mapFile);
    return map;
}

void Map_movePlayer(Map* map, char direction) {
    int x;
    int y;
    int found = 0;
    for (int i = 0; i < map->lines; i++) {
        if(found != 0) {
            break;
        }
        for (int j = 0; j < map->columns; j++) {
            if(map->map[i][j] == '@') {
                x = i;
                y = j;
                found++;
                break;
            }
        }
    }
    switch(direction) {
        case 'a':
            map->map[x][y-1] = '@';
            break;
        case 'd':
            map->map[x][y+1] = '@';
            break;
        case 'w':
            map->map[x-1][y] = '@';
            break;
        case 's':
            map->map[x+1][y] = '@';
            break;
        default:
            break;
    }
    map->map[x][y] = '.';
}

void Map_printf(Map* m) {
    for (int i = 0; i < m->lines; i++) {
        printf("%s\n", m->map[i]);
    }
}

Map* Map_new(char* pathToMap) {
    if(pathToMap == NULL) return NULL;
    FILE* fmap = fopen(pathToMap, "r");
    if(fmap == NULL) {
        return NULL;
    }
    Map* map = createMapArr(fmap);
    readline(fmap); // Ignore the first line since it's the dimensions.
    for (int i = 0; i < map->lines; i++) {
        char* line = readline(fmap);
        if(line == NULL) {
            printf("Erro ao ler linha do Mapa\n");
            exit(1);
        }
        sprintf(map->map[i], "%s", line);
    }
    fclose(fmap);
    return map;
}

#endif