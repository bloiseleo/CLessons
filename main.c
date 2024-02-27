#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int end(Map* map) {
    return Map_checkLose(map);
}

int main() {
    Map* map = Map_new("./mapa.txt");
    int score = 0;
    do {
        Map_printf(map);
        char direction;
        scanf(" %c", &direction);
        Map_movePlayer(map, direction);
        score++;
    } while(!end(map));
    printf("Voce sobreviveu %d rodadas", score);
    return 0;
}