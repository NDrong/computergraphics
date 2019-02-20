#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "../object.h"

class Triangle: public Object
{
    public:
        Triangle(Point va, Point vb, Point vc);

        virtual Hit intersect(Ray const &ray);

        Point va, vb, vc;
};

#endif
