#ifndef _MAZE_H_
#define _MAZE_H_

#include "cell.h"

typedef struct {
    cell m[MAX_SIZE][MAX_SIZE];
    int m_size;
    int start, finish;
} mz;

void gen_random_entries( mz* m );

void print_maze( mz* m );

#endif