#include "sceneobject.h"
#include "vertex.h"
#include "model.h"

SceneObject::SceneObject()
{
    scaling = 1.0f;
    scalingFactor = 1.0f;
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
    transform.scale(scaling * scalingFactor);
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

    std::vector<ColoredVertex> cube;

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

    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(sizeof(ColoredVertex) * cube.size()), &cube[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), reinterpret_cast<GLvoid*>(3 * sizeof(float)));

    _numVertices = cube.size();
    translation = {2, 0, -6};
    updateTransformationMatrix();
}

void SceneObject::createPyramid() {
    initializeOpenGLFunctions();

    std::vector<ColoredVertex> pyramid;

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

    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(sizeof(ColoredVertex) * pyramid.size()), &pyramid[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), reinterpret_cast<GLvoid*>(3 * sizeof(float)));

    _numVertices = pyramid.size();
    translation = {-2, 0, -6};
    updateTransformationMatrix();
}

void SceneObject::createSphere() {
    scalingFactor = 0.04f;
    loadMesh(":/models/sphere.obj");
}

void SceneObject::loadMesh(QString filename) {
    initializeOpenGLFunctions();

    Model model(filename);
    auto vertices = model.getVertices();
    std::vector<ColoredVertex> object;
    float r, g, b;
    for (auto const &vertex : vertices) {
        r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        object.push_back(ColoredVertex(vertex, r, g, b));
    }

    glGenBuffers(1, &this->vbo);
    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(sizeof(ColoredVertex) * object.size()), &object[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), reinterpret_cast<GLvoid*>(3 * sizeof(float)));

    _numVertices = object.size();
    translation = {0, 0, -10};

    // Determine scaling factor based on max. width and height of the vertices.


    updateTransformationMatrix();
}

void SceneObject::bind() {
    glBindVertexArray(this->vao);
}

size_t SceneObject::numVertices() {
    return _numVertices;
}
