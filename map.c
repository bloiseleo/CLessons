#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "filereading.h"
#include "map.h"

Position* Map_find(Map* map, char c) {
    int x;
    int y;
    int found = 0;
    for (int i = 0; i < map->lines; i++) {
        if(found != 0) {
            break;
        }
        for (int j = 0; j < map->columns; j++) {
            if(map->map[i][j] == c) {
                x = i;
                y = j;
                found++;
                break;
            }
        }
    }
    if(found) {
        Position* p = malloc(sizeof(Position));
        p->x = x;
        p->y = y;
        return p;
    }
    return NULL;
}

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
    Position* hp = map->heroPosition;
    int newX = hp->x;
    int newY = hp->y;
    switch(direction) {
        case 'a':
            --newY;
            break;
        case 'd':
            ++newY;
            break;
        case 'w':
            --newX;
            break;
        case 's':
            ++newX;
            break;
        default:
            break;
    }
    if(newX <= 0 || newY <=0 || newX >= map->lines || newY >= map->columns) {
        return;
    }
    if (map->map[newX][newY] != '.') {
        return;
    }
    map->map[hp->x][hp->y] = '.';
    hp->x = newX;
    hp->y = newY;
    map->map[hp->x][hp->y] = '@';
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
    Position* p = Map_find(map, '@');
    if(p == NULL) {
        printf("Hero is not positioned in map\n");
        exit(1);
    }
    map->heroPosition = p;
    return map;
}

#endif