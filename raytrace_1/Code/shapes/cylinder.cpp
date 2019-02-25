#include "cylinder.h"

#include <cmath>

Hit Cylinder::intersect(Ray const &ray)
{
    Point diff = ray.O - center;

    double a = ray.D.x * ray.D.x + ray.D.z * ray.D.z;
    double b = 2 * (ray.D.x * diff.x + ray.D.z * diff.z);
    double c = diff.x * diff.x + diff.z * diff.z - (radius * radius);

    double delta = b*b - 4 * a * c;
    if (delta < 0.001) {
        return Hit::NO_HIT();
    }

    double t1 = (-b - sqrt(delta)) / (2 * a);
    double t2 = (-b + sqrt(delta)) / (2 * a);

    if (t1 > t2) {
        std::swap(t1, t2);
    }

    double tHit = t1;

    double r = ray.O.y + tHit * ray.D.y;
    if (r >= center.y && r <= center.y + height) {
        Point pHit = ray.at(tHit);

        Vector N(pHit.x - center.x, 0, pHit.z - center.z);
        N.normalize();
        return {tHit, N};
    }

    return Hit::NO_HIT();
}

Cylinder::Cylinder(Point center, double radius, double height)
:
center(center), radius(radius), height(height)
{}
