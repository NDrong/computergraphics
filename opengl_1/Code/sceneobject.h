#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <QOpenGLFunctions_3_3_Core>

class SceneObject
{
public:
    SceneObject();
    ~SceneObject();

    void bind();
    void createCube();
    void createPyramid();

    size_t numVertices();

private:
    size_t _numVertices;
    GLuint vbo, vao;
};

#endif // SCENEOBJECT_H
