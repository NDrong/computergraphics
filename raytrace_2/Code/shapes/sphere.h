#ifndef SPHERE_H_
#define SPHERE_H_

#include "../object.h"

class Sphere : public Object {
public:
    Sphere(Point const &pos, double radius);

    Sphere(Point const &pos, double radius, Vector rotAxis, double rotAngle);

    virtual Hit intersect(Ray const &ray);

    virtual Point getTextureCoords(Point pOnObject);

    Point const position;
    double const r;

private:
    Vector rotAxis;
    double rotAngle;
    bool hasRotation;

    Vector rotate(Vector vec, Vector rot, double angle);
};

#endif
