#include "../include/snek.h"
#include <stdlib.h>
#include <curses.h>
#include <stdbool.h>

snek* init_snek( int y, int x, snek* next, snek* prev ) {
    snek* s = (snek*)malloc( sizeof(snek) );
    s->y = y;
    s->x = x;
    s->next = next;
    s->prev = prev;
    return s;
}

void clean_snek( snek* head ) {
    snek* s = head;
    snek* next;
    while( s ) {
        next = s->next;
        free( s );
        s = next;
    }
    return;
}

void grow_snek( snek* head ) {
    snek* tail = head;
    while( tail->next ) {
        tail = tail->next;
    } 
    tail->next = init_snek( tail->y, tail->x, NULL, tail );
    return;
}

int check_collission( snek* head ) {
    if( head->x < 0 || head->x >= COLS )
        return 1;
    if( head->y < 0 || head->y >= LINES )
        return 1;
    move(head->y, head->x);
    char object_at_head = inch();
    if( object_at_head == '#' )
        return 1;
    else if( object_at_head == 'O' )
        return 2;
    return 0;
}

int move_snek( snek* head, direction d ) {
    snek* s = head;
    while( s->next ) {
        s = s->next;
    }
    move(s->y, s->x);
    addch(' ');
    while( s->prev ) {
        s->y = s->prev->y;
        s->x = s->prev->x;
        s = s->prev;
    }
    switch( d ) {
        case M_UP:
            head->y--;
            break;
        case M_RIGHT:
            head->x++;
            break;
        case M_DOWN:
            head->y++;
            break;
        case M_LEFT:
            head->x--;
            break;
    }
    int col;
    if((col = check_collission( head )) == 1)
        return 1;
    else if( col == 2 ) {
        grow_snek( head );
        add_apple( head );
    }

    return 0;
}