#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "math_utils.h"


void init_seed_to_null()
{
  srand(time(NULL));
  random_double(0.0,1.0);
}
int random_int(int min, int max)
{
  return rand() % (max + 1 - min) + min;
}
double random_double(double min, double max)
{
  double range = (max - min); 
  double div = RAND_MAX / range;
  return min + (rand() / div);
}
