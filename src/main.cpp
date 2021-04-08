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
#include "draw.h"
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
    window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    // Init GLEW
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        cout << "Error with glew" << endl;
        return -1;
    }


    //// ANIMATION ////
    
    // Ceate animation vertecies
    AnimationVertex animVertecies[vertexNum];


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

        // Move vertecies
        for (int i = 0; i < vertexNum; i++) {
            animVertecies[i].step();
        }

        // Check the nearest vertecies
        for (int i = 0; i < vertexNum; i++) {
            animVertecies[i].getNearest(animVertecies);
        }


        //// GRAPHICS ////

        // Clear
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw polygons

        // Draw Lines

        // Draw points
        for (int i = 0; i < vertexNum; i++) {
            drawCircle(animVertecies[i].x, animVertecies[i].y, 0.001);
        }

        // Show the drawn screen
        SDL_GL_SwapWindow(window);
        
    }
    

    return 1;
}