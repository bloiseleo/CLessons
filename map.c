#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include "filereading.h"
#include "map.h"
#include "random.h"

enum Rounds playRound;
int pill = 0;

void Map_explode(Map* map) {
    if(pill <= 0) {
        return;
    }
    Position* p = map->heroPosition;
    for(int i = p->y + 1; i < p->y + 4; i++) {
        if(i >= map->columns - 1) {
            break;
        }
        map->map[p->x][i] = FREE_SPACE;
    }
    pill--;
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

int Map_canMove(int x, int y, Map* map) {
    if(x <= 0 || y <=0 || x >= map->lines || y >= map->columns) {
        return 0;
    }
    if(playRound == GHOST_ROUND) {
        char v = map->map[x][y];
        if(v != FREE_SPACE && v == PLAYER) {
            return 1;
        }
    }
    if(map->map[x][y] == PILL)  {
        pill++;
        return 1;
    }
    if (map->map[x][y] != FREE_SPACE) {
        return 0;
    }
    return 1;
}

Position* Map_applyDirection(Map* map, char direction, Position* position) {
    int newX = position->x;
    int newY = position->y;
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
    Position* newP = malloc(sizeof(Position));
    newP->x = newX;
    newP->y = newY;
    return newP;
}

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

char Map_generateDirection(Position gp, Position hp) {
    int ra = random(5);
    int rax = random(5);
    if(rax > ra) {
        int heightGpToHp = gp.x - hp.x;
        int widthGpToHp = gp.y - hp.y;
        if(heightGpToHp > 0) {
            return UP;
        }
        if(heightGpToHp < 0) {
            return DOWN;
        }
        if(widthGpToHp > 0) {
            return LEFT;
        }
        if(widthGpToHp < 0) {
            return RIGHT;
        }
    }
    int r = random(5);
    enum Moves m[5] = {UP, DOWN, LEFT, RIGHT};
    return m[r];
}

int Map_moveGhost(int ghostIndex, Map* map) {
    Position gp = map->ghostsPosition[ghostIndex];
    Position* hp = map->heroPosition;
    char d = Map_generateDirection(gp, *hp);
    Position* newGP = Map_applyDirection(map, d, &gp);
    if(!Map_canMove(newGP->x, newGP->y, map)){
        return 0;
    }
    map->map[gp.x][gp.y] = FREE_SPACE;
    map->map[newGP->x][newGP->y] = GHOST;
    map->ghostsPosition[ghostIndex] = *newGP;
    return 1;
}

void Map_moveGhosts(Map* map) {
    for (int i = 0; i < map->ghostsSize; i++) {
        int moved = 0;
        int tries = 0;
        while(!moved) {
            if(tries > 3) {
                break;
            }
            moved = Map_moveGhost(i, map);
            tries++;
        }
    }
}

int Map_checkLose(Map* m) {
    Position* p = Map_find(m, PLAYER);
    if(p == NULL) {
        return 1;
    }
    return 0;
}

void Map_movePlayerCharacter(int x, int y, Map* map) {
    Position* hp = map->heroPosition;
    map->map[hp->x][hp->y] = FREE_SPACE;
    hp->x = x;
    hp->y = y;
    map->map[hp->x][hp->y] = PLAYER;
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
    Position* newPositionHero = Map_applyDirection(map, direction, hp);
    if(!Map_canMove(newPositionHero->x, newPositionHero->y, map)) {
        free(newPositionHero);
        return;
    }
    Map_movePlayerCharacter(newPositionHero->x, newPositionHero->y, map);
    free(newPositionHero);
    playRound = GHOST_ROUND;
    Map_moveGhosts(map);
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
    playRound = PLAYER_ROUND;
    return map;
}

#endif