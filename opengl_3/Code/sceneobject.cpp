#include "sceneobject.h"

#include <utility>
#include "model.h"

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

void SceneObject::setTranslation(QVector3D translation)
{
    SceneObject::translation = translation;
    updateTransformationMatrix();
}

void SceneObject::setRotation(float rX, float rY, float rZ) {
    while (rX > 360) rX -= 360;
    while (rY > 360) rY -= 360;
    while (rZ > 360) rZ -= 360;
    rotation = {rX, rY, rZ};
    updateTransformationMatrix();
}

void SceneObject::setRotation(QVector3D rotation) {
    setRotation(rotation.x(), rotation.y(), rotation.z());
}

QVector3D SceneObject::getRotation() const {
    return rotation;
}

void SceneObject::createObject(const std::vector<ColoredVertex>& vertices, const QVector3D& translation) {
    initializeOpenGLFunctions();

    glGenBuffers(1, &this->vbo);
    glGenVertexArrays(1, &this->vao);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

    glBufferData(GL_ARRAY_BUFFER, GLsizeiptr(sizeof(ColoredVertex) * vertices.size()), &vertices[0], GL_STATIC_DRAW);

    // Pass a nullptr because the coordinates start at an offset of zero (i.e. the very first variable in the class).
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), nullptr);

    // Pass an offset of 3 floats because the colors start at the fourth (i.e. index three) variable in the class.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), reinterpret_cast<GLvoid*>(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), reinterpret_cast<GLvoid*>(6 * sizeof(float)));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(ColoredVertex), reinterpret_cast<GLvoid*>(9 * sizeof(float)));

    _numVertices = vertices.size();
    this->translation = translation;
    updateTransformationMatrix();
}

void SceneObject::createFromModelResource(QString filename, const QVector3D& translation) {
    initializeOpenGLFunctions();

    Model model(filename);
    model.unitize();
    auto vertices = model.getVertices();
    auto normals = model.getNormals();
    auto textureCoords = model.getTextureCoords();

    std::vector<ColoredVertex> object;
    float r, g, b;
    int i = 0;
    for (auto const &vertex : vertices) {
        // Generate (pseudo)random colors for the vertices.
        r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        object.emplace_back(vertex, r, g, b, normals[i], textureCoords[i]);

        i++;
    }

    createObject(object, translation);
}

void SceneObject::bind() {
    glBindVertexArray(this->vao);
}

void SceneObject::setWaveParameters(size_t index, float amplitude, float frequency, float phase) {
    waveAmplitudes[index] = amplitude;
    waveFrequencies[index] = frequency;
    wavePhases[index] = phase;
}

size_t SceneObject::numVertices() {
    return _numVertices;
}
