//
// Created by Julius on 21-3-2019.
//

#include <limits>
#include "BoundingBox.h"

BoundingBox BoundingBox::operator+(const Point &point) const {
    BoundingBox b(topLeft, point);
    b.bottomRight = Point(std::max(b.bottomRight.x, point.x), std::max(b.bottomRight.y, point.y), std::max(b.bottomRight.z, point.z));
    return b;
}

BoundingBox BoundingBox::operator+(const BoundingBox &box) const {
    Point ntl(std::min(topLeft.x, box.topLeft.x), std::min(topLeft.y, box.topLeft.y), std::min(topLeft.z, box.topLeft.z));
    Point nbr(std::max(bottomRight.x, box.bottomRight.x), std::max(bottomRight.y, box.bottomRight.y), std::max(bottomRight.z, box.bottomRight.z));
    return {ntl, nbr};
}

Point BoundingBox::getBottomRight() const {
    return bottomRight;
}

Point BoundingBox::getTopLeft() const {
    return topLeft;
}

BoundingBox::BoundingBox(const Point &a, const Point &b) {
    topLeft = Point(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
    bottomRight = Point(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}

bool BoundingBox::inBox(const Point &p) const {
    return (p.x >= topLeft.x && p.x < bottomRight.x) &&
            (p.y >= topLeft.y && p.y < bottomRight.y) &&
            (p.z >= topLeft.z && p.z < bottomRight.z);
}

BoundingBox::BoundingBox() {
    topLeft = Point(std::numeric_limits<double>::max(),std::numeric_limits<double>::max(),std::numeric_limits<double>::max());
    bottomRight = Point(-std::numeric_limits<double>::max(),-std::numeric_limits<double>::max(),-std::numeric_limits<double>::max());
}

BoundingBox BoundingBox::operator+=(const BoundingBox &box) {
    topLeft = Point(std::min(topLeft.x, box.topLeft.x), std::min(topLeft.y, box.topLeft.y), std::min(topLeft.z, box.topLeft.z));
    bottomRight = Point(std::max(bottomRight.x, box.bottomRight.x), std::max(bottomRight.y, box.bottomRight.y), std::max(bottomRight.z, box.bottomRight.z));

    return *this;
}

BoundingBox BoundingBox::operator+=(const Point &point) {
    topLeft = Point(std::min(topLeft.x, point.x), std::min(topLeft.y, point.y), std::min(topLeft.z, point.z));
    bottomRight = Point(std::max(bottomRight.x, point.x), std::max(bottomRight.y, point.y), std::max(bottomRight.z, point.z));

    return *this;
}

bool BoundingBox::intersects(const Ray &ray) const {
    double tmin = (topLeft.x - ray.O.x) / ray.D.x;
    double tmax = (bottomRight.x - ray.O.x) / ray.D.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    double tymin = (topLeft.y - ray.O.y) / ray.D.y;
    double tymax = (bottomRight.y - ray.O.y) / ray.D.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    double tzmin = (topLeft.z - ray.O.z) / ray.D.z;
    double tzmax = (bottomRight.z - ray.O.z) / ray.D.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return true;
}
