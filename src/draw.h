#ifndef DRAW_H_
#define DRAW_H_

#include "vertex.h"

void drawVertexCirles(AnimationVertex * animVertecies);
void drawPolygons(AnimationVertex * animVertecies);
int polygonExists(indexType * indices, int indicesNum, indexType * newIndices);

#endif