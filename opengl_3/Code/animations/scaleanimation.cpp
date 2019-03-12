#include "scaleanimation.h"

ScaleAnimation::ScaleAnimation(double cycleTime, float from, float to, InterpolationMode interpolationMode) : Animation(cycleTime, interpolationMode), from(from), to(to)
{

}

void ScaleAnimation::update(float pointInCycle, SceneObject *obj)
{
    float scale = from + (to - from) * pointInCycle;
    obj->setScaling(scale);
}
