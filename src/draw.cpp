#include <iostream>

#include <GL/glew.h>

#include "defines.h"
#include "points.h"
#include "vertex.h"
#include "vertex_buffer.h"
#include "color.h"

using namespace std;

// Draws all the points on the screen
void drawPoints(Point * points) {

    // Create the array with vertecies from the points
    int i;
    float x, y, r, g, b, a;
    Vertex vertecies[POINTS_NUM];

    for (i = 0; i < POINTS_NUM; i++) {

        // Convert into range of (-1, 1)
        x = points[i].x / ((float) SCREEN_WIDTH);
        y = points[i].y / ((float) SCREEN_HEIGHT);
        
        // Set color
        r = 1.0f;
        g = 1.0f;
        b = 1.0f;
        a = 1.0f;

        vertecies[i] = Vertex{x, y}; //, r, g, b, a};
    }

    // Create Vertex buffer
    VertexBuffer vertexBuffer(vertecies, sizeof(vertecies)/sizeof(Vertex));
    vertexBuffer.unbind();

    // Draw the Vertex array
    vertexBuffer.bind();
    glDrawArrays(GL_TRIANGLE_FAN, 0, sizeof(vertecies)/sizeof(Vertex));
    vertexBuffer.unbind();
    
}