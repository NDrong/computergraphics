#ifndef SCALEANIMATION_H
#define SCALEANIMATION_H

#include "animation.h"

class ScaleAnimation : public Animation
{
    double from, to;
public:
    ScaleAnimation(double cycleTime, float from, float to, InterpolationMode interpolationMode = InterpolationMode::LINEAR);

    // Animation interface
protected:
    void update(float pointInCycle, SceneObject *obj) override;
};

#endif // SCALEANIMATION_H
