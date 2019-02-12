#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>

class SceneObject
{
public:
    SceneObject();
    ~SceneObject();

    void bind();
    void createCube();
    void createPyramid();

    void rotate(float rX, float rY, float rZ);

    size_t numVertices();

    QMatrix4x4 transform;

private:
    size_t _numVertices;
    GLuint vbo, vao;
    float oldRX, oldRY, oldRZ;
};

#endif // SCENEOBJECT_H
