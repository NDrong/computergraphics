#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class Vertex
{
public:
    Vertex(float posX, float posY, float posZ, float r, float g, float b);
    Vertex(QVector3D const &vector);
    float x,y,z;
    float r,g,b;
};

#endif // VERTEX_H
