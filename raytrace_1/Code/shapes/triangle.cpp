#include "triangle.h"

#include <cmath>

Hit Triangle::intersect(Ray const &ray)
{
    /* Your intersect calculation goes here */

    Vector U = vb - va;
    Vector V = vc - va;
    Vector N = U.cross(V);

    double nd = N.dot(ray.D);

    if (nd < 0.001) {
        return Hit::NO_HIT();
    }

    double D = N.dot(va);
    double t = -(N.dot(ray.O) + D) / nd;

    if (t < 0) {
        return Hit::NO_HIT();
    }

    Vector pHit = ray.at(t);
    Vector C;

    Vector edge0 = vb - va;
    Vector vp0 = pHit - va;
    C = edge0.cross(vp0);
    if (N.dot(C) < 0) {
        return Hit::NO_HIT();
    }

    Vector edge1 = vc - vb;
    Vector vp1 = pHit - vb;
    C = edge1.cross(vp1);
    if (N.dot(C) < 0) {
        return Hit::NO_HIT();
    }

    Vector edge2 = va - vc;
    Vector vp2 = pHit - vc;
    C = edge2.cross(vp2);
    if (N.dot(C) < 0) {
        return Hit::NO_HIT();
    }

    return Hit(t, N);
}

Triangle::Triangle(Point va, Point vb, Point vc)
:
va(va), vb(vb), vc(vc)
{}
