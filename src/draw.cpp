#include <iostream>
#include <GL/glew.h>
#include <math.h>
#include "config.h"
#include "draw.h"
#include "vertex.h"
#include "buffer.h"


int polygonExists(indexType * indices, int indicesNum, indexType * newIndices) {
	
	int i, j, k, l;

	int polygonExists = 0;

	bool inArray[POLY_COUNT];	
	for (l = 0; l < POLY_COUNT; l++) {
		inArray[l] = false;
	}

	// Go through every triangle and compare with the new one
	bool sameArray = true;
	for (i = 0; i < indicesNum; i += POLY_COUNT) {
		
		for (l = 0; l < POLY_COUNT; l++) {
			inArray[l] = false;
		}
		
		// Compare two Polygons
		for (j = 0; j < POLY_COUNT; j++) {
			
			for (k = 0; k < POLY_COUNT; k++){
				if (indices[i+j] == newIndices[k]){
					inArray[j] = true;
				}
			}

		}
		
		sameArray = true;
		for (l = 0; l < POLY_COUNT; l++) {
			if (inArray[l] == false) sameArray = false;
		}
		
		if (sameArray == true) {
			polygonExists = 1;
		}
		
	}

	return polygonExists;
}



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
	
	int exists = 0;

	int drawVerteciesNum = 0;
	int indicesNum = 0;
	std::cout << "Reach -1" << std::endl;
	indexType * indices = (indexType *) malloc(sizeof(indexType));
	std::cout << "Reach 0" << std::endl;
	// Make Draw Vertecies from the animVertecies
	float color = 0.5f;
	drawVerteciesNum = animVertexNum;
	DrawVertex * drawVertecies = (DrawVertex *) malloc(drawVerteciesNum * sizeof(DrawVertex));
	for (int i = 0; i <  animVertexNum; i++) {
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

		// Get the new possible indices
		indexType newIndices[POLY_COUNT];
		newIndices[0] = (indexType)animVertecies[i].arrayIndex;
		for (int j = 0; j < POLY_COUNT -1; j++)
			newIndices[j+1] = (indexType)animVertecies[i].nearest[j];

		// Check if this polygon exists already
		exists = polygonExists(indices, indicesNum, newIndices); 
		std::cout << "Exists = " << exists << std::endl;
		//exists = 0;
		if (exists == 0) {
			std::cout << "Reach 1" << std::endl;
			// Update Count
			indicesNum += POLY_COUNT;
			std::cout << "Reach 2" << std::endl;
			// Allocate new memory
			indices = (indexType *) realloc(indices, indicesNum * sizeof(indexType));
			std::cout << "Reach 3" << std::endl;
			indices[i*3 + 0] = (indexType)animVertecies[i].arrayIndex;
			indices[i*3 + 1] = (indexType)animVertecies[i].nearest[0];
			indices[i*3 + 2] = (indexType)animVertecies[i].nearest[1];
			std::cout << "Reach 4" << std::endl;
		}
	}
	/*
	std::cout << "\n-------------------\n";
	for (int i = 0; i < drawVerteciesNum; i++) {
		std::cout << "X= " << drawVertecies[i].x << " Y= " << drawVertecies[i].y << "\n";
	}
	std::cout << "\n";
	for (int i = 0; i < indicesNum; i++) {
		if (i % 3 == 0) std::cout << std::endl;
		std::cout << indices[i] << " ";
	}
	*/
	std::cout << "Reach 5" << std::endl;
	// Draw the stuf on screen
	IndexBuffer indexBuffer(indices, indicesNum, sizeof(indexType));
	std::cout << "Reach 6" << std::endl;
	VertexBuffer vertexBuffer(drawVertecies, drawVerteciesNum);
	std::cout << "Reach 6.5" << std::endl;
    vertexBuffer.unbind();
	std::cout << "Reach 7" << std::endl;
	vertexBuffer.bind();
	indexBuffer.bind();
	glDrawElements(GL_TRIANGLES, indicesNum, GL_UNSIGNED_INT, 0);
	indexBuffer.unbind();
	vertexBuffer.unbind();
	std::cout << "Reach 8" << std::endl;



}

