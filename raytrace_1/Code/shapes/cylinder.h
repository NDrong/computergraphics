#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "../object.h"

class Cylinder: public Object
{
    public:
        Cylinder(Point center, double radius, double height);

        virtual Hit intersect(Ray const &ray);

        Point center;
        double radius, height;
};

#endif
