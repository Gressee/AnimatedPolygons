// Standard stuff
#include <iostream>
#include <math.h>

// Local Includes
#include "points.h"


// Constructor
Point::Point(float startX, float startY, float startDir) {
    speed = 1;
    x = startX;
    y = startY;
    dir = startDir;
}

// Move the point 
void Point::step() {
    x += cos(dir) * speed;
    y += sin(dir) * speed;
}
