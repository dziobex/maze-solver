#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <time.h>

#include "maze.h"
#include "cell.h"
#include "solver.h"

#define BUFF_SIZE 100

int main( int argc, char **argv ) {

    /* ---- TU PRZYJMUJE INPUT ---- */

    int repeat;
    int maze_size = 10;
    char buff[ BUFF_SIZE ];

    do {
        maze_size = 0;
        repeat = 0;

        printf( "Podaj rozmiar kwadratowego labiryntu (5 <= rozmiar <= 10):\n");
        if ( fgets(buff, BUFF_SIZE, stdin) == NULL)
            return EXIT_FAILURE;

        for ( int i = 0; i < strlen( buff ); ++i )
            if ( isdigit( buff[i] ) )
                maze_size = maze_size * 10 + ( buff[i] - '0' );
            else if ( buff[i] != '\n' && buff[i] != '\0' ) {
                repeat = 1;
                break;
            }

    } while ( repeat == 1 || !( maze_size >= 5 && maze_size <= 10 ) );

    srand( time( NULL ));

    /* ---- WYGENEROWANIE LABIRYNTU ---- */

    maze m;
    init_maze( &m, maze_size );

    /* ---- LOSOWY PUNKT WEJSCIA I WYJSCIA ---- */

    int start = rand() % maze_size;
    int finish = rand() % maze_size;
    
    set_maze_entries( &m, start, finish );

    /* ---- PODRÓŻ PRZEZ LABIRYNT ---- */

    passage( NULL, &(m.m[0][start]) );

    /* ---- PRZYDZIELANIE LOSOWYCH WAG ---- */

    for ( int y = 0; y < maze_size; ++y ) {
        for ( int x = 0; x < maze_size; ++x ) {
            double weight = ((double)rand() / RAND_MAX) * 10.0;
            m.m[y][x].value = weight;
        }
    }

    print_maze( &m );
    shortest_path( &m );
    print_maze( &m );

    return EXIT_SUCCESS;
}