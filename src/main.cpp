// Standard stuff
#include <iostream>

// OpenGL and SDL
#define GLEW_STATIC
#include <GL/glew.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

// Local Includes
#include "color.h"
#include "config.h"
#include "defines.h"
#include "draw.h"
#include "points.h"
#include "shader.h"
#include "vertex_buffer.h"
#include "vertex.h"

using namespace std;


int main() {
    
    ////// SETUP OPENGL AND SDL ETC //////

    // Inti SDL
    SDL_Window * window;
    SDL_Init(SDL_INIT_EVERYTHING);

    // Init vertex buffer
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Create window
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // Init GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cout << "Error with glew" << endl;
        return -1;
    }


    ////// ANIMATION //////

    // Animation variables
    float animationTime = 0.0;

    // Create the point
    Point * points;
    points = (Point *) malloc(POINTS_NUM * sizeof(Point));
    for (int i = 0; i < POINTS_NUM; i++) {
        points[i] = Point(0.1f*(float)i, 0.1f*(float)i, 1.0f + (float)i);
    }

    // Main Loop
    bool run = true;
    while (run){
        
        //// CHECK QUIT ////
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                run = false;
            }
        }

        
        //// ANIMATION ////

        // Update point position
        for (int i = 0; i < POINTS_NUM; i++) points[i].step();

        // Update nearest points


        //// GRAPHICS ////

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw polygons

        // Draw Lines

        // Draw points
        drawPoints(points);

        // Show the drawn screen
        SDL_GL_SwapWindow(window);
        
    }
    

    return 1;
}