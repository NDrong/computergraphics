#ifndef ROTATIONANIMATION_H
#define ROTATIONANIMATION_H

#include "animation.h"

class RotationAnimation : public Animation
{
    QVector3D axis;

public:
    RotationAnimation(double cycleTime, QVector3D axis, InterpolationMode interpolationMode = InterpolationMode::LINEAR);

protected:
    void update(float pointInCycle, SceneObject* obj) override;
};

#endif // ROTATIONANIMATION_H
