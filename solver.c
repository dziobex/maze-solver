#include "solver.h"

#include <stdio.h>


/* znajdowanie komórki, do której koszt dojścia jest najmniejszy */

cell* min_cost( maze* m ) {
    cell *c = NULL;
    double vl = 10000;

    for ( int i = 0; i < m->m_size; ++i ) {
        for ( int j = 0; j < m->m_size; ++j ) {
            if ( m->m[i][j].visited == 0 && m->m[i][j].total_value < vl ) {
                c = &m->m[i][j];
                vl = c->total_value;
            }
        }
    }

    return c;
}

/* znajdowanie najkrótszej ścieżki - dijsktra */

void shortest_path( maze* m ) {

    /* reset wszystkich wizytacji */
    for ( int i = 0; i < m->m_size; ++i ) {
        for ( int j = 0; j < m->m_size; ++j ) {
            m->m[i][j].visited = 0;
        }
    }

    m->m[0][m->start].total_value = 0;

    cell* current_cell = min_cost( m );

    while ( current_cell != NULL ) {
        // printf( "(%i, %i) ", current_cell->y, current_cell->x );
        current_cell->visited = 1;

        if ( current_cell->y == m->m_size - 1 && current_cell->x == m->finish ) {
            printf("\nSCIEZKA NAJKROTSZEJ SCIEZKI, wspolrzede wierzcholkow na macierzy (od konca):\n");

            cell* cc = current_cell;
            cc->bounds[2] = 2;

            while ( cc != NULL ) {
                cc->label = 'o';
                printf("(%i, %i) ", cc->y, cc->x );

                if ( cc->previous != NULL ) {
                    for( int i = 0; i < 4; ++i ) {
                        if ( cc->near[i] == cc->previous )
                            cc->bounds[i] = 2;
                        if ( cc == cc->previous->near[i] )
                            cc->previous->bounds[i] = 2;
                    }
                } else
                    cc->bounds[0] = 2;
                cc = cc->previous;
            }
            printf("\nNajmniejsza suma wag: %f\n\n", current_cell->total_value );
            
            break;

        }

        // najmniejsze koszty dojścia dla somsiadów

        double new_cost = current_cell->total_value + current_cell->value;
        for( int i = 0; i < 4; ++i ) {
            if ( current_cell->bounds[i] == 0 && current_cell->near[i] != NULL
                && current_cell->near[i]->total_value > new_cost ) {
                    current_cell->near[i]->total_value = new_cost;
                    current_cell->near[i]->previous = current_cell;
                    // printf( "%f ", current_cell->value );
                }
        }

        current_cell = min_cost( m );
    }
}

/* losowe usuwanie ścianek */

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