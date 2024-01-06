#ifndef _SOLVER_H_
#define _SOLVER_H_

#include "cell.h"
#include "maze.h"

/* alternatywa dla kolejki priorytetowej xd */
cell* min_cost( maze* m );

/* dijkstra B) */
void shortest_path( maze* m );

/* rekurencyjne usuwanie ścianek między somsiadami */
void passage( cell* previous_popped, cell* popped );

#endif