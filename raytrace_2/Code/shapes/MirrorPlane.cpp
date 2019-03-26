//
// Created by Julius van Dijk on 2019-03-26.
//

#include "MirrorPlane.h"

Hit MirrorPlane::intersect(Ray const &ray) {
    double denom = N.dot(ray.D);
    if (denom > 0.0001) {
        Point relative = center - ray.O;
        double t = relative.dot(N) / denom;
        if (t < -0.0001) {
            return Hit::NO_HIT();
        }

        Point hitPoint = ray.at(t);
        if ((hitPoint - center).length() > size) {
            return Hit::NO_HIT();
        }

        return Hit(t, N);
    }

    return Hit::NO_HIT();
}

MirrorPlane::MirrorPlane(Point center, double size, Vector N) : center(center), size(size), N(N) {
    bb = BoundingBox(center - size, center + size);
}
