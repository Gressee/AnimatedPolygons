#include <iostream>
#include <GL/glew.h>
#include <math.h>
#include "config.h"
#include "draw.h"
#include "vertex.h"
#include "buffer.h"

// Draws a filled circle around every vertex
void drawVertexCirles(AnimationVertex * animVertecies) {


	int drawVerteciesNum = 0; 
	int indicesNum = 0;
	int indicesPerCircle = (drawVerteciesPerCircle - 1) * 3;
	int centerIndex = 0;
	int baseindex = 0;  // Index where indices for the current circle start

	// Create arrays
	DrawVertex * drawVertecies;
	drawVertecies = (DrawVertex *) malloc(sizeof(DrawVertex));
	indexType * indices;
	indices = (indexType *) malloc(sizeof(indexType));

	float angle, newX, newY, color;

	// Generate Vertecies and Indices for every animation Vertex
	for (int i = 0; i < animVertexNum; i++) {
	
		// Reacclocate memory for new Circle
		drawVerteciesNum += drawVerteciesPerCircle;
		indicesNum += indicesPerCircle;
		drawVertecies = (DrawVertex *) realloc(drawVertecies, drawVerteciesNum * sizeof(DrawVertex));
		indices = (indexType *) realloc(indices, indicesNum * sizeof(indexType));

		// First vertex in the Center
		centerIndex = drawVerteciesNum - drawVerteciesPerCircle;  // Index of the vertex that is in the center for this circle
		drawVertecies[centerIndex] = {
			convertX(animVertecies[i].x), // Convert from room to gl coords
			convertY(animVertecies[i].y), 
			1.0, 1.0, 1.0, 1.0}; // Color

		// Get new vertecies
		color = 1.0f;
		for (int j = 0; j < drawVerteciesPerCircle - 1; j++) {
			
			// Position of a new vertex
			angle = (((float)j) / (float)(drawVerteciesPerCircle-1)) * M_PI * 2.0;
			newX = cos(angle) * animVertecies[i].radius + animVertecies[i].x;
			newY = sin(angle) * animVertecies[i].radius + animVertecies[i].y;

			// Convert coords
			newX = convertX(newX);
			newY = convertY(newY);

			// Add new vertex to array
			drawVertecies[centerIndex + j + 1] = {newX, newY, color, color, color, color};
		}

		/*
			Get new inices:
			For v vertecies per circle there are v-1 triangle 
			so (v-1)*3 new indices per circle
			Every triangle uses the center circle
			The Last triangle needs to conect to the first vertex on the outer circle
			so its seperate
		*/
		baseindex = indicesNum - indicesPerCircle;
		for (int j = 0; j < drawVerteciesPerCircle -2; j++) {
			indices[baseindex + 3*j] = centerIndex;
			indices[baseindex + 3*j + 1] = centerIndex + j + 1;
			indices[baseindex + 3*j + 2] = centerIndex + j + 2;
		}
		indices[indicesNum - 3] = centerIndex;									// Center Vertex
		indices[indicesNum - 2] = drawVerteciesNum - 1;							// Last Vertex on outer circle
		indices[indicesNum - 1] = drawVerteciesNum - drawVerteciesPerCircle +1;	// First Vertex on outer circle

	}	

	IndexBuffer indexBuffer(indices, indicesNum, sizeof(indexType));

	VertexBuffer vertexBuffer(drawVertecies, drawVerteciesNum);
    vertexBuffer.unbind();

	
	vertexBuffer.bind();
	indexBuffer.bind();
	glDrawElements(GL_TRIANGLES, indicesNum, GL_UNSIGNED_INT, 0);
	indexBuffer.unbind();
	vertexBuffer.unbind();
	
	

	
}

// Draw all the Polygons
void drawPolygons(AnimationVertex * animVertecies)  {
	int drawVerteciesNum = 0;
	int indicesNum = 0;

	indexType * indices = (indexType *) malloc(sizeof(indexType));

	// Make Draw Vertecies from the animVertecies
	float color;
	drawVerteciesNum = animVertexNum;
	DrawVertex * drawVertecies = (DrawVertex *) malloc(drawVerteciesNum * sizeof(DrawVertex));
	for (int i = 0; i <  animVertexNum; i++) {
		color = (float)(rand() % 100) / 100.0f;
		drawVertecies[i] = {
			convertX(animVertecies[i].x),
			convertY(animVertecies[i].y),
			color,
			color,
			color,
			color
		};
	}

	// Go through every animVertex and make a triangle with its nearest 
	for (int i = 0; i < animVertexNum; i++) {
		/*
			This is no optimal solution bc it can only handle the case if
			the polygons are all trinagles
		*/

		// Update Count
		indicesNum += 3;

		// Allocate new memory
		indices = (indexType *) realloc(indices, indicesNum * sizeof(indexType));

		int i1 = animVertecies[i].arrayIndex;
		int i2 = animVertecies[i].nearest[0];
		int i3 = animVertecies[i].nearest[1];

		indices[i*3 + 0] = animVertecies[i].arrayIndex;
		indices[i*3 + 1] = animVertecies[i].nearest[0];
		indices[i*3 + 2] = animVertecies[i].nearest[1];

	}

	std::cout << "\n-------------------\n";
	for (int i = 0; i < drawVerteciesNum; i++) {
		std::cout << "X= " << drawVertecies[i].x << " Y= " << drawVertecies[i].y << "\n";
	}
	std::cout << "\n";
	for (int i = 0; i < indicesNum; i++) {
		if (i % 3 == 0) std::cout << std::endl;
		std::cout << indices[i] << " ";
	}

	// Draw the stuf on screen
	IndexBuffer indexBuffer(indices, indicesNum, sizeof(indexType));

	VertexBuffer vertexBuffer(drawVertecies, drawVerteciesNum);
    vertexBuffer.unbind();

	vertexBuffer.bind();
	indexBuffer.bind();
	glDrawElements(GL_TRIANGLES, indicesNum, GL_UNSIGNED_INT, 0);
	indexBuffer.unbind();
	vertexBuffer.unbind();



}