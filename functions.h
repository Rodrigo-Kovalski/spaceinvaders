/*Rodrigo Kovalski de Araújo*/
#ifndef __FUNCTIONS__
#define __FUNCTIONS_
#define NLIN 38
#define NCOL 100
#define MAX_INVADERS 56
#define	ALIVE 0
#define EXPLODING 1
#define DEAD 2 
#define END 3 
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <ncurses.h>
#include "structs.h"

void create_game(GAME *);
void load_game(GAME *, CANNON*, BARRIER*, INVADER *);
void print_screen(GAME *);
void update_screen(GAME *,CANNON *,INVADER *);

void create_cannon(CANNON *);
void move_cannon_right(GAME *,CANNON *,int);
void move_cannon_left(GAME *,CANNON *,int);
void cannon_shot(GAME *, CANNON *);


void create_barrier(BARRIER *, GAME *);

void create_invader(INVADER *);
void show_mothership(GAME *, INVADER *, CANNON *);

#endif
