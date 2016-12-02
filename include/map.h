#ifndef __MAP_H__
#define __MAP_H__

struct Map
{
  int width;
  int height;

  char* mapArray;
};
typedef struct Map Map;

Map* create_map(void);
void delete_map(Map* map);

void init_map_empty(Map* map);

void load_map(Map* map, const char* file_name);
void print_map(const Map* map);

#endif
