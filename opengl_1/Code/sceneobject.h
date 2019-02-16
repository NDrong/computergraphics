#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>

class SceneObject : protected QOpenGLFunctions_3_3_Core
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
    QMatrix4x4 rotation;

    GLuint vbo, vao;
private:
    size_t _numVertices;
    float oldRX, oldRY, oldRZ;
};

#endif // SCENEOBJECT_H
