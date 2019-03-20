#ifndef ROTATIONANIMATION_H
#define ROTATIONANIMATION_H

#include "animation.h"

class RotationAnimation : public Animation
{

public:
    enum Axis { X, Y, Z };
    RotationAnimation(double cycleTime, Axis axis, float fromDegree, float toDegree, InterpolationMode interpolationMode = InterpolationMode::LINEAR);

protected:
    void update(float pointInCycle, SceneObject* obj) override;

private:
    Axis axis;
    float fromDegree, toDegree;
};

#endif // ROTATIONANIMATION_H
