/*Rodrigo Kovalski de Araújo. GRR20183146*/
#include "functions.h"

/********FUNÇÕES PARA CRIAÇÃO E MANIPULAÇÃO DA TELA DO JOGO*********/

void create_game(GAME * screen){
	int i,j;
	screen->lin = NLIN;
	screen->col = NCOL; 
	screen->map = (int **) malloc(screen->lin * sizeof(int*));
	for(i = 0; i < screen->lin; i++) 
		screen->map[i] = (int *) malloc(screen->col * sizeof(int));	

	for(i = 0; i < screen->lin; i++){
		for(j = 0; j < screen->col; j++){
			if(i == 0 || i == screen->lin-1 || j == 0 || j == screen->col-1){
				screen->map[i][j] = -1;
			}else{
				screen->map[i][j] = 0;
			}
		}
	}
}
	
void load_game(GAME * screen, CANNON * player, BARRIER * barrier, INVADER *  alien){
	int i,j,k,l; /*Indices*/

/**************criando canhão**************/		
	create_cannon(player);
	player->poslin = screen->lin-3;
	player->poscol = (screen->col/2)-2;
	player->points = 0;
	k = -1; l = 0;
	for(i = player->poslin; i < player->poslin + player->lin; i++){
		k+=1;
		l=0;
		for(j = player->poscol; j < player->poscol + player->col; j++){
			screen->map[i][j] = player->shape[k][l];
			l+=1;
		}
	}

/*************criando barreira************/
	create_barrier(barrier, screen);
	barrier->poslin = screen->lin-8;
	int space = 14;
	barrier->poscol = screen->col - screen->col + space;
	while(barrier->poscol <= screen->col - space){
		k = -1; l = 0;
		for(i = barrier->poslin; i < barrier->poslin + barrier->lin; i++){
			k+=1;
			l=0;
			for(j = barrier->poscol; j < barrier->poscol + barrier->col; j++){
				screen->map[i][j] = barrier->shape[k][l];
				l+=1;
			}
		}
		
		barrier->poscol = barrier->poscol + barrier->col + space;		
	}

/*************criando invasores*************/
	create_invader(alien);
}


void update_screen(GAME * screen,CANNON * player, INVADER * alien){
	int i,j,k,l,n;
	for(i = 1; i < screen->lin - 2; i++){
		for(j = 1; j < screen->col-1; j++){
			if(screen->map[i][j] == 5){
				if(screen->map[i-1][j] == 0){	
					screen->map[i-1][j] = 5;
					screen->map[i][j] = 0;
				}else if(screen->map[i-1][j] == -1){
					screen->map[i][j] = 0;
				}else{
					screen->map[i-1][j] = 0;
					screen->map[i][j] = 0;
				}
			}
		}		
	}
	if(alien->state != END)
		show_mothership(screen,alien,player);

	
	n = 1;
	while(n < 12){
			k = -1; l = 0;
			for(i = alien[n].poslin; i < alien[n].poslin + alien[n].lin; i++){
				k+=1;
				l=0;
				for(j = alien[n].poscol; j < alien[n].poscol + alien[n].col; j++){
					screen->map[i][j] = alien[n].shape[k][l];
					l+=1;
				}
			}
		n++;		
	}


		
}

void print_screen(GAME * screen){
	int i,j,index;
	for(i = 0; i < screen->lin; i++){
		for(j = 0; j < screen->col; j++){
			index = screen->map[i][j];
			switch(index){
				case -1:
					printw("#");
				break;
				case 0:
					printw(" ");
				break;
				case 1:
					printw("M");
				break;
				case 2:
					printw("/");
				break;
				case 3:
					printw("^");
				break;
				case 4:
					printw("\\");
				break;
				case 5:
					printw("|");
				break;
				case 6:
					printw("$");
				break;
				case 7:
					printw("A");
				break;
				case 8:
					printw("_");
				break;
				case 9:
					printw("-");
				break;
				case 10:
					printw("d");
				break;
				case 11:
					printw("b");
				break;
				case 12:
					printw("n");
				break;
				case 13:
					printw("m");
				break;
				case 14:
					printw("}");
				break;
				case 15:
					printw("{");
				break;
				case 16:
					printw("W");
				break;
				case 17:
					printw(".");
				break;
				case 18:
					printw("v");
				break;
				case 19:
					printw("X");
				break;
				case 20:
					printw("'");
				break;
				case 21:
					printw("o");
				break;
				case 22:
					printw(",");
				break;
				case 23:
					printw("a");
				break;
				case 24:
					printw(">");
				break;	
				case 25:
					printw("<");
				break;
				default:
					printw(" ");
				break;	
			}
		}
		printw("\n");
	}
}

/****************CRIANÇÃO E MANIPULAÇÃO DO CANHÃO**********************/

void create_cannon(CANNON * player){
	int i;

	player->lin = 2;
	player->col = 5;
	player->points = 0;
	player->shell = 5;
	player->shape = (int **) malloc(player->lin * sizeof(int *));

	for(i = 0; i < player->lin; i++) 
		player->shape[i] = (int *) malloc(player->col * sizeof(int));

	player->shape[0][0] = 0;
	player->shape[0][1] = 2;
	player->shape[0][2] = 3;
	player->shape[0][3] = 4;
	player->shape[0][4] = 0;
	player->shape[1][0] = 1;
	player->shape[1][1] = 1;
	player->shape[1][2] = 1;
	player->shape[1][3] = 1;
	player->shape[1][4] = 1;
}

void move_cannon_right(GAME * screen, CANNON * player, int key){
	int i,j,k,l;

	if(player->poscol <= (screen->col - player->col - 2)){		
		for(i = player->poslin; i < player->poslin + player->lin; i++){
			for(j = player->poscol; j < player->poscol + player->col; j++)
				screen->map[i][j] = 0;
		}

		player->poscol = player->poscol + 1; /*move*/
		k = -1; l = 0;
		for(i = player->poslin; i < player->poslin + player->lin; i++){
			k+=1;
			l=0;
			for(j = player->poscol; j < player->poscol + player->col; j++){
				screen->map[i][j] = player->shape[k][l];
				l+=1;
			}
		}
	}
}


void move_cannon_left(GAME * screen, CANNON * player, int key){
	int i,j,k,l;

	if(player->poscol >= (screen->col - NCOL + 2)){
		for(i = player->poslin; i < player->poslin + player->lin; i++){
			for(j = player->poscol; j < player->poscol + player->col; j++)
				screen->map[i][j] = 0;
		}

		player->poscol = player->poscol - 1; /*move*/
		k = -1; l = 0;
		for(i = player->poslin; i < player->poslin + player->lin; i++){
			k+=1;
			l=0;
			for(j = player->poscol; j < player->poscol + player->col; j++){	
				screen->map[i][j] = player->shape[k][l];
				l+=1;
			}
		}
	}
}

void cannon_shot(GAME * screen, CANNON * player){
	int x,y;
	x = player->poslin-1;
	y = player->poscol+2;
	screen->map[x][y] = player->shell;
}


/****************BARREIRA********************/
void create_barrier(BARRIER * barrier, GAME * screen){
	int i;

	barrier->lin = 3;
	barrier->col = 7;
	barrier->shape = (int **) malloc(barrier->lin * sizeof(int **));
	
	for(i = 0; i < barrier->lin; i++){
		barrier->shape[i] = (int *) malloc (barrier->col * sizeof(int *));
	}
	
	barrier->shape[0][0] = 0; 
	barrier->shape[0][1] = 7; 
	barrier->shape[0][2] = 1; 
	barrier->shape[0][3] = 1; 
	barrier->shape[0][4] = 1; 
	barrier->shape[0][5] = 7; 
	barrier->shape[0][6] = 0; 
	barrier->shape[1][0] = 1; 
	barrier->shape[1][1] = 1; 
	barrier->shape[1][2] = 1; 
	barrier->shape[1][3] = 1; 
	barrier->shape[1][4] = 1; 
	barrier->shape[1][5] = 1; 
	barrier->shape[1][6] = 1; 
	barrier->shape[2][0] = 1; 
	barrier->shape[2][1] = 1; 
	barrier->shape[2][2] = 0; 
	barrier->shape[2][3] = 0; 
	barrier->shape[2][4] = 0; 
	barrier->shape[2][5] = 1; 
	barrier->shape[2][6] = 1;
}




/*************CRIAÇÃO E MANIPULAÇÃO DE INVASORES************/

void create_invader(INVADER * alien){
	int i,j,y;
	y = 6;
	while(i < 56){
	if(i == 0){  /*MOTHERSHIP*/
		alien[i].id = i;
		alien[i].lin = 3;
		alien[i].col = 9;
		alien[i].bomb = 23;
		alien[i].state = ALIVE; /*alive*/
		alien[i].shape = (int **) malloc(alien[i].lin * sizeof(int **));
	
		for(j = 0; j < alien[i].lin; j++)
			alien[i].shape[j] = (int *) malloc(alien[i].col * sizeof(int *));
		
		alien[i].shape[0][0] = 0;
		alien[i].shape[0][1] = 2;
		alien[i].shape[0][2] = 1;
		alien[i].shape[0][3] = 1;
		alien[i].shape[0][4] = 1;
		alien[i].shape[0][5] = 1;
		alien[i].shape[0][6] = 1;
		alien[i].shape[0][7] = 4;
		alien[i].shape[0][8] = 0;
		alien[i].shape[1][0] = 7;
		alien[i].shape[1][1] = 1;
		alien[i].shape[1][2] = 21;
		alien[i].shape[1][3] = 1;
		alien[i].shape[1][4] = 21;
		alien[i].shape[1][5] = 1;
		alien[i].shape[1][6] = 21;
		alien[i].shape[1][7] = 1;
		alien[i].shape[1][8] = 7;
		alien[i].shape[2][0] = 0;
		alien[i].shape[2][1] = 4;
		alien[i].shape[2][2] = 2;
		alien[i].shape[2][3] = 20;
		alien[i].shape[2][4] = 9;
		alien[i].shape[2][5] = 20;
		alien[i].shape[2][6] = 4;
		alien[i].shape[2][7] = 2;
		alien[i].shape[2][8] = 0;
		
		alien[i].poslin = 2;
		alien[i].poscol = 1;
		

		alien[i].explosion = (int **) malloc(alien[i].lin * sizeof(int **));
		for(j = 0; j < alien[i].lin; j++)
			alien[i].explosion[j] = (int *) malloc(alien[i].col * sizeof(int *));
		
		alien[i].explosion[0][0] = 0;	
		alien[i].explosion[0][1] = 4;	
		alien[i].explosion[0][2] = 4;	
		alien[i].explosion[0][3] = 4;	
		alien[i].explosion[0][4] = 16;	
		alien[i].explosion[0][5] = 2;	
		alien[i].explosion[0][6] = 2;	
		alien[i].explosion[0][7] = 2;	
		alien[i].explosion[0][8] = 0;	
		alien[i].explosion[1][0] = 9;	
		alien[i].explosion[1][1] = 24;	
		alien[i].explosion[1][2] = 24;	
		alien[i].explosion[1][3] = 24;	
		alien[i].explosion[1][4] = 19;	
		alien[i].explosion[1][5] = 25;	
		alien[i].explosion[1][6] = 25;	
		alien[i].explosion[1][7] = 25;	
		alien[i].explosion[1][8] = 9;	
		alien[i].explosion[2][0] = 0;	
		alien[i].explosion[2][1] = 2;	
		alien[i].explosion[2][2] = 2;	
		alien[i].explosion[2][3] = 2;	
		alien[i].explosion[2][4] = 1;	
		alien[i].explosion[2][5] = 4;	
		alien[i].explosion[2][6] = 4;	
		alien[i].explosion[2][7] = 4;	
		alien[i].explosion[2][8] = 0;	
	
	}

	if(i > 0 && i < 12){ /*alien_nv_1*/
		alien[i].id = i;
		alien[i].lin = 3;
		alien[i].col = 5;
		alien[i].bomb = 6;
		alien[i].state = ALIVE;
		alien[i].shape = (int **) malloc(alien[i].lin * sizeof(int **));
		
		for(j = 0; j < alien[i].col; j++)
			alien[i].shape[j] = (int *) malloc(alien[i].col * sizeof(int *));

		alien[i].shape[0][0] = 0;
		alien[i].shape[0][1] = 12;
		alien[i].shape[0][2] = 13;
		alien[i].shape[0][3] = 12;
		alien[i].shape[0][4] = 0;
		alien[i].shape[1][0] = 10;	
		alien[i].shape[1][1] = 11;	
		alien[i].shape[1][2] = 1;	
		alien[i].shape[1][3] = 10;	
		alien[i].shape[1][4] = 11;	
		alien[i].shape[2][0] = 8;	
		alien[i].shape[2][1] = 2;	
		alien[i].shape[2][2] = 9;	
		alien[i].shape[2][3] = 4;	
		alien[i].shape[2][4] = 8;
	
		alien[i].poslin = 7;
		alien[i].poscol = y;
		y+=7;
			
	}
	if(i > 22 && i < 45){/*alien_nv_2*/

	}
	if(i > 44 && i < 56){/*alien_nv_3*/

	}

	i++;
	}

}

void show_mothership(GAME * screen, INVADER * alien, CANNON * player){
	int i,j,k,l;	
	
	for(i = alien[0].poscol; i < alien[0].poscol + alien[0].col + 1; i++){
		if(screen->map[alien[0].poslin + alien[0].lin][i] == 5 && alien[0].state == ALIVE){
			alien[0].state = EXPLODING;
			player->points = player->points + 10;
		}
	}	


	if(alien[0].poscol < (screen->col - alien[0].col - 2) && (alien[0].state == ALIVE)){		
		for(i = alien[0].poslin; i < alien[0].poslin + alien[0].lin; i++){
			for(j = alien[0].poscol; j < alien[0].poscol + alien[0].col; j++){
				screen->map[i][j] = 0;
			}
		}
		
		if(alien[0].poscol < (screen->col - alien[0].col)){
			alien[0].poscol = alien[0].poscol + 1; /*move*/
			k = -1; l = 0;
			for(i = alien[0].poslin; i < alien[0].poslin + alien[0].lin; i++){
				k+=1;
				l=0;
				for(j = alien[0].poscol; j < alien[0].poscol + alien[0].col; j++){
					screen->map[i][j] = alien[0].shape[k][l];
					l+=1;
				}
			}
		}	
	}else if(alien[0].state == EXPLODING){
		for(i = alien[0].poslin; i < alien[0].poslin + alien[0].lin; i++){
			for(j = alien[0].poscol; j < alien[0].poscol + alien[0].col; j++)
				screen->map[i][j] = 0;
		}
		
		k = -1; l = 0;
		for(i = alien[0].poslin; i < alien[0].poslin + alien[0].lin; i++){
			k+=1;
			l=0;
			for(j = alien[0].poscol; j < alien[0].poscol + alien[0].col; j++){
				screen->map[i][j] = alien[0].explosion[k][l];
				l+=1;
			}
		}
		alien[0].state = DEAD;
	}else if(alien[0].state == DEAD){
		for(i = alien[0].poslin; i < alien[0].poslin + alien[0].lin; i++){
			for(j = alien[0].poscol; j < alien[0].poscol + alien[0].col; j++)
				screen->map[i][j] = 0;
		alien[0].state = END;
		}
	}else{
		for(i = alien[0].poslin; i < alien[0].poslin + alien[0].lin; i++){
			for(j = alien[0].poscol; j < alien[0].poscol + alien[0].col; j++)
				screen->map[i][j] = 0;
		}
		alien[0].state = END;
	}
}
