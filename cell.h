#ifndef _CELL_H_
#define _CELL_H_

typedef struct cell cell;

struct cell {
    int id;             // który to wierzchołek
    char label;         // . - nieodwiedzone, * - część najkrótszej scieżki

    cell* near[4];      // top, right, bottom, left - wierzchołki, z którymi dany wierzchołek jest połączony
    char bounds[4];     // granice ze wszond powszond

    char y, x;          // pozycja w macierzy
    char visited;       // flaga: 0 - not visited, 1 - visited

    double value;       // wygenerowana waga dla pola
    double total_value; // łączna, najkrótsza suma wag aby dotrzeć do (tej) komórki
    cell* previous;     // wskaźnik do poprzedniej komórki (potrzebne przy wyznaczaniu min. ścieżki)
};

cell init_cell( int y, int x, int size );
void init_nears( cell* c, cell* t, cell* r, cell* b, cell* l );
cell* leave( cell* c );

#endif