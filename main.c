#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int main() {
    
    char** map = Map_new("./mapa.txt");

    for (int i = 0; i < 5; i++) {
        printf("%s\n", map[i]);
    }
    

    return 0;
}