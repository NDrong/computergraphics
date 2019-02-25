#ifndef CONE_H_
#define CONE_H_

#include "../object.h"

class Cone: public Object
{
    public:
        Cone(Point center, double radius, double height);

        virtual Hit intersect(Ray const &ray);

        Point center;
        double radius, height;
};

#endif
