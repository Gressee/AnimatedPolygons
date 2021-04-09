#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>

// Importtant
typedef uint32_t indexType;

// Screen
extern int screenWidth;
extern int screenHeight;
extern int roomWidth;
extern int roomHeight;
float convertX(float x);
float convertY(float y);

// Animation
extern const int animVertexNum;

// Graphics
extern int drawVerteciesPerCircle;

// Other random functions
float clampAngle(float angle);

// Corners of a Polygon
// MUST STAY AT 3 bc of drawPolygons in draw.cpp
#define POLY_COUNT 3  

#endif