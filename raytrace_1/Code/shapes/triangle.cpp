#include "triangle.h"

#include <cmath>

Hit Triangle::intersect(Ray const &ray)
{
    /* Your intersect calculation goes here */

    Vector v0v1 = vb - va;
    Vector v0v2 = vc - va;
    Vector pvec = ray.D.cross(v0v2);
    double det = v0v1.dot(pvec);

    if (fabs(det) < 0.001) return Hit::NO_HIT();

    double invDet = 1 / det;

    Vector tvec = ray.O - va;
    double u = tvec.dot(pvec) * invDet;

    if (u < 0 || u > 1) return Hit::NO_HIT();

    Vector qvec = tvec.cross(v0v1);
    double v = ray.D.dot(qvec) * invDet;

    if (v < 0 || (u + v) > 1) return Hit::NO_HIT();

    double t = v0v2.dot(qvec) * invDet;
    Vector N = v0v1.cross(v0v2);
    N.normalize();

    return Hit(t, N);
}

Triangle::Triangle(Point va, Point vb, Point vc)
:
va(va), vb(vb), vc(vc)
{}
