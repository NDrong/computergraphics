#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>

class ColoredVertex
{
public:
    ColoredVertex(float posX, float posY, float posZ, float r, float g, float b);
    ColoredVertex(QVector3D const &vector, float r, float g, float b);

    float x,y,z;
    float r,g,b;
};

#endif // VERTEX_H
