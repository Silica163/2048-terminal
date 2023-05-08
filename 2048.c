#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROW 4
#define COL 4
#define WIN 2048

void print_state(int (*state)[ROW][COL],int *score);
void createMap(int (*state)[ROW][COL]);
void move(int (*st)[ROW][COL],unsigned int dir,unsigned int *isMove);
void addEqual(int (*st)[ROW][COL],unsigned int dir,int * score,int * isMove,int * win);
void newTile(int (*st)[ROW][COL],int score);
int over(int (*st)[ROW][COL]);

int main(){
	int game_state[ROW][COL];
	createMap(&game_state);
	int score = 0;
	int win = 0;
	while(1){
		unsigned int dir;
		unsigned int isMove = 0;
		print_state(&game_state,&score);

		if(over(&game_state)){
			printf("game over\n");
			return 0;
		} 

		printf("up[1] down[2] right[3] left[4] : ");
		scanf("%u",&dir);

		if(dir > 4 || dir < 1)continue;
		move(&game_state,dir,&isMove);
		addEqual(&game_state,dir,&score,&isMove,&win);
		move(&game_state,dir,&isMove);

		if (win == 1){	
			print_state(&game_state,&score);
			printf("you win. Continue[1] , Quid[2] :");
			int con;
			scanf("%d",&con);
			win = (con - 1) % 2;
			if(win)return 0;
		}
		if(!isMove)continue;
		newTile(&game_state,score);
	}
	return 0;
}

void newTile(int (*st)[ROW][COL],int score){

	int zero = 0;
	int pos[ROW*COL][2];
	for(int r = 0;r<ROW;r++)for(int c = 0;c < COL;c++)if((*st)[r][c] == 0){
		pos[zero][0] = r;
		pos[zero][1] = c;
		zero += 1 ;
	}

	time_t sec;
	time(&sec);
	srand(score * sec);
	int num1 = rand();
	srand(sec * num1 * score);
	int posIndex = rand() % zero ;
	srand((sec * num1) ^ ( score * posIndex));
	int tileValue = ((rand() % 2)+1) * 2;

	(*st)[pos[posIndex][0]][pos[posIndex][1]] = 6 - tileValue;

}

int over(int (*st)[ROW][COL]){
	int isOver = 1;
	for(int r = 0;r < ROW ;r++)
		for(int c = 0;c < COL ;c++)
			if(
					(*st)[r][c] == 0 || 
					((*st)[r][c] == (*st)[r][c+1] && c < COL - 1)||
					((*st)[r][c] == (*st)[r+1][c] && r < ROW - 1)
			)
				isOver = 0;
	return isOver;
}

void addEqual(int (*st)[ROW][COL],unsigned int dir,int *score,int *isMove, int * win){

	// up down right left
	// 1    2    3    4
	//move left

	int up = dir ==1;
	int down = dir == 2;
	int right = dir == 3;
	int left = dir == 4;

	int cEdge1 = (COL - 1) * right;
	int cEdge2 = (COL * left) + right - left ;
	int rEdge1 = (ROW - 1) * down;
	int rEdge2 = (ROW * up) + down - up;

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
				*isMove = 1;
				if((*st)[r][c] == WIN)*win += 1;
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
				*isMove = 1;
				if((*st)[r][c] == WIN)*win += 1;
			}
		}
	}
}
void print_state(int (*state)[ROW][COL],int *score){
	printf("score : %d \n+------+------+------+------+\n",*score);
	for(int r = 0;r < ROW;r++){
		for(int c = 0 ;c < COL ; c++){
			if((*state)[r][c] == 0){
				printf("|      ");
				continue;
			}
			printf("|%6d",(*state)[r][c]);
		}
		printf("|\n");
		printf("+------+------+------+------+\n");
	}
}


void createMap(int (*state)[ROW][COL]){
	for(int r =0;r < ROW;r++)
		for(int c = 0;c < COL;c++)
			(*state)[r][c] = 0;

	newTile(state,0);
	newTile(state,3);
}

void move(int (*st)[ROW][COL],unsigned int dir,unsigned int * isMove){

	// up down right left
	// 1    2    3    4
	//move left

	int up = dir ==1;
	int down = dir == 2;
	int right = dir == 3;
	int left = dir == 4;

	int hor = left||right;
	int vert = up||down;

	int cEdge1 = (COL-1) * right;
	int cEdge2 = COL * left ;
	int rEdge1 = (ROW - 1) * down;
	int rEdge2 = ROW * up;

	// move horizon
	for(
		int r = (rEdge1*vert); 
		(r < ROW)*hor || (vert * (r < rEdge2 && up)||(r >= rEdge2 && down));
		r+= (up-down)*vert + hor
	){
		for(
			int c = cEdge1*hor;
			(( c < cEdge2 && left) || (c >= cEdge2 && right)) || (c < COL) * vert;
			c += (left-right)*hor + vert
		){
			int *now = &(*st)[r][c];
			if(
				*now != 0 && 
				((c != cEdge1 && hor) || (r != rEdge1 && vert))
			)for(
				int i = cEdge1*hor + rEdge1*vert ;
				(i * left) + (c * right) + (i * up) + (r * down) < (i * right) + (c * left) + (i * down) + (r * up);
				i += (left-right) * hor + (up - down)*vert
			)if((*st)[i*vert + r*hor][i*hor + c*vert] == 0){
				(*st)[i*vert + r*hor][i*hor + c*vert] = *now;
				*now = 0;
				*isMove = 1;
				break;
			};
		}
	}

	// move vertical
	/*for(int c = 0; c < COL;c++){
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
				*isMove = 1;
				break;
			};
		}
	}*/
}

