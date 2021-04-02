#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_


#include <GL/glew.h>
#include "vertex.h"

class VertexBuffer {
public:

    GLuint bufferId;
    GLuint vao;


    VertexBuffer(void* data, uint32_t numVertices) {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), data, GL_STATIC_DRAW);

        // Position Attribute
        glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, x));

        // Color Attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, x));

    }

    virtual ~VertexBuffer() {
        glDeleteBuffers(1, &bufferId);
    }

    void bind() {
       glBindVertexArray(vao);
    }

    void unbind() {
        glBindVertexArray(0);
    }
};


#endif