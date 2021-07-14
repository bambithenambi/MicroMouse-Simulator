
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
    static int rightRotation=0; //will retain value each time function is called
    static bool didMoveForward=false;//indicates if the mouse's last action was moving forward
    static bool hasNotTurned=false;//indicates whether mouse is moving in a 2x2 square or some other space

    if (!isWallForward()&&isWallLeft()) {
        if (didMoveForward) {
            hasNotTurned=true;
        }
        moveForward();
        didMoveForward=true;
    }
    else if (isWallLeft()) {
        turnRight();
        if (rightRotation==0) {
            if (didMoveForward) {
                rightRotation++;
            }
        }
        else {
            if (didMoveForward && !hasNotTurned) {
                rightRotation++;
            }
        }
        didMoveForward=false;
        hasNotTurned=false;
    }
    else {
        turnLeft();
        moveForward();
        rightRotation=0;
        didMoveForward=true;
    }

    if (rightRotation==3) {
        if (!isWallForward()) {
            foundFinish();
        }
        rightRotation=0;
    }


}
