#ifndef BUFFER_H_
#define BUFFER_H_


#include <GL/glew.h>
#include "vertex.h"

class VertexBuffer {
public:

    GLuint bufferId;
    GLuint vao;


    VertexBuffer(void * data, int numVertices) {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(DrawVertex), data, GL_STATIC_DRAW);

        // Position Attribute
        glEnableVertexAttribArray(0);
	    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(DrawVertex), (void *) offsetof(DrawVertex, x));

        // Color Attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(DrawVertex), (void *) offsetof(DrawVertex, r));

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


class IndexBuffer {
private:
    GLuint bufferId;

public:

    IndexBuffer(void * data, int numIndices, int elementSize) {
        
        glGenBuffers(1, &bufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * elementSize, data, GL_STATIC_DRAW);

    }

    virtual ~IndexBuffer() {
        glDeleteBuffers(1, &bufferId);
    }

    void bind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferId);
    }

    void unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    

};

#endif