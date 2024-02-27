#include <time.h>
#include <stdlib.h>

int random(int max) {
    srand(time(0));
    return (rand() % max);
}