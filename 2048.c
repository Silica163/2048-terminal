#include <stdio.h>

#define ROW 4
#define COL 4

void print_state(int (*state)[ROW][COL],int *score);
void createMap(int (*state)[ROW][COL]);
void move(int (*st)[ROW][COL],unsigned int dir);
void addEqual(int (*st)[ROW][COL],unsigned int dir,int * score);
void newTile(int (*st)[ROW][COL]);
int over(int (*st)[ROW][COL]);

int main(){
	int game_state[ROW][COL];
	createMap(&game_state);
	int score = 0;
	while(1){
		unsigned int dir;
		print_state(&game_state,&score);
		printf("up[1] down[2] right[3] left[4] : ");
		scanf("%u",&dir);

		move(&game_state,dir);
		print_state(&game_state,&score);
		addEqual(&game_state,dir,&score);
		print_state(&game_state,&score);
		move(&game_state,dir);
		if(over(&game_state)){
			printf("game over\n");
			return 0;
		} else {
			newTile(&game_state);
		}
	}
	return 0;
}

void newTile(int (*st)[ROW][COL]){
	for(int r = 0;r<ROW;r++)for(int c = 0;c < COL;c++)if((*st)[r][c] == 0){
		if(r == c && c == 0)(*st)[r][c] = 2;
	}
}

int over(int (*st)[ROW][COL]){
	int isOver = 1;
	for(int r = 0;r < ROW ;r++)
		for(int c = 0;c < COL;c++)
			if(
					(*st)[r][c] == 0 || 
					(*st)[r][c] == (*st)[r][c+1]||
					(*st)[r][c] == (*st)[r+1][c]
			)
				isOver = 0;
	return isOver;
}

void addEqual(int (*st)[ROW][COL],unsigned int dir,int *score){

	// up down right left
	// 1    2    3    4
	//move left

	int up = dir ==1;
	int down = dir == 2;
	int right = dir == 3;
	int left = dir == 4;

	int cEdge1 = (COL - 1) * right;
	int cEdge2 = (COL * left) - left + right ;
	int rEdge1 = (ROW - 1) * down;
	int rEdge2 = (ROW * up) - up + down;

	// add horizon
	for(int r = 0;r < ROW;r++){
		for(
			int c = cEdge1;
			(c < cEdge2 && left) || (c >= cEdge2 && right);
			c += left-right
		){
			if((*st)[r][c] == 0)continue;
			if((*st)[r][c] == (*st)[r][c+left-right]){
				(*st)[r][c] += (*st)[r][c+left-right];
				(*st)[r][c+left-right] = 0;
				*score += (*st)[r][c];
			}
		}
	}

	// add vertical
	for(int c = 0;c < COL; c++){
		for(
			int r = rEdge1;
			(r < rEdge2 && up) || (r >= rEdge2 && down);
			r += up - down
		){
			if((*st)[r][c] == 0)continue;
			if((*st)[r][c] == (*st)[r+up-down][c]){
				(*st)[r][c] += (*st)[r+up-down][c];
				(*st)[r+up-down][c] = 0;
				*score += (*st)[r][c];
			}
		}
	}
}
void print_state(int (*state)[ROW][COL],int *score){
	printf("score : %d \n+------+------+------+------+\n",*score);
	for(int r = 0;r < ROW;r++){
		for(int c = 0 ;c < COL ; c++){
			printf("|%6d",(*state)[r][c]);
		}
		printf("|\n");
		printf("+------+------+------+------+\n");
	}
}


void createMap(int (*state)[ROW][COL]){
	int map[ROW][COL];
	for(int r =0;r < ROW;r++)
		for(int c = 0;c < COL;c++)
			map[r][c] = 0;
	map[1][1] = 2;
	map[2][2] = 2;
	for(int r = 0;r < ROW;r++){
		for( int c = 0;c < COL;c++ ){
			(*state)[r][c] = map[r][c];
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
	int rEdge1 = (ROW - 1) * down;
	int rEdge2 = ROW * up;

	// move horizon
	for(int r = 0 ; r < ROW ;r++){
		for(
			int c = cEdge1;
			( c < cEdge2 && left) || (c >= cEdge2 && right);
			c += (-1 * right) + (1 * left)
		){
			int *now = &(*st)[r][c];
			if(*now != 0 && c != cEdge1 )for(
				int c2 = cEdge1 ;
				(c2 *left) + (c * right) < (c2 * right) + (c * left);
				c2 += (-1 * right) + (1 * left) 
			)if((*st)[r][c2] == 0){
				(*st)[r][c2] = *now;
				*now = 0;
				break;
			};
		}
	}

	// move vertical
	for(int c = 0; c < COL;c++){
		for(
			int r = rEdge1 ;
			( r < rEdge2 && up) || (r >= rEdge2 && down);
			r+= ( -1 * down) + ( 1 * up )
		){
			int *now = &(*st)[r][c];
			if(*now != 0 && r != rEdge1)for(
				int r2 = rEdge1;
				(r2 * up) + (r * down) < (r2 * down) + (r * up);
				r2 += (-1 * down) + (1 * up)
			)if((*st)[r2][c] == 0){
				(*st)[r2][c] = *now;
				*now = 0;
				break;
			};
		}
	}
}

