#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>
#include <QVector3D>

class SceneObject : protected QOpenGLFunctions_3_3_Core
{
public:
    SceneObject();
    ~SceneObject();

    void bind();
    void createCube();
    void createPyramid();
    void createSphere();

    void setRotation(float rX, float rY, float rZ);
    void setScaling(float s);

    size_t numVertices();

    QMatrix4x4 transform;

    GLuint vbo, vao;
private:
    enum ObjectType
    {
        Cube,
        Pyramid,
        Sphere,
    };
    ObjectType objectType;
    size_t _numVertices;
    float oldRX, oldRY, oldRZ;

    void updateTransformationMatrix();
    QVector3D translation, rotation;
    float scaling;
};

#endif // SCENEOBJECT_H
