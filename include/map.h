#ifndef __MAP_H__
#define __MAP_H__

struct Map
{
  int position_trainer;
  char buffer;
  
  int width;
  int height;

  char* mapArray;
};
typedef struct Map Map;

Map* create_map(void);
void delete_map(Map* map);

void set_position_trainer_start(Map* map, int i);
int get_position_trainer(Map* map);

int trainer_can_move(Map* map, Direction dir);
void move_trainer(Map* map, Direction dir);
int get_action_associated(Map* map);


void init_map_empty(Map* map);

void load_map(Map* map, const char* file_name);
void print_map(const Map* map);

#endif
