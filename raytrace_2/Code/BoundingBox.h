//
// Created by Julius on 21-3-2019.
//

#ifndef RAY_BOUNDINGBOX_H
#define RAY_BOUNDINGBOX_H


#include "triple.h"
#include "ray.h"

class BoundingBox {
    Point topLeft, bottomRight;

public:
    BoundingBox();
    BoundingBox(const Point& a, const Point& b);

    Point getTopLeft() const;
    Point getBottomRight() const;

    bool inBox(const Point& p) const;
    bool intersects(const Ray& ray) const;

    BoundingBox operator+(const BoundingBox& box) const;
    BoundingBox operator+(const Point& point) const;
    BoundingBox operator+=(const BoundingBox& box);
    BoundingBox operator+=(const Point& point);

};


#endif //RAY_BOUNDINGBOX_H
