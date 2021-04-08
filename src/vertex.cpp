#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "vertex.h"
#include "config.h"

using namespace std;

//// DEFINE ANIMATION VERTEX ////

// Constructor
AnimationVertex::AnimationVertex(void) {
    // Set random values as start 
    x = (float)(rand() % 200 -100) / 100;
    y = (float)(rand() % 200 -100) / 100;
    dir = (float)(rand() % 628) / 100;    
    
    // Fille the nearest array with NULL pointers
    for (int i = 0; i < VERTEX_CONNECTIONS; i++) {
        nearest[i] = NULL;
    }
}

// Move the Vertex one frame
void AnimationVertex::step(void) {
    x += cos(dir);
    y += sin(dir);
}

// Get the 3 nearest vertecies
void AnimationVertex::getNearest(AnimationVertex * vertecies) {
    for (int i = 0; i < vertexNum; i++) {
        // Exit if its this vertex
        if (vertecies[i].x == x && vertecies[i].y == y) continue;

        // If nearest contains a NULL pointer put it in that spot
        bool setNearest = false;
        for (int j = 0; j < VERTEX_CONNECTIONS; j++) {
            if (nearest[j] == NULL) {
                nearest[j] = &vertecies[i];
                setNearest = true;
                break;
            }
        }
        
        // Check if in for loop the value got set
        if (setNearest == true) continue;

        // If not continued jet nearest is full with pointers
        
        // Get the index with the farest vertex in nearest
        int farestIndex = 0;
        float farestDist = distToVertex(nearest[0]);
        for (int j = 0; j < VERTEX_CONNECTIONS; j ++) {
            float testDist = distToVertex(nearest[j]); 
            if (testDist > farestDist) {
                farestDist = testDist;
                farestIndex = j;
            }
        }

        /*
            If the dist to the other vertex is lower
            than the farest dist in the nearest array it gets
            replaced
        */

        float dist = distToVertex(&vertecies[i]);
        if (dist < farestDist) {
            nearest[farestIndex] = &vertecies[i];
        }
    }
}

// Clac distnce between this an anoter vertex
float AnimationVertex::distToVertex(AnimationVertex * vertex) {
    return sqrt(pow(x - vertex->x, 2) + pow(y - vertex->x, 2));
}
