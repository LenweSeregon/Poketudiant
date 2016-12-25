#ifndef __MAP_H__
#define __MAP_H__

enum Tile_type
  {
    WILD = '1',
    ROAD = '0',
    NURSE = 'n',
    ENEMY = 'e'
  };
typedef enum Tile_type Tile_type;

/* ------------------------------------------------ */

struct Tile_wild
{
  int level;
  char val;
};
typedef struct Tile_wild Tile_wild;

/* ------------------------------------------------ */

struct Tile_enemy
{
  char val;
  char name[MAX_NAME_DIPLOMA_TRAINER];
};
typedef struct Tile_enemy Tile_enemy;

/* ------------------------------------------------ */

struct Tile_nurse
{
  char val;
};
typedef struct Tile_nurse Tile_nurse;


/* ------------------------------------------------ */

struct Tile_road
{
  char val;
};
typedef struct Tile_road Tile_road;


/* ------------------------------------------------ */

union Tile_union
{
  Tile_wild wild;
  Tile_enemy enemy;
  Tile_nurse nurse;
  Tile_road road;
};
typedef union Tile_union Tile_union;

/* ------------------------------------------------ */

struct Tile
{
  Tile_union tile;
  Tile_type type;
};
typedef struct Tile Tile;

/* ------------------------------------------------ */

struct Map
{
  int position_trainer;
  Tile buffer;
  
  int width;
  int height;

  /*char* mapArray;*/
  Tile* mapArray;
};
typedef struct Map Map;

Map* create_map(void);
void delete_map(Map* map);

void set_position_trainer_start(Map* map, int i);

int trainer_can_move(Map* map, Direction dir);
void move_trainer(Map* map, Direction dir);
int get_action_associated(const Map* map);
int get_level_wild_poketudiant(const Map* map);
const char* get_name_diploma_trainer(const Map* map);
void destroy_enemy_and_set_road(Map* map);

void init_map_empty(Map* map);

void load_map(Map* map, const char* file_name);
void print_map(const Map* map);

#endif
