#include "sceneobject.h"
#include "vertex.h"

SceneObject::SceneObject()
{

}

SceneObject::~SceneObject() {
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}

void SceneObject::createCube() {
    Vertex triangle[3] = {
        { -1.0, -1.0, 0, 1.0, 0.0, 0.0 },
        { 1.0, -1.0, 0, 0.0, 1.0, 0.0 },
        { 0.0, 1.0, 0, 0.0, 0.0, 1.0 }
    };

    glGenBuffers(1, &this->vbo);
    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, triangle, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(2 * sizeof(float)));

    _numVertices = 3;
}

void SceneObject::createPyramid() {
    Vertex triangle[3] = {
        { -0.75, -1.0, 0, 1.0, 0.0, 0.0 },
        { 1.0, -1.0, 0, 0.0, 1.0, 0.0 },
        { 0.0, 1.0, 0, 0.0, 0.0, 1.0 }
    };

    glGenBuffers(1, &this->vbo);
    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, triangle, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(2 * sizeof(float)));

    _numVertices = 3;
}

void SceneObject::bind() {
    glBindVertexArray(this->vao);
}

size_t SceneObject::numVertices() {
    return _numVertices;
}
