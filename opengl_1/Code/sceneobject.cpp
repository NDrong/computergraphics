#include "sceneobject.h"
#include "vertex.h"

SceneObject::SceneObject()
{
    scaling = 1.0f;
}

SceneObject::~SceneObject() {
    glDeleteBuffers(1, &this->vbo);
    glDeleteVertexArrays(1, &this->vao);
}

void SceneObject::updateTransformationMatrix() {
    transform.setToIdentity();
    transform.translate(translation);
    transform.rotate(rotation.x(), 1, 0, 0);
    transform.rotate(rotation.y(), 0, 1, 0);
    transform.rotate(rotation.z(), 0, 0, 1);
    transform.scale(scaling);
}

void SceneObject::setScaling(float s) {
    scaling = s;
    updateTransformationMatrix();
}

void SceneObject::setRotation(float rX, float rY, float rZ) {
    rotation = {rX, rY, rZ};
    updateTransformationMatrix();
}

void SceneObject::createCube() {
    initializeOpenGLFunctions();

    std::vector<Vertex> cube;

    cube.push_back({ -1.0f,-1.0f,-1.0f,1,0,0});
    cube.push_back({ -1.0f,-1.0f, 1.0f,1,0,0});
    cube.push_back({ -1.0f, 1.0f, 1.0f,1,0,0});

    cube.push_back({ 1.0f, 1.0f,-1.0f, 1,0,0});
    cube.push_back({ -1.0f,-1.0f,-1.0f,1,0,0});
    cube.push_back({ -1.0f, 1.0f,-1.0f,1,0,0});

    cube.push_back({ 1.0f,-1.0f, 1.0f, 0,0,1});
    cube.push_back({ -1.0f,-1.0f,-1.0f,0,0,1});
    cube.push_back({ 1.0f,-1.0f,-1.0f, 0,0,1});

    cube.push_back({ 1.0f, 1.0f,-1.0f, 0,0,1});
    cube.push_back({ 1.0f,-1.0f,-1.0f, 0,0,1});
    cube.push_back({ -1.0f,-1.0f,-1.0f,0,0,1});

    cube.push_back({ -1.0f,-1.0f,-1.0f,0,1,0});
    cube.push_back({ -1.0f, 1.0f, 1.0f,0,1,0});
    cube.push_back({ -1.0f, 1.0f,-1.0f,0,1,0});

    cube.push_back({ 1.0f,-1.0f, 1.0f, 0,1,0});
    cube.push_back({ -1.0f,-1.0f, 1.0f,0,1,0});
    cube.push_back({ -1.0f,-1.0f,-1.0f,0,1,0});

    cube.push_back({ -1.0f, 1.0f, 1.0f,1,1,0});
    cube.push_back({ -1.0f,-1.0f, 1.0f,1,1,0});
    cube.push_back({ 1.0f,-1.0f, 1.0f, 1,1,0});

    cube.push_back({ 1.0f, 1.0f, 1.0f, 1,1,0});
    cube.push_back({ 1.0f,-1.0f,-1.0f, 1,1,0});
    cube.push_back({ 1.0f, 1.0f,-1.0f, 1,1,0});

    cube.push_back({ 1.0f,-1.0f,-1.0f, 1,0,1});
    cube.push_back({ 1.0f, 1.0f, 1.0f, 1,0,1});
    cube.push_back({ 1.0f,-1.0f, 1.0f, 1,0,1});

    cube.push_back({ 1.0f, 1.0f, 1.0f, 1,0,1});
    cube.push_back({ 1.0f, 1.0f,-1.0f, 1,0,1});
    cube.push_back({ -1.0f, 1.0f,-1.0f,1,0,1});

    cube.push_back({ 1.0f, 1.0f, 1.0f,0,1,1});
    cube.push_back({ -1.0f, 1.0f,-1.0f,0,1,1});
    cube.push_back({ -1.0f, 1.0f, 1.0f,0,1,1});

    cube.push_back({ 1.0f, 1.0f, 1.0f,0,1,1});
    cube.push_back({ -1.0f, 1.0f, 1.0f,0,1,1});
    cube.push_back({ 1.0f,-1.0f, 1.0f, 0,1,1});

    glGenBuffers(1, &this->vbo);
    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * cube.size(), &cube[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(2 * sizeof(float)));

    _numVertices = cube.size();
    translation = {2, 0, -6};
    updateTransformationMatrix();
}

void SceneObject::createPyramid() {
    initializeOpenGLFunctions();

    std::vector<Vertex> pyramid;

    pyramid.push_back({0, 1, 0, 1, 0, 0});
    pyramid.push_back({-1, -1, 1, 0, 1, 0});
    pyramid.push_back({1, -1, 1, 0, 0, 1});

    pyramid.push_back({0, 1, 0, 1, 0, 0});
    pyramid.push_back({1, -1, 1, 0, 0, 1});
    pyramid.push_back({1, -1, -1, 0, 1, 0});

    pyramid.push_back({0, 1, 0, 1, 0, 0});
    pyramid.push_back({1, -1, -1, 0, 1, 0});
    pyramid.push_back({-1, -1, -1, 0, 0, 1});

    pyramid.push_back({0, 1, 0, 1, 0, 0});
    pyramid.push_back({-1, -1, -1, 0, 0, 1});
    pyramid.push_back({-1, -1, 1, 0, 1, 0});

    pyramid.push_back({-1, -1, 1, 1, 0, 0});
    pyramid.push_back({-1, -1, -1, 0, 1, 0});
    pyramid.push_back({1, -1, -1, 0, 0, 1});
    pyramid.push_back({1, -1, -1, 0, 0, 1});
    pyramid.push_back({1, -1, 1, 0, 1, 0});
    pyramid.push_back({-1, -1, 1, 1, 0, 0});

    glGenBuffers(1, &this->vbo);
    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(sizeof(Vertex) * pyramid.size()), &pyramid[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<GLvoid*>(2 * sizeof(float)));

    _numVertices = pyramid.size();
    translation = {-2, 0, -6};
    updateTransformationMatrix();
}

void SceneObject::bind() {
    glBindVertexArray(this->vao);
}

size_t SceneObject::numVertices() {
    return _numVertices;
}
