#include "sceneobject.h"
#include "vertex.h"

SceneObject::SceneObject()
{
    oldRX = oldRY = oldRZ = 0;
}

SceneObject::~SceneObject() {
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}

void SceneObject::rotate(float rX, float rY, float rZ) {
    float dX = rX - oldRX;
    float dY = rY - oldRY;
    float dZ = rZ - oldRZ;

    transform.rotate(dX, dY, dZ);
    oldRX = rX;
    oldRY = rY;
    oldRZ = rZ;
}

void SceneObject::createCube() {
    std::vector<Vertex> cube;
    cube.push_back({ -1.0f,-1.0f,-1.0f,1,0,0});
    cube.push_back({ -1.0f, 1.0f, 1.0f,1,0,0});
    cube.push_back({ -1.0f,-1.0f, 1.0f,1,0,0});

    cube.push_back({ 1.0f, 1.0f,-1.0f, 1,0,0});
    cube.push_back({ -1.0f, 1.0f,-1.0f,1,0,0});
    cube.push_back({ -1.0f,-1.0f,-1.0f,1,0,0});

    cube.push_back({ 1.0f,-1.0f, 1.0f, 0,0,1});
    cube.push_back({ 1.0f,-1.0f,-1.0f, 0,0,1});
    cube.push_back({ -1.0f,-1.0f,-1.0f,0,0,1});

    cube.push_back({ 1.0f, 1.0f,-1.0f, 0,0,1});
    cube.push_back({ -1.0f,-1.0f,-1.0f,0,0,1});
    cube.push_back({ 1.0f,-1.0f,-1.0f, 0,0,1});

    cube.push_back({ -1.0f,-1.0f,-1.0f,0,1,0});
    cube.push_back({ -1.0f, 1.0f,-1.0f,0,1,0});
    cube.push_back({ -1.0f, 1.0f, 1.0f,0,1,0});

    cube.push_back({ 1.0f,-1.0f, 1.0f, 0,1,0});
    cube.push_back({ -1.0f,-1.0f,-1.0f,0,1,0});
    cube.push_back({ -1.0f,-1.0f, 1.0f,0,1,0});

    cube.push_back({ -1.0f, 1.0f, 1.0f,1,1,0});
    cube.push_back({ 1.0f,-1.0f, 1.0f, 1,1,0});
    cube.push_back({ -1.0f,-1.0f, 1.0f,1,1,0});

    cube.push_back({ 1.0f, 1.0f, 1.0f, 1,1,0});
    cube.push_back({ 1.0f, 1.0f,-1.0f, 1,1,0});
    cube.push_back({ 1.0f,-1.0f,-1.0f, 1,1,0});

    cube.push_back({ 1.0f,-1.0f,-1.0f, 1,0,1});
    cube.push_back({ 1.0f,-1.0f, 1.0f, 1,0,1});
    cube.push_back({ 1.0f, 1.0f, 1.0f, 1,0,1});

    cube.push_back({ 1.0f, 1.0f, 1.0f, 1,0,1});
    cube.push_back({ -1.0f, 1.0f,-1.0f,1,0,1});
    cube.push_back({ 1.0f, 1.0f,-1.0f, 1,0,1});

    cube.push_back({ 1.0f, 1.0f, 1.0f,0,1,1});
    cube.push_back({ -1.0f, 1.0f, 1.0f,0,1,1});
    cube.push_back({ -1.0f, 1.0f,-1.0f,0,1,1});

    cube.push_back({ 1.0f, 1.0f, 1.0f,0,1,1});
    cube.push_back({ 1.0f,-1.0f, 1.0f, 0,1,1});
    cube.push_back({ -1.0f, 1.0f, 1.0f,0,1,1});




    glGenBuffers(1, &this->vbo);
    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * cube.size(), &cube[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(2 * sizeof(float)));

    _numVertices = cube.size();
    transform.translate(2, 0, -6);
}

void SceneObject::createPyramid() {
    std::vector<Vertex> pyramid;

    pyramid.push_back({0, 1, 0, 1, 0, 0});
    pyramid.push_back({-1, -1, -1, 1, 0, 0});
    pyramid.push_back({1, -1, -1, 1, 0, 0});
    pyramid.push_back({0, 1, 0, 1, 0, 0});
    pyramid.push_back({-1, -1, 1, 0, 1, 0});
    pyramid.push_back({1, -1, 1, 0, 1, 0});

    pyramid.push_back({0, 1, 0, 0, 0, 1});
    pyramid.push_back({1, -1, -1, 0, 0, 1});
    pyramid.push_back({1, -1, 1, 0, 0, 1});
    pyramid.push_back({0, 1, 0, 0, 0, 1});
    pyramid.push_back({-1, -1, -1, 0, 0, 1});
    pyramid.push_back({-1, -1, 1, 0, 0, 1});

    pyramid.push_back({-1, -1, -1, 1, 1, 1});
    pyramid.push_back({-1, -1, 1, 1, 1, 1});
    pyramid.push_back({1, -1, -1, 1, 1, 1});
    pyramid.push_back({-1, -1, 1, 1, 1, 1});
    pyramid.push_back({1, -1, -1, 1, 1, 1});
    pyramid.push_back({1, -1, 1, 1, 1, 1});

    glGenBuffers(1, &this->vbo);
    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * pyramid.size(), &pyramid[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(2 * sizeof(float)));

    _numVertices = pyramid.size();
    transform.translate(-2, 0, -6);
}

void SceneObject::bind() {
    glBindVertexArray(this->vao);
}

size_t SceneObject::numVertices() {
    return _numVertices;
}
