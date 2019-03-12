#include "animation.h"
#include <memory>

Animation::Animation(double cycleTime) : Animation(cycleTime, InterpolationMode::LINEAR)
{

}

Animation::Animation(double cycleTime, Animation::InterpolationMode interpolationMode) : cycleTime(cycleTime), interpolationMode(interpolationMode)
{

}

Animation::~Animation() {}

void Animation::doUpdate(unsigned long currentTick, SceneObject *obj)
{
    float pointInCycle = 0;

    if (interpolationMode == InterpolationMode::LINEAR) {
        pointInCycle = fmod(static_cast<double>(currentTick), cycleTime) / cycleTime;
    }

    update(pointInCycle, obj);
}
