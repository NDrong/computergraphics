#include "cone.h"

#include <cmath>

Hit Cone::intersect(Ray const &ray) {
    Point diff = ray.O - center;

    double tan = (radius * radius) / (height * height);

    double deltaY = height - diff.y;
    double a = (ray.D.x * ray.D.x) + (ray.D.z * ray.D.z) - (tan * ray.D.y * ray.D.y);
    double b = (2 * diff.x * ray.D.x) + (2 * diff.z * ray.D.z) + (2 * tan * deltaY * ray.D.y);
    double c = (diff.x * diff.x) + (diff.z * diff.z) - (tan * deltaY * deltaY);

    double discriminant = b * b - 4 * a * c;

    if (fabs(discriminant) < 0.001) return Hit::NO_HIT();

    double t1 = (-b + sqrt(discriminant)) / (2 * a);
    double t2 = (-b - sqrt(discriminant)) / (2 * a);

    double tHit = (t1 > t2) ? t2 : t1;

    double r = ray.O.y + tHit * ray.D.y;
    if (r > center.y && r < center.y + height) {
        Point pHit = ray.at(tHit);
        diff = pHit - center;
        r = sqrt((diff.x * diff.x) + (diff.z * diff.z));
        Vector N(diff.x, r * (radius / height), diff.z);
        N.normalize();
        return {tHit, N};
    }

    return Hit::NO_HIT();
}

Cone::Cone(Point center, double radius, double height)
        :
        center(center), radius(radius), height(height) {}
