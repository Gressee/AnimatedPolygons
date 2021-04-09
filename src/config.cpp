#include "config.h"
#include <math.h>

/*
    Screen Coords are only to setup the window
    and the frame buffer

    Room Coords are for the animation of Animation Vertexes
    Origin is in the top left
*/
int screenWidth = 1600;
int screenHeight = 900;
int roomWidth = 1600;
int roomHeight = 900;

// Convert X from Room Coords to GL coords
float convertX(float x) {
    return x/(float)roomWidth * 2.0f - 1.0f;
}

// Convert Y from Room Coords to GL coords
float convertY(float y) {
    return y/(float)roomHeight * 2.0f - 1.0f;
}

// Animation
const int animVertexNum = 3;

// Graphics
int drawVerteciesPerCircle = 12; // Can't be smaler than 5 !!!

// Random Stuff
float clampAngle(float angle) {
    while (angle < 0) angle += 2.0f*M_PI;
    while (angle > 2.0f*M_PI) angle -= 2.0f*M_PI;
    return angle;
}