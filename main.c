#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <time.h>

#include "maze.h"

#define BUFF_SIZE 100

static cell maze[MAX_SIZE][MAX_SIZE] = {};
static int maze_size = 10;

static int start_cell = 0, end_cell = 0;

void passage( cell* previous_popped, cell* popped ) {
    if ( previous_popped != NULL ) {
        popped->visited = 1;
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

int main( int argc, char **argv ) {

    /* ---- TU PRZYJMUJE INPUT ---- */

    int repeat;
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

    /* ---- TU GENERUJE LABIRYNT ---- */


    for ( int y = 0; y < maze_size; ++y )
        for ( int x = 0; x < maze_size; ++x ) {

            maze[y][x] = init_cell( y, x, 0 );
            init_nears( &maze[y][x],
                y - 1 >= 0 ? &maze[y - 1][x] : NULL,
                x + 1 < maze_size ? &maze[y][x + 1] : NULL,
                y + 1 < maze_size ? &maze[y + 1][x] : NULL,
                x - 1 >= 0 ? &maze[y][x - 1] : NULL );
        }

    /* ---- LOSOWY PUNKT WEJSCIA I WYJSCIA ---- */

    start_cell = rand() % maze_size;
    end_cell = rand() % maze_size;

    maze[0][start_cell].bounds[0] = 0;
    maze[maze_size - 1][end_cell].bounds[2] = 0;

    /* ---- PODRÓŻ PRZEZ LABIRYNT ---- */

    passage( NULL, &maze[0][start_cell] );

    /* ---- PRZYDZIELANIE LOSOWYCH WAG ---- */

    for ( int y = 0; y < maze_size; ++y ) {
        for ( int x = 0; x < maze_size; ++x ) {
            double weight = (double)( rand() * 10.0 ) / (double)RAND_MAX;
            maze[y][x].value = weight;
        }
    }
    
    print_maze( maze, maze_size );

    return EXIT_SUCCESS;
}