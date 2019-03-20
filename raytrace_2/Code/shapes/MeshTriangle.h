//
// Created by Julius van Dijk on 2019-03-20.
//

#ifndef RAY_MESHTRIANGLE_H
#define RAY_MESHTRIANGLE_H


#include "../object.h"
#include "../vertex.h"

class MeshTriangle : public Object {

    Point getBaryCentricCoordinates(const Point& p) const;

    Vector getNormal(const Point& bc) const;

public:
    MeshTriangle(Vertex const &v0,
                 Vertex const &v1,
                 Vertex const &v2);

    virtual Hit intersect(Ray const &ray);

    Point p0, p1, p2, n0, n1, n2, t0, t1, t2;

};


#endif //RAY_MESHTRIANGLE_H
