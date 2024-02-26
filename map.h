typedef struct {
    char** map;
    int lines;
    int columns;
} Map;

Map* Map_new(char* pathToMap);
void Map_printf(Map* map);
void Map_movePlayer(Map* map, char direction);