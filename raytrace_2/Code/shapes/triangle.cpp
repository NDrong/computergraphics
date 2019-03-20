#include "triangle.h"

#include <cfloat>   // DBL_EPSILON
#include <cmath>

Hit Triangle::intersect(Ray const &ray)
{
    // Möller-Trumbore
    Vector edge1(v1 - v0);
    Vector edge2(v2 - v0);
    Vector h = ray.D.cross(edge2);
    double a = edge1.dot(h);
    if (a > -DBL_EPSILON && a < DBL_EPSILON)
        return Hit::NO_HIT();

    double f = 1 / a;
    Vector s = ray.O - v0;
    double u = f * s.dot(h);
    if (u < 0.0 || u > 1.0)
        return Hit::NO_HIT();

    Vector q = s.cross(edge1);
    double v = f * ray.D.dot(q);
    if (v < 0.0 || u + v > 1.0)
        return Hit::NO_HIT();

    double t = f * edge2.dot(q);

    if (t <= DBL_EPSILON)    // line intersection (not ray)
        return Hit::NO_HIT();

    // determine orientation of the normal
    Vector normal = getNormal(ray.at(t));
    if (N.dot(ray.D) > 0)
        normal = -normal;

    return Hit(t, normal);
}

Triangle::Triangle(Point const &v0,
         Point const &v1,
         Point const &v2)
:
    v0(v0),
    v1(v1),
    v2(v2),
    N(),
    useSurfaceNormal(true)
{
    // Calculate surface normal
    Vector U(v1 - v0);
    Vector V(v2 - v0);
    N = U.cross(V);
    N.normalize();
}

Triangle::Triangle(Point const &v0, Point const &v1, Point const &v2, Point const &nv0, Point const &nv1,
                   Point const &nv2) : Triangle(v0, v1, v2) {
    Triangle::nv0 = nv0;
    Triangle::nv1 = nv1;
    Triangle::nv2 = nv2;
    useSurfaceNormal = false;
}

Vector Triangle::getNormal(const Point &point) const {
    if (useSurfaceNormal) {
        return N;
    }

    // Calculate barycentric coordinates u,v,w
    Vector d0 = v1 - v0;
    Vector d1 = v2 - v0;
    Vector d2 = point - v0;
    double d00 = d0.dot(d0);
    double d01 = d0.dot(d1);
    double d11 = d1.dot(d1);
    double d20 = d2.dot(d0);
    double d21 = d2.dot(d1);
    double denom = d00 * d11 - d01 * d01;

    double v = (d11 * d20 - d01 * d21) / denom;
    double w = (d00 * d21 - d01 * d20) / denom;
    double u = 1.0 - v - w;

    return (u * nv0 + v * nv1 + w * nv2).normalized();
}
