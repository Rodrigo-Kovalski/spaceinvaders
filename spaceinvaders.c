/*Rodrigo Kovalski Kovalski de Araújo*/
#include "functions.h"

int main(void){
	initscr();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	
	GAME screen;
	CANNON player;
	BARRIER barrier;
	INVADER alien[MAX_INVADERS];
	

	create_game(&screen);
	load_game(&screen,&player,&barrier,alien);	
	print_screen(&screen);				
	
	int key;
	while((key = getch()) != 'q'){
		clear();
		if(key == KEY_RIGHT){
			move_cannon_right(&screen,&player,key);
		}else if(key == KEY_LEFT){
			move_cannon_left(&screen,&player,key);
		}else if(key == ' '){
			cannon_shot(&screen,&player);
		}
		update_screen(&screen,&player,alien);
		print_screen(&screen);
		usleep(45000);
	}

	endwin();
return 0;
}
