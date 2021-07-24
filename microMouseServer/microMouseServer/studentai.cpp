
#include "micromouseserver.h"

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
    static int state = 0;
    if(!isWallLeft()){
        if(isWallRight() && !isWallForward() && state==0) //right entry, first cell
            state = 1;
        if(!isWallRight() || isWallForward()) //impossible states for solution, reset
            state = 0;
        turnLeft();
        moveForward();
    }
    else if(!isWallForward()){
        if(state == 0 && !isWallRight()) //Left entry, first cell
            state = 2;
        if(isWallRight()){ //impossible state for solution, reset.
            state = 0;
        }
        moveForward();
    }
    else if(!isWallRight()){
        if(state >0)
            state += 2;
        turnRight();
        moveForward();
    }
    else{  //dead end, turn around by turning left once so next cycle you go left
        state = 0;
        turnLeft();
    }
    if(state >= 6)
        foundFinish();
}
