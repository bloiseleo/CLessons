#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int end() {
    return 0;
}

int main() {
    Map* map = Map_new("./mapa.txt");
    do {
        Map_printf(map);
        char direction;
        scanf(" %c", &direction);
        Map_movePlayer(map, direction);
    } while(!end());
    return 0;
}