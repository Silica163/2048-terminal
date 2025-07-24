#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROW 4
#define COL 4
#define WIN 2048

void print_state(int (*state)[ROW][COL],int *score);
void createMap(int (*state)[ROW][COL]);
void move(int (*st)[ROW][COL],unsigned int dir,unsigned int *isMove);
void addEqual(int (*st)[ROW][COL],unsigned int dir,int * score,unsigned int * isMove,int * win);
void newTile(int (*st)[ROW][COL],int score);
int over(int (*st)[ROW][COL]);
void startMsg();

int main(){
    startMsg();
    int game_state[ROW][COL];
    createMap(&game_state);
    int score = 0;
    int win = 0;
    while(1){
        unsigned int dir;
        unsigned int isMove = 0;
        print_state(&game_state,&score);

        if(over(&game_state)){
            int cont;
            printf("game over. [1]Quit, [2]Retry? :");
            fflush(stdout);
            scanf("%d",&cont);
            cont--;
            if(cont%2){
                createMap(&game_state);
                win = score = 0;
                continue;
            }else{
                return 0;
            }
        }

        printf("[1]Up [2]Down [3]Right [4]Left : ");
        fflush(stdout);
        scanf("%u",&dir);

        if(dir > 4 || dir < 1)continue;
        move(&game_state,dir,&isMove);
        addEqual(&game_state,dir,&score,&isMove,&win);
        move(&game_state,dir,&isMove);

        if (win == 1){
            print_state(&game_state,&score);
            printf("you win. Continue[1], Quit[2]? :");
            fflush(stdout);
            int con;
            scanf("%d",&con);
            win = (con - 1) % 2;
            if(win)return 0;
            win += 2;
        }
        if(!isMove)continue;
        newTile(&game_state,score);
    }
    return 0;
}

void startMsg(){
    printf("\n");
    printf(" __   __   _   __\n");
    printf(" __) | /| /_| (__)\n");
    printf("(__  |/_|   | (__)\n\n");

    printf("Enter command to fight,\n");
    printf("Move tiles up down left and right,\n");
    printf("Merge and double when it's neighbor is the same,\n");
    printf("Spawn new one and move again.\n");
    printf("After just one tile reach 2048, you win.\n");
    printf("But when its can't move anymore it's fin.\n\n");

    printf("view source https://github.com/silica163/2048-terminal\n");
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
    int num1 = rand();
    srand(sec * num1 + score);
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

void addEqual(int (*st)[ROW][COL],unsigned int dir,int *score,unsigned int *isMove, int * win){

    // up down right left
    // 1    2    3    4

    int up = dir ==1;
    int down = dir == 2;
    int right = dir == 3;
    int left = dir == 4;

    int vert = up||down;
    int hor = left||right;

    int cEdge1 = (COL - 1) * right;
    int cEdge2 = (COL * left) + right - left ;
    int rEdge1 = (ROW - 1) * down;
    int rEdge2 = (ROW * up) + down - up;

    for(
        int r = rEdge1*vert;
        (r < ROW) * hor || ((r < rEdge2 && up) || (r >= rEdge2 && down)) * vert;
        r += (up-down) + hor
    ){
        for(
            int c = cEdge1*hor;
            ((c < cEdge2 && left) || (c >= cEdge2 && right))*hor || (c < COL)*vert;
            c += (left-right) + vert
        ){
            if((*st)[r][c] == 0)continue;
            if((*st)[r][c] == (*st)[r+(up-down)*vert][c+(left-right)*hor]){
                (*st)[r][c] += (*st)[r+(up-down)*vert][c+(left-right)*hor];
                (*st)[r+(up-down)*vert][c+(left-right)*hor] = 0;
                *score += (*st)[r][c];
                *isMove = 1;
                if((*st)[r][c] == WIN)*win += 1;
            }
        }
    }
}

void print_state(int (*state)[ROW][COL],int *score){

    char bars[][4] = {
        "┌","┬","┐",
        "├","┼","┤",
        "└","┴","┘",
        "─","│"
    };

    printf("\nscore : %d \n",*score);
    for(int r = 0;r < ROW;r++){

        if(r > 0 ) printf("%s",bars[3]);
        if(r == 0) printf("%s",bars[0]);
        for(int c = 0;c<COL;c++){
            for(int i = 0;i<6;i++)printf("%s",bars[9]);
            if(c < COL-1 && r == 0){
                printf("%s",bars[1]);
                continue;
            }
            if(c < COL - 1 ){
                printf("%s",bars[4]);
                continue;
            }
        }
        if(r == 0) printf("%s\n",bars[2]);
        if(r > 0 ) printf("%s\n",bars[5]);

        for(int c = 0 ;c < COL ; c++){
            if((*state)[r][c] == 0){
                printf("%s      ",bars[10]);
                continue;
            }
            printf("%s%6d",bars[10],(*state)[r][c]);
        }
        printf("%s\n",bars[10]);
    }

    printf("%s",bars[6]);
    for(int c = 0;c<COL;c++){
        for(int i = 0;i<6;i++)printf("%s",bars[9]);
        if(c < COL -1 )printf("%s",bars[7]);
    }
    printf("%s\n",bars[8]);
}


void createMap(int (*state)[ROW][COL]){
    for(int r =0;r < ROW;r++)
        for(int c = 0;c < COL;c++)
            (*state)[r][c] = 0;

    newTile(state,3);
    newTile(state,7);
}

void move(int (*st)[ROW][COL],unsigned int dir,unsigned int * isMove){

    // up down right left
    // 1    2    3    4

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
}
