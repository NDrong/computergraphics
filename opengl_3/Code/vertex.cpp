#include "vertex.h"

ColoredVertex::ColoredVertex(float posX, float posY, float posZ, float r, float g, float b, QVector3D normal) : x(posX), y(posY), z(posZ), r(r), g(g), b(b), normal(normal)
{

}

ColoredVertex::ColoredVertex(QVector3D const &vector, float r, float g, float b, QVector3D normal, QVector2D textureCoords) : x(vector.x()), y(vector.y()), z(vector.z()), r(r), g(g), b(b), normal(normal), textureCoords(textureCoords)
{

}
