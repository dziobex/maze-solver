#ifndef _SOLVER_H_
#define _SOLVER_H_

#include "cell.h"
#include "maze.h"

cell* min_cost( maze* m );

void shortest_path( maze* m );

/* rekurencyjne usuwanie ścianek między somsiadami */
void passage( cell* previous_popped, cell* popped );

#endif