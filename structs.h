/*Rodrigo Kovalski de Araújo. GRR20183146*/
#ifndef __STRUCTS__
#define __STRUCTS__

typedef struct t_game{
	int lin;
	int col;
	int** map;
}GAME;

typedef struct t_cannon{
	int lin;
	int col;
	int poslin;
	int poscol;
	int shell;
	unsigned long int points;
	int** shape;
}CANNON;

typedef struct t_barrier{
	int lin;
	int col;
	int poslin;
	int poscol;
	int** shape;

}BARRIER;

typedef struct t_invader{
	int id;
	int lin;
	int col;
	int poslin;
	int poscol;
	int state;
	int bomb;
	int** shape;
	int** explosion;
}INVADER;

#endif
