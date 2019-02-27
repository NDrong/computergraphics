#ifndef VERTEX_H
#define VERTEX_H

#include <QVector3D>
#include <QVector2D>

class ColoredVertex
{
public:
    ColoredVertex(float posX, float posY, float posZ, float r, float g, float b, QVector3D normal);
    ColoredVertex(QVector3D const &vector, float r, float g, float b, QVector3D normal, QVector2D textureCoords);

    float x,y,z;
    float r,g,b;
    QVector3D normal;
    QVector2D textureCoords;
};

#endif // VERTEX_H
