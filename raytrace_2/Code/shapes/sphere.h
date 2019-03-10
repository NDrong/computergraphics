#ifndef SPHERE_H_
#define SPHERE_H_

#include "../object.h"

class Sphere : public Object {
public:
    Sphere(Point const &pos, double radius);

    Sphere(Point const &pos, double radius, Point rotation, int angle);

    virtual Hit intersect(Ray const &ray);

    virtual Point getTextureCoords(Point pOnObject);

    Vector rotate(Vector vec, Vector rot, int angle);

    Point const position;
    double const r;

    Vector rotationParams;
    int rotationAngle;
    bool hasRotation;
};

#endif
