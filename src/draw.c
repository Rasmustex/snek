#include "../include/snek.h"
#include <curses.h>
#include <stdlib.h>

void draw_snek( snek* head ) {
    move( head->y, head->x );
    addch('@');
    snek* s = head->next;
    snek* next;
    while( s ) {
        next = s->next;
        move( s->y, s->x );
        addch('#');
        s = next;
    }
    return;
}

void add_apple( snek* head ) {
    snek* s = head;
    int x, y;
    bool is_in_snek = true;
    while( is_in_snek ) {
        is_in_snek = false;
        s = head;
        x = (rand() % COLS);
        y = (rand() % LINES);
        while( s ) {
            if( y == s->y && x == s->x ) {
                is_in_snek = true;
                break;
            }
            s = s->next;
        }
    }
    move( y, x );
    addch('O');
    return;
}