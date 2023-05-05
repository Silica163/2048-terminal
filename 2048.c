#include <stdio.h>

#define ROW 4
#define COL 4

void print_state(int (*state)[ROW][COL]);
void createMap(int (*state)[ROW][COL]);
void move(int (*st)[ROW][COL],unsigned int dir);

int main(){
	int game_state[ROW][COL];
	createMap(&game_state);
	print_state(&game_state);
	move(&game_state,4);
	print_state(&game_state);
	move(&game_state,3);
	print_state(&game_state);
	return 0;
	return 0;
}

void print_state(int (*state)[ROW][COL]){
	printf("+------+------+------+------+\n");
	for(int r = 0;r < ROW;r++){
		for(int c = 0 ;c < COL ; c++){
			printf("|%6d",(*state)[r][c]);
		}
		printf("|\n");
		printf("+------+------+------+------+\n");
	}
}


void createMap(int (*state)[ROW][COL]){
	for(int r = 0;r < ROW;r++){
		for( int c = 0;c < COL;c++ ){
			(*state)[r][c] = (c == r)*((c+1) >> 1)*2;
		}
	}
}

void move(int (*st)[ROW][COL],unsigned int dir){

	// up down right left
	// 1    2    3    4
	//move left

	for(int r = 0 ; r < ROW && dir == 4;r++){
		for(int c = 0;c < COL;c++){
			if((*st)[r][c] != 0 && c != 0){
				for(int c2 = 0;c2 < COL;c2++)if((*st)[r][c2] == 0){
					(*st)[r][c2] = (*st)[r][c];
					(*st)[r][c] = 0;
					break;
				}
			}
		}
	}
	for(int r = 0 ; r < ROW && dir == 3;r++){
		for(int c = COL-1 ; c >= 0;c--){
			if((*st)[r][c] != 0 && c != COL-1){
				for(int c2 = COL-1 ; c2 >=0 ;c2--)if((*st)[r][c2] == 0){
					(*st)[r][c2] = (*st)[r][c];
					(*st)[r][c] = 0;
					break;
				}
			}
		}
	}
}

