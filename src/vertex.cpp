#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "vertex.h"
#include "config.h"

using namespace std;

//// DEFINE ANIMATION VERTEX ////

// Constructor
AnimationVertex::AnimationVertex(void) {

    // Set random values as start (in Room coords)
    x = (float)(rand() % roomWidth);
    y = (float)(rand() % roomHeight);
    dir = (float)(rand() % 628) / 100;

    // Set radius
    radius = 7;  
    
    // Fille the nearest array with -1 (= not set yet)
    for (int i = 0; i < POLY_COUNT - 1; i++) {
        nearest[i] = -1;
    }
}

// Move the Vertex one frame
void AnimationVertex::step(void) {

    // Handle the bounce at the edges
    if (x > roomWidth) dir = clampAngle(M_PI - dir);
    if (x < 0) dir = clampAngle(M_PI - dir);
    if (y > roomHeight) dir = clampAngle(-dir);
    if (y < 0) dir = clampAngle(-dir);

    // Move 
    x += cos(dir);
    y += sin(dir);

}

// Get the 3 nearest vertecies
void AnimationVertex::getNearest(AnimationVertex * animVertecies) {

    for (int i = 0; i < animVertexNum; i++) {
        // Exit if its this vertex
        if (animVertecies[i].x == x && animVertecies[i].y == y) continue;

        // If nearest contains a NULL pointer put it in that spot
        bool setNearest = false;
        for (int j = 0; j < POLY_COUNT - 1; j++) {
            if (nearest[j] == -1) {
                nearest[j] = animVertecies[i].arrayIndex;
                setNearest = true;
                break;
            }
        }
        
        // Check if in for loop the value got set
        if (setNearest == true) continue;

        // If not continued jet nearest is full with pointers
        
        // Get the index with the farest vertex in nearest
        int farestIndex = 0;
        float farestDist = distToVertex(&animVertecies[nearest[0]]);
        for (int j = 0; j < POLY_COUNT - 1; j ++) {
            float testDist = distToVertex(&animVertecies[nearest[j]]); 
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

        float dist = distToVertex(&animVertecies[i]);
        if (dist < farestDist) {
            // Check if the other vertex is already in the array
            bool inArray = false;
            for (int j = 0; j < POLY_COUNT - 1; j++) {
                if (nearest[j] == animVertecies[i].arrayIndex) {
                    inArray = true;
                }
            } 

            if (inArray == false) {
                nearest[farestIndex] = animVertecies[i].arrayIndex;
            }
        }
    }
}

// Clac distnce between this an anoter vertex
float AnimationVertex::distToVertex(AnimationVertex * vertex) {
    return sqrt(pow(x - vertex->x, 2) + pow(y - vertex->x, 2));
}
