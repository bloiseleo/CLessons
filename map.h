enum Moves {
    UP = 'w',
    DOWN = 's',
    LEFT = 'a',
    RIGHT = 'd'
};

enum Characters {
    PLAYER = '@',
    GHOST = 'F',
    FREE_SPACE = '.'
};

struct position {
    int x;
    int y;
};

typedef struct position Position;

struct map {
    char** map;
    int lines;
    int columns;
    int ghostsSize;
    Position* heroPosition;
    Position* ghostsPosition;
};

typedef struct map Map;


Map* Map_new(char* pathToMap);
void Map_printf(Map* map);
void Map_movePlayer(Map* map, char direction);