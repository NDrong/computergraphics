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
    rotation = QMatrix4x4();
    rotation.rotate(rX, 1, 0, 0);
    rotation.rotate(rY, 0, 1, 0);
    rotation.rotate(rZ, 0, 0, 1);
}

void SceneObject::createCube() {
    initializeOpenGLFunctions();

    std::vector<Vertex> cube;

        // Kubus in normale volgorde van het wereldwijde web.
// Back face
   cube.push_back( {-0.5f, -0.5f, -0.5f,  1, 0, 0}); // Bottom-left
   cube.push_back( { 0.5f, -0.5f, -0.5f,   1, 0, 0}); // bottom-right
   cube.push_back( { 0.5f,  0.5f, -0.5f,   1, 0, 0}); // top-right
   cube.push_back( { 0.5f,  0.5f, -0.5f,  1, 0, 0 }); // top-right
   cube.push_back( {-0.5f,  0.5f, -0.5f,  1, 0, 0 }); // top-left
   cube.push_back( {-0.5f, -0.5f, -0.5f,  1, 0, 0 }) ;// bottom-left
// Front face
   cube.push_back( {-0.5f, -0.5f,  0.5f,   0, 1, 0}); // bottom-left
   cube.push_back( { 0.5f,  0.5f,  0.5f,  0, 1, 0}); // top-right
   cube.push_back( { 0.5f, -0.5f,  0.5f,  0, 1, 0}); // bottom-right
   cube.push_back( { 0.5f,  0.5f,  0.5f,  0, 1, 0}); // top-right
   cube.push_back( {-0.5f, -0.5f,  0.5f,  0, 1, 0}); // bottom-left
   cube.push_back( {-0.5f,  0.5f,  0.5f,  0, 1, 0}); // top-left
 // Left face
   cube.push_back( {-0.5f,  0.5f,  0.5f,  0, 0, 1}); // top-right
   cube.push_back( {-0.5f, -0.5f, -0.5f,  0, 0, 1}) ;// bottom-left
   cube.push_back( {-0.5f,  0.5f, -0.5f,  0, 0, 1}) ;//top-left
   cube.push_back( {-0.5f, -0.5f, -0.5f,  0, 0, 1}) ;// bottom-left
   cube.push_back( {-0.5f,  0.5f,  0.5f,  0, 0, 1}) ; // top-right
   cube.push_back( {-0.5f, -0.5f,  0.5f,  0, 0, 1}); // bottom-right
 // Right face
   cube.push_back( { 0.5f,  0.5f,  0.5f,  0, 1, 1}); // top-left
   cube.push_back( { 0.5f,  0.5f, -0.5f,  0, 1, 1}); // top-right
   cube.push_back( { 0.5f, -0.5f, -0.5f,  0, 1, 1}); // bottom-right
   cube.push_back( { 0.5f, -0.5f, -0.5f,  0, 1, 1}); // bottom-right
   cube.push_back( { 0.5f, -0.5f,  0.5f,  0, 1, 1}); // bottom-left
   cube.push_back( { 0.5f,  0.5f,  0.5f,  0, 1, 1}); // top-left
 // Bottom face
   cube.push_back( {-0.5f, -0.5f, -0.5f,  1, 0, 1}) ;// top-right
   cube.push_back( { 0.5f, -0.5f,  0.5f,  1, 0, 1}) ;// bottom-left
   cube.push_back( { 0.5f, -0.5f, -0.5f,  1, 0, 1}) ;// top-left
   cube.push_back( { 0.5f, -0.5f,  0.5f,  1, 0, 1}) ;// bottom-left
   cube.push_back( {-0.5f, -0.5f, -0.5f,  1, 0, 1}) ;// top-right
   cube.push_back( {-0.5f, -0.5f,  0.5f,  1, 0, 1}) ;// bottom-right
 // Top face
   cube.push_back( {-0.5f,  0.5f, -0.5f,  1, 1, 0}) ;// top-left
   cube.push_back( { 0.5f,  0.5f, -0.5f,  1, 1, 0}) ;// top-right
   cube.push_back( { 0.5f,  0.5f,  0.5f,  1, 1, 0}) ;// bottom-right
   cube.push_back( { 0.5f,  0.5f,  0.5f,  1, 1, 0}) ;// bottom-right
   cube.push_back( {-0.5f,  0.5f,  0.5f,  1, 1, 0}) ;// bottom-left
   cube.push_back( {-0.5f,  0.5f, -0.5f,  1, 1, 0}) ;// top-left



    /*
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
    */

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
    initializeOpenGLFunctions();

    std::vector<Vertex> pyramid;

    // Poging 2 tot het maken van een piramide.
    // Bottom face 1 (OK)
    pyramid.push_back({-1, -1, 1, 1.0, 0, 0.0});
    pyramid.push_back({1, -1, -1, 1.0, 0, 0.0});
    pyramid.push_back({-1, -1, -1, 1.0, 0, 0.0});
    pyramid.push_back({-1, -1, 1, 1.0, 0, 0.0});
    pyramid.push_back({1, -1, 1, 1.0, 0, 0.0});
    pyramid.push_back({1, -1, -1, 1.0, 0, 0.0});

    // Right face (OK)
    pyramid.push_back({0, 1, 0, 0, 0.25, 0.75});
    pyramid.push_back({1, -1, -1, 0, 0.25, 0.75});
    pyramid.push_back({1, -1, 1, 0, 0.25, 0.75});

    // Left face (OK)
    pyramid.push_back({0, 1, 0, 0.25, 0, 0.25});
    pyramid.push_back({-1, -1, 1, 0.25, 0, 0.25});
    pyramid.push_back({-1, -1, -1, 0.25, 0, 0.25});

    // Front face (OK)
    pyramid.push_back({0, 1, 0, 0.25, 0.25, 0});
    pyramid.push_back({-1, -1, -1, 0.25, 0.25, 0});
    pyramid.push_back({1, -1, -1, 0.25, 0.25, 0});

    // Back face (OK)
    pyramid.push_back({0, 1, 0, 0, 0.25, 0.25});
    pyramid.push_back({1, -1, 1, 0, 0.25, 0.25});
    pyramid.push_back({-1, -1, 1, 0, 0.25, 0.25});

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
    transform.translate(-2, 0, -6);
}

void SceneObject::bind() {
    glBindVertexArray(this->vao);
}

size_t SceneObject::numVertices() {
    return _numVertices;
}
