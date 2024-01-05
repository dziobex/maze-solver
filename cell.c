#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "cell.h"

cell init_cell( int y, int x, int size ) {
    cell new_cell = (cell) { .y = y, .x = x, .visited = 0 };
    
    new_cell.id = y * size + x;
    new_cell.value = 0.0;
    new_cell.total_value = 1000;    // ="nieskończoność"
    new_cell.label = ' ';

    for ( int i = 0; i < 4; ++i )
        new_cell.bounds[i] = 1;
    return new_cell;
}

void init_nears( cell *c, cell *t, cell *r, cell *b, cell *l ) {
    for ( int i = 0; i < 4; ++i)
        c->near[i] = malloc( sizeof( cell ) );
    c->near[0] = t;
    c->near[1] = r;
    c->near[2] = b;
    c->near[3] = l;
}

cell *leave( cell *c ) {
    cell *next  = NULL;

    cell *reloaded[4];
    int ids [4];
    int count = 0;

    for ( int i = 0; i < 4; ++i ) {
        reloaded[i] = malloc( sizeof(cell ) );
        if ( c->near[i] != NULL && c->near[i]->visited == 0 ) {
            ids[count] = i;
            reloaded[ count++ ] = c->near[i];
        }
    }
    
    if ( count == 0 ) {
        return NULL;
    }

    int rnd_index = rand() % count;
    
    next = reloaded[ rnd_index ]; // 0 1 2 3

    // c->near[ ids[rnd_index] ] = NULL;
    
    for ( int i = 0; i < 4; ++i)
        free( reloaded[i] );

    return next;
}