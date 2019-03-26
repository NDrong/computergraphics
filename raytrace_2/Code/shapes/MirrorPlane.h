//
// Created by Julius van Dijk on 2019-03-26.
//

#ifndef RAY_MIRRORPLANE_H
#define RAY_MIRRORPLANE_H

#include "../object.h"

class MirrorPlane : public Object {

public:
    MirrorPlane(Point center, double size, Vector N);

    virtual Hit intersect(Ray const &ray);

private:
    Point center;
    double size;
    Vector N;

};


#endif //RAY_MIRRORPLANE_H
