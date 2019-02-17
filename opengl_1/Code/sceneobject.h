#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QMatrix4x4>
#include <QVector3D>
#include <cmath>
#include "vertex.h"

class SceneObject : protected QOpenGLFunctions_3_3_Core
{
public:
    SceneObject();
    ~SceneObject();

    void bind();
    void createCube();
    void createPyramid();
    void createSphere();
    void createObject(const std::vector<ColoredVertex>& vertices,const QVector3D& translation);

    void loadMesh(QString filename, const QVector3D& translation);

    void setRotation(float rX, float rY, float rZ);
    void setScaling(float s);

    size_t numVertices();

    QMatrix4x4 transform;

    GLuint vbo, vao;
private:
    size_t _numVertices;

    void updateTransformationMatrix();

    QVector3D translation, rotation;

    float scaling;
    float scalingFactor;
};

#endif // SCENEOBJECT_H
