#ifndef _MAZE_H_
#define _MAZE_H_

#define MAX_SIZE 10

typedef struct cell cell;

struct cell {
    cell *near[4];  // top, right, bottom, left
    char bounds[4]; // granice ze wszond powszond

    char y, x;      // pozycja w matrycy
    char visited;   // flaga: 0 - not visited, 1 - visited
    double value;   // wygenerowana waga dla pola
};

cell init_cell( int y, int x, double rnd_value );
void init_nears( cell *c, cell *t, cell *r, cell *b, cell *l );
cell *leave( cell *c );

void print_maze( cell maze[MAX_SIZE][MAX_SIZE], int size );

#endif