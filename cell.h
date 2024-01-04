#ifndef _CELL_H_
#define _CELL_H_

typedef struct cell cell;
#define MAX_SIZE 10

struct cell {
    cell *near[4];  // top, right, bottom, left
    char bounds[4]; // granice ze wszond powszond

    char y, x;      // pozycja w macierzy
    char visited;   // flaga: 0 - not visited, 1 - visited
    double value;   // wygenerowana waga dla pola

    cell *previous;
};

cell init_cell( int y, int x, double rnd_value );
void init_nears( cell *c, cell *t, cell *r, cell *b, cell *l );
cell *leave( cell *c );

void print_maze( cell maze[MAX_SIZE][MAX_SIZE], int size );

#endif