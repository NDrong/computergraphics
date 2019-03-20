//
// Created by Julius van Dijk on 2019-03-20.
//

#include "MeshTriangle.h"
#include <cfloat>   // DBL_EPSILON
#include <cmath>

MeshTriangle::MeshTriangle(Vertex const &v0, Vertex const &v1, Vertex const &v2) {
    p0 = Point(v0.x, v0.y, v0.z);
    p1 = Point(v1.x, v1.y, v1.z);
    p2 = Point(v2.x, v2.y, v2.z);

    n0 = Point(v0.nx, v0.ny, v0.nz);
    n1 = Point(v1.nx, v1.ny, v1.nz);
    n2 = Point(v2.nx, v2.ny, v2.nz);

    t0 = Point(v0.u, v0.v, 0);
    t1 = Point(v1.u, v1.v, 0);
    t2 = Point(v2.u, v2.v, 0);
}

Point MeshTriangle::getBaryCentricCoordinates(const Point &p) const {
    Vector d0 = p1 - p0;
    Vector d1 = p2 - p0;
    Vector d2 = p - p0;
    double d00 = p.dot(d0);
    double d01 = d0.dot(d1);
    double d11 = d1.dot(d1);
    double d20 = d2.dot(d0);
    double d21 = d2.dot(d1);
    double denom = d00 * d11 - d01 * d01;

    double v = (d11 * d20 - d01 * d21) / denom;
    double w = (d00 * d21 - d01 * d20) / denom;
    double u = 1.0 - v - w;

    return Point(u, v, w);
}

Hit MeshTriangle::intersect(Ray const &ray) {
    // Möller-Trumbore
    Vector edge1(p1 - p0);
    Vector edge2(p2 - p0);
    Vector h = ray.D.cross(edge2);
    double a = edge1.dot(h);
    if (a > -DBL_EPSILON && a < DBL_EPSILON)
        return Hit::NO_HIT();

    double f = 1 / a;
    Vector s = ray.O - p0;
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
    if (normal.dot(ray.D) > 0)
        normal = -normal;

    return Hit(t, normal);
}

Vector MeshTriangle::getNormal(const Point &bc) const {
    return bc.x * n0 + bc.y * n1 + bc.z * n2;
}
