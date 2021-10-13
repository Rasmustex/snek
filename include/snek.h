#ifndef SNEK_H
#define SNEK_H

#ifdef __cplusplus
extern "C" {
#endif 

    typedef struct sn snek;
    struct sn {
        int x, y;
        snek *next, *prev;
    };

    typedef enum {
        M_UP = 0b00,
        M_DOWN = 0b01,
        M_RIGHT = 0b10,
        M_LEFT = 0b11
    } direction;

    snek* init_snek( int y, int x, snek* next, snek* prev );
    void clean_snek( snek* head );
    void draw_snek( snek* head );
    int move_snek( snek* head, direction d );
    void add_apple( snek* head );

#ifdef __cplusplus
}
#endif
#endif 