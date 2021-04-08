#include <GL/glew.h>
#include <math.h>
#include "draw.h"

void drawCircle(float x, float y, float radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle
	
	GLfloat twicePi = 2.0f * M_PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}