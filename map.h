struct position {
    int x;
    int y;
};


typedef struct position Position;

struct map {
    char** map;
    int lines;
    int columns;
    Position* heroPosition;
};

typedef struct map Map;

Map* Map_new(char* pathToMap);
void Map_printf(Map* map);
void Map_movePlayer(Map* map, char direction);