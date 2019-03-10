#ifndef SPHERE_H_
#define SPHERE_H_

#include "../object.h"

class Sphere : public Object {
public:
    Sphere(Point const &pos, double radius);

    Sphere(Point const &pos, double radius, Point rotation, int angle);

    virtual Hit intersect(Ray const &ray);

    virtual Point getTextureCoords(Point pOnObject);

    void rotate(Ray const &ray);

    Point const position;
    double const r;

    Vector rotationParams;
    int rotationAngle;
};

#endif
