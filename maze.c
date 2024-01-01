#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "maze.h"

cell init_cell( int y, int x, double rnd_value ) {
    cell new_cell = (cell) { .y = y, .x = x, .visited = 0 };
    
    new_cell.value = rnd_value;

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

    c->near[ ids[rnd_index] ] = NULL;
    
    for ( int i = 0; i < 4; ++i)
        free( reloaded[i] );

    return next;
}

void print_maze(cell maze[MAX_SIZE][MAX_SIZE], int size) {

    /* --- GORNA BARIERKA ---- */

    /* wyswietlanie gornych barierek komorek */
    for ( int x = 0; x < size; ++ x) {
        /* barierka nad lewa scianka przed komorka */
        printf ("%s ", "#");
        /* barierka nad komorka */
        printf ("%s ", maze[0][x].bounds[0] == 1 ? "#" : " ");
    }
    /* barierka od skrajnej prawej + odstep na nowy wiersz z komorkami */
    printf("#\n");

    /* ---- KOMORKI LABIRYNTU ---- */

    for ( int y = 0; y < size; ++y ) {
        for ( int x = 0; x < size; ++ x) {
            if ( maze[y][x].bounds[3] == 1 )
                printf("# ");
            else
                printf("  ");
            printf("  ");
            if ( x == size - 1 )
                printf("# ");
        }

        printf("\n");

        /* --- DOLNE BARIERKI ---- */

        /* wyswietlanie dolnych barierek komorek */
        for ( int x = 0; x < size; ++ x) {
            /* barierka pod lewa scianka przed komorka */
            printf ("%s ", "#");
            /* barierka pod komorka */
            printf ("%s ", maze[ y ][x].bounds[2] == 1 ? "#" : " ");
        }
        /* barierka od skrajnej prawej + odstep na nowy wiersz z komorkami */
        printf("#\n");
    }
}