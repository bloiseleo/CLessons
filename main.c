#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

int end(Map* map) {
    return Map_checkLose(map);
}

void clear() {
    printf("\e[1;1H\e[2J");
}

int main() {
    srand(time(0));
    Map* map = Map_new("./mapa.txt");
    int score = 0;
    do {
        Map_printf(map);
        char direction;
        scanf(" %c", &direction);
        if(direction == EXPLODE) {
            Map_explode(map);
        } else {
            Map_movePlayer(map, direction);
        }
        score++;
        clear();
    } while(!end(map));
    printf("Voce sobreviveu %d rodadas", score);
    return 0;
}