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
	while(1){
		unsigned int dir;
		print_state(&game_state);
		printf("up[1] down[2] right[3] left[4] : ");
		scanf("%u",&dir);
		move(&game_state,dir);
	}
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
			(*state)[r][c] = ( c << r) ^ (r << c);
		}
	}
}

void move(int (*st)[ROW][COL],unsigned int dir){

	// up down right left
	// 1    2    3    4
	//move left

	int up = dir ==1;
	int down = dir == 2;
	int right = dir == 3;
	int left = dir == 4;

	int cEdge1 = (COL-1) * right;
	int cEdge2 = COL * left ;

	// move horizontal
	for(int r = 0 ; r < ROW ;r++){
		for(
				int c = cEdge1;
				( c < cEdge2 && left) || (c >= cEdge2 && right);
				c += (-1 * right) + (1 * left)
		){
			int *now = &(*st)[r][c];
			if(*now != 0 && c != cEdge1 ){
				for(
						int c2 = cEdge1 ;
						(c2 < c && left) || (c2 >= c && right );
						c2 += (-1 * right) + (1 * left) 
				)if((*st)[r][c2] == 0){
					(*st)[r][c2] = *now;
					*now = 0;
					break;
				}
			}
		}
	}
}

