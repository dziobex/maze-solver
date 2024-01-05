#ifndef _MAZE_H_
#define _MAZE_H_

#include "cell.h"

#define MAX_SIZE 10

typedef struct {
    cell m[MAX_SIZE][MAX_SIZE];
    int m_size;
    int start, finish;
} maze;


void init_maze( maze* m, int size );

void set_maze_entries( maze* m, int start, int finish );

void print_maze( maze* m );

#endif