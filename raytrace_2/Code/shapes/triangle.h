#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "../object.h"

class Triangle : public Object {
public:
    Triangle(Point const &v0,
             Point const &v1,
             Point const &v2);

    Triangle(Point const &v0,
             Point const &v1,
             Point const &v2,
             Point const &nv0,
             Point const &nv1,
             Point const &nv2);

    virtual Hit intersect(Ray const &ray);

    Point v0;
    Point v1;
    Point v2;

    bool useSurfaceNormal;
    Vector N;
    Point nv0, nv1, nv2;
    Vector getNormal(const Point& hit) const;

};

#endif
