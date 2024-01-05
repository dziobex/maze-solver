#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#include "maze.h"

/* generowanie labiryntu */

void init_maze( maze* m, int size ) {
    m->m_size = size;

    m->start = 0;
    m->finish = 0;

    for ( int y = 0; y < MAX_SIZE; ++y )
        for ( int x = 0; x < MAX_SIZE; ++x ) {
            m->m[y][x] = init_cell( y, x, size );
            init_nears( &m->m[y][x],
                y - 1 >= 0 ? &m->m[y - 1][x] : NULL,
                x + 1 < size ? &m->m[y][x + 1] : NULL,
                y + 1 < size ? &m->m[y + 1][x] : NULL,
                x - 1 >= 0 ? &m->m[y][x - 1] : NULL );
        }
}

/* ustawienie wygenerowanie już punktu wejścia i wyjścia labiryntu */

void set_maze_entries( maze* m, int start, int finish ) {
    m->start = start;
    m->finish = finish;

    m->m[0][start].bounds[0] = 0;
    m->m[m->m_size - 1][finish].bounds[2] = 0;
}

/* wypis labiryntu na konsoli */

void print_maze( maze* m ) {

    int size = m->m_size;

    /* --- GORNA BARIERKA ---- */

    /* wyswietlanie gornych barierek komorek */
    for ( int x = 0; x < size; ++ x) {
        /* barierka nad lewa scianka przed komorka */
        printf ("%s ", "#");
        /* barierka nad komorka */
        printf ("%s ", m->m[0][x].bounds[0] == 1 ? "#" : ( m->m[0][x].bounds[0] == 2 ? "o" : " " ) );
    }
    /* barierka od skrajnej prawej + odstep na nowy wiersz z komorkami */
    printf("#\n");

    /* ---- KOMORKI LABIRYNTU ---- */

    for ( int y = 0; y < size; ++y ) {
        for ( int x = 0; x < size; ++ x) {
            if ( m->m[y][x].bounds[3] == 1 )
                printf("# ");
            else if ( m->m[y][x].bounds[3] == 2 )
                printf("o ");
            else
                printf("  ");
            printf("%c ", m->m[y][x].label);
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
            printf ("%s ", m->m[ y ][x].bounds[2] == 1 ? "#" : ( m->m[ y ][x].bounds[2] == 2 ? "o" : " " ));
        }
        /* barierka od skrajnej prawej + odstep na nowy wiersz z komorkami */
        printf("#\n");
    }
}