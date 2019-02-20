#include "sphere.h"

#include <cmath>

using namespace std;

Hit Sphere::intersect(Ray const &ray)
{
    /****************************************************
    * RT1.1: INTERSECTION CALCULATION
    *
    * Given: ray, position, r
    * Sought: intersects? if true: *t
    *
    * Insert calculation of ray/sphere intersection here.
    *
    * You have the sphere's center (C) and radius (r) as well as
    * the ray's origin (ray.O) and direction (ray.D).
    *
    * If the ray does not intersect the sphere, return false.
    * Otherwise, return true and place the distance of the
    * intersection point from the ray origin in *t (see example).
    ****************************************************/

    // place holder for actual intersection calculation

    Vector OC = position - ray.O;

    double tca = OC.dot(ray.D);
    double d2 = OC.dot(OC) - tca * tca;
    if (d2 > r * r) return Hit::NO_HIT();
    double thc = sqrt(r*r - d2);
    double t0 = tca - thc;
    double t1 = tca + thc;

    if (t0 > t1) std::swap(t0, t1);

    if (t0 < 0) {
        t0 = t1;
        if (t0 < 0) {
            return Hit::NO_HIT();
        }
    }

    /****************************************************
    * RT1.2: NORMAL CALCULATION
    *
    * Given: t, C, r
    * Sought: N
    *
    * Insert calculation of the sphere's normal at the intersection point.
    ****************************************************/

    Vector N = (ray.at(t0) - position).normalized();

    return Hit(t0,N);
}

Sphere::Sphere(Point const &pos, double radius)
:
    position(pos),
    r(radius)
{}
