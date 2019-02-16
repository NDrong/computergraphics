#include "vertex.h"

ColoredVertex::ColoredVertex(float posX, float posY, float posZ, float r, float g, float b) : x(posX), y(posY), z(posZ), r(r), g(g), b(b)
{

}

ColoredVertex::ColoredVertex(QVector3D const &vector, float r, float g, float b) : x(vector.x()), y(vector.y()), z(vector.z()), r(r), g(g), b(b)
{

}
