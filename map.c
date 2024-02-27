#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "filereading.h"
#include "map.h"

void Map_findGhosts(Map* map) {
    int bufferSize = 1;
    int read = 0;
    Position* buff = malloc(sizeof(Position) * bufferSize);
    for(int i = 0; i < map->lines; i++) {
        for(int j = 0; j < map->columns; j++) {
            if(map->map[i][j] == GHOST) {
                if(read >= bufferSize) {
                    bufferSize *= 2;
                    buff = realloc(buff, sizeof(Position) * bufferSize);
                }
                Position p = {
                    .x = i,
                    .y = j
                };
                buff[read++] = p;
            }
        }
    }
    map->ghostsPosition = realloc(buff, sizeof(Position) * read);
    map->ghostsSize = read;
}

int Map_canMove(int x, int y, Map* map) {
    if(x <= 0 || y <=0 || x >= map->lines || y >= map->columns) {
        return 0;
    }
    if (map->map[x][y] != '.') {
        return 0;
    }
    return 1;
}

void Map_movePlayerCharacter(int x, int y, Map* map) {
    Position* hp = map->heroPosition;
    map->map[hp->x][hp->y] = '.';
    hp->x = x;
    hp->y = y;
    map->map[hp->x][hp->y] = PLAYER;
}

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
        case LEFT:
            --newY;
            break;
        case RIGHT:
            ++newY;
            break;
        case UP:
            --newX;
            break;
        case DOWN:
            ++newX;
            break;
        default:
            break;
    }
    if(!Map_canMove(newX, newY, map)) {
        return;
    }
    Map_movePlayerCharacter(newX, newY, map);
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
    Map_findGhosts(map);
    return map;
}

#endif