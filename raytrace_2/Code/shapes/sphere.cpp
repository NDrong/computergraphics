#include "sphere.h"
#include "solvers.h"

#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

Hit Sphere::intersect(Ray const &ray) {
    // Sphere formula: ||x - position||^2 = r^2
    // Line formula:   x = ray.O + t * ray.D

    Vector L = ray.O - position;
    double a = ray.D.dot(ray.D);
    double b = 2 * ray.D.dot(L);
    double c = L.dot(L) - r * r;

    double t0;
    double t1;
    if (not Solvers::quadratic(a, b, c, t0, t1))
        return Hit::NO_HIT();

    // t0 is closest hit
    if (t0 < 0)  // check if it is not behind the camera
    {
        t0 = t1;    // try t1
        if (t0 < 0) // both behind the camera
            return Hit::NO_HIT();
    }

    // calculate normal
    Point hit = ray.at(t0);
    Vector N = (hit - position).normalized();

    // determine orientation of the normal
    if (N.dot(ray.D) > 0)
        N = -N;

    return Hit(t0, N);
}

Sphere::Sphere(Point const &pos, double radius) : position(pos), r(radius), hasRotation(false) {}

Sphere::Sphere(Point const &pos, double radius, Vector rotAxis, double rotAngle)
        : Sphere(pos, radius) {
    Sphere::rotAxis = rotAxis.normalized();
    Sphere::rotAngle = rotAngle * M_PI / 180;
    hasRotation = true;
}

Point Sphere::getTextureCoords(Point pOnObject) {
    Point pDiff = pOnObject - position;
    if (hasRotation) pDiff = rotate(pDiff, rotAxis, rotAngle);

    double theta = std::acos(pDiff.z / r);
    double phi = std::atan2(pDiff.y, pDiff.x);
    if (phi < 0) phi += 2 * M_PI;

    return Point(phi / (2 * M_PI), (M_PI - theta) / M_PI, 0.0);
}

Vector Sphere::rotate(Vector vec, Vector rot, double angle) {
    // Rodrigues' rotation formula.
    Vector term1 = vec * cos(angle);
    Vector term2 = rot.cross(vec) * sin(angle);
    Vector term3 = rot * rot.dot(vec) * (1 - cos(angle));
    return Vector(term1 + term2 + term3);
}


