#ifndef _SOLVER_H_
#define _SOLVER_H_

#include "cell.h"

/* generowanie labiryntu */

/* generowanie losowego wejścia/wyjścia */

/* wypis danych */


/* ---- macierz incydencji ---- */


/* rekurencyjne usuwanie ścianek między somsiadami */
void passage( cell* previous_popped, cell* popped ) {
    popped->visited = 1;

    if ( previous_popped != NULL ) {
        // nad
        if ( previous_popped->y < popped->y ) {
            previous_popped->bounds[2] = 0;
            popped->bounds[0] = 0;
        }
        // pod
        if ( previous_popped->y > popped->y ) {
            previous_popped->bounds[0] = 0;
            popped->bounds[2] = 0;
        }
        // z prawo
        if ( previous_popped->x < popped->x ) {
            previous_popped->bounds[1] = 0;
            popped->bounds[3] = 0;
        }
        // z lewo
        if ( previous_popped->x > popped->x ) {
            previous_popped->bounds[3] = 0;
            popped->bounds[1] = 0;
        }
    }

    cell* next = leave( popped );

    while ( next != NULL ) {
        passage( popped, next );
        next = leave( popped );
    }
}

#endif