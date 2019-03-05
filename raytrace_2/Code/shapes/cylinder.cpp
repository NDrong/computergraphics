#include "cylinder.h"
#include "solvers.h"

#include <cmath>

Hit Cylinder::intersect(Ray const &ray)
{
    Point diff = ray.O - center;

    double a = ray.D.x * ray.D.x + ray.D.z * ray.D.z;
    double b = 2 * (ray.D.x * diff.x + ray.D.z * diff.z);
    double c = diff.x * diff.x + diff.z * diff.z - (radius * radius);

    double t1, t2;
    if (not Solvers::quadratic(a, b, c, t1, t2)) {
        return Hit::NO_HIT();
    }

    if (t1 < 0) {
        t1 = t2;
        if (t1 < 0) {
            return Hit::NO_HIT();
        }
    }

    Point pHit = ray.at(t1);
    if (pHit.y >= center.y && pHit.y <= center.y + height) {

        Vector N(pHit.x - center.x, 0, pHit.z - center.z);
        N.normalize();
        return {t1, N};
    }

    return Hit::NO_HIT();
}

Cylinder::Cylinder(Point center, double radius, double height)
:
center(center), radius(radius), height(height)
{}
