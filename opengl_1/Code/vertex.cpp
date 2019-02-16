#include "vertex.h"

Vertex::Vertex(float posX, float posY, float posZ, float r, float g, float b) : x(posX), y(posY), z(posZ), r(r), g(g), b(b)
{

}

Vertex::Vertex(QVector3D const &vector, float r, float g, float b) : x(vector.x()), y(vector.y()), z(vector.z()), r(r), g(g), b(b)
{

}
