#include "../include/snek.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <time.h>

#define MOVEMENT_TIMEOUT 150 

// TODO: Enable drawing a smaller box as the game window, as terminal emulators can be quite large

int main() {
    srand(time(0));
    setlocale( LC_ALL, "en_US.UTF-8" );
    initscr(); cbreak(); noecho(); nonl(); intrflush( stdscr, FALSE ); keypad( stdscr, TRUE ); curs_set( 0 ); 
    // box(stdscr, 0, 0);
    timeout( MOVEMENT_TIMEOUT );

    snek* head = init_snek( LINES/2, COLS/2, NULL, NULL );

    add_apple( head );

    draw_snek( head );
    direction d = M_RIGHT;
    direction prev_d = M_RIGHT;
    refresh();
    char input = 1;
    while( (input = getch()) != 'q' ) {
        switch( input ) {
            case 5: 
                d = M_RIGHT;
                break;
            case 3:
                d = M_UP;
                break;
            case 4:
                d = M_LEFT;
                break;
            case 2:
                d = M_DOWN;
                break;
            default:
                break;
        }
        if( (d ^ prev_d) != 1 || d == prev_d ) {
            prev_d = d;
            if(move_snek( head, d )) 
                break;
        } else if( move_snek( head, prev_d )) 
            break;
        draw_snek( head );
        refresh();
    }
    endwin();
    snek* s = head->next;
    int score = 0;
    while( s ) {
        score++;
        s = s->next;
    }
    if( input != 'q' )
        printf("Oh no! You died! :c\n");
    printf("Score: %d\n", score);
    clean_snek(head);
}