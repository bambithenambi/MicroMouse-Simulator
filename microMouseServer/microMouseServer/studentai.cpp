#include <string>
#include "micromouseserver.h"
void updateCoord(int &x, int &y, int &dir, int a[20][20]) {
    dir = dir%4;
    if (dir==0)
        y++;
    else if (dir==1)
        x++;
    else if (dir==2)
        y--;
    else if (dir==3)
        x--;
    a[x][y] = a[x][y]+1;

}
int timesLeft(int x, int y, int dir, int a[20][20]) {
    dir--;
    dir = dir%4;
    switch(dir) {
        case 0:
            return a[x][y+1];
        case 1:
            return a[x+1][y];
        case 2:
            return a[x][y-1];
        case 3:
            return a[x-1][y];
        default: return 10000;
    }
}
int timesForward(int x, int y, int dir, int a[20][20]) {
    switch(dir) {
        case 0:
            return a[x][y+1];
        case 1:
            return a[x+1][y];
        case 2:
            return a[x][y-1];
        case 3:
            return a[x-1][y];
        default: return 10000;
    }
}
int timesRight(int x, int y, int dir, int a[20][20]) {
    dir++;
    dir = dir%4;
    switch(dir) {
        case 0:
            return a[x][y+1];
        case 1:
            return a[x+1][y];
        case 2:
            return a[x][y-1];
        case 3:
            return a[x-1][y];
        default: return 10000;
    }
}

void microMouseServer::studentAI()
{
/*
 * The following are the eight functions that you can call. Feel free to create your own fuctions as well.
 * Remember that any solution that calls moveForward more than once per call of studentAI() will have points deducted.
 *
 *The following functions return if there is a wall in their respective directions
 *bool isWallLeft();
 *bool isWallRight();
 *bool isWallForward();
 *
 *The following functions move the mouse. Move forward returns if the mouse was able to move forward and can be used for error checking
 *bool moveForward();
 *void turnLeft();
 *void turnRight();
 *
 * The following functions are called when you need to output something to the UI or when you have finished the maze
 * void foundFinish();
 * void printUI(const char *mesg);
*/
    //to check if maze is solved, the mouse must turn right and move forward three times consecutively
    //after three moves and turns, the mouse should have an empty grid spot in front of it, the spot it started on
    /*
    static int rightRotation=0; //will retain value each time function is called
    static bool didMoveForward=false;//indicates if the mouse's last action was moving forward
    static bool hasNotTurned=false;//indicates whether mouse is moving in a 2x2 square or some other space
    */
    /*
    static int moves[3] = { -1, -1, -1}; //initialize moves array
    static int current_move;
    static int move_selector=0; //count moves executed

    if (!isWallForward()&&isWallLeft()) {
        moveForward();
        current_move = 0;
    }
    else if (isWallForward()&&isWallLeft()&&isWallRight()) { //dead end condition
        turnRight();
        turnRight();
        moveForward();
        current_move = 1;
    }
    else if (isWallLeft()) {
        turnRight();
        moveForward();
        current_move = 2;
    }
    else {
        turnLeft();
        moveForward();
        current_move = 3;
    }
    int i = move_selector%3;
    if (move_selector<3) { //initialize position array
        moves[i] = current_move;
    }
    else {
        moves[0]=moves[1]; //drop oldest position
        moves[1]=moves[2]; //shift other two positions 1 index to the left
        moves[2]=current_move; //append new position to the rightmost index
    }
    if ((moves[0]==2)&&(moves[1]==2)&&(moves[2]==2)) { //check if last three moves were (turnRight+moveForward)
        foundFinish();
    }
    move_selector++;
    */
    static int history[20][20];
    static int x=0, y=0, dir=0;
    static int moves[3] = { -1, -1, -1}; //initialize moves array
    static int current_move;
    static int move_selector=0; //count moves executed
    memset(history, 0, sizeof(history));

    if(!isWallLeft() &&
       (timesLeft(x, y, dir, history)<=timesForward(x, y, dir, history)) &&
       !isWallForward() &&
       !isWallRight() &&
       (timesLeft(x, y, dir, history)<=timesRight(x, y, dir, history))){
        current_move = 3;
        turnLeft();
        dir--;
        moveForward();
        updateCoord(x, y, dir, history);
    }
    else if(!isWallForward()){
        current_move = 0;
        moveForward();
        updateCoord(x, y, dir, history);
    }
    else if(!isWallRight()){
        current_move = 2;
        turnRight();
        dir++;
        moveForward();
        updateCoord(x, y, dir, history);
    }
    else{  //dead end, turn around by turning left once so next cycle you go left
        current_move = 1;
        turnLeft();
        dir--;
        updateCoord(x, y, dir, history);
    }
    int i = move_selector%3;
    if (move_selector<3) { //initialize position array
        moves[i] = current_move;
    }
    else {
        moves[0]=moves[1]; //drop oldest position
        moves[1]=moves[2]; //shift other two positions 1 index to the left
        moves[2]=current_move; //append new position to the rightmost index
    }
    if ((moves[0]==2)&&(moves[1]==2)&&(moves[2]==2)) { //check if last three moves were (turnRight+moveForward)
        foundFinish();
    }
    move_selector++;
}

