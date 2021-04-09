#ifndef VERTEX_H_
#define VERTEX_H_

#include <stdlib.h>
#include <math.h>
#include "config.h"


// Struct that is jused by opengl to draw
typedef struct {
    // Pos
    float x;
    float y;
    
    // Color
    float r;
    float g;
    float b;
    float a;
} DrawVertex;


// Class that is used for the animation with 
class AnimationVertex {
public:
    float x;
    float y;
    float dir;  // in RAD
    float speed;
    float radius; 
    int nearest[POLY_COUNT - 1];  // Stores the arrayIndexes of the nearest

    // The index where this Vertex is in the animVertecies array
    int arrayIndex = 0;  

    AnimationVertex();
    void step(void);
    void getNearest(AnimationVertex * vertecies);
    float distToVertex(AnimationVertex * vertex);


};


#endif