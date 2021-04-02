#ifndef POINTS_H_
#define POINTS_H_

class Point {
public:
    // Animation
    // Position is in range (-1, 1)
    // Angle in RAD
    float x, y, dir, speed; 

    // Constructor
    Point(float startX, float startY, float startDir);

    // Move the point 
    void step();
};

#endif
