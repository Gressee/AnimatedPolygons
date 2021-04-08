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
    AnimationVertex * nearest[VERTEX_CONNECTIONS];  

    AnimationVertex();
    void step(void);
    void getNearest(AnimationVertex * vertecies);
    float distToVertex(AnimationVertex * vertex);


};


#endif