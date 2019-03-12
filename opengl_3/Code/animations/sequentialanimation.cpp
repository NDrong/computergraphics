#include "sequentialanimation.h"

SequentialAnimation::SequentialAnimation(InterpolationMode interpolationMode) : Animation(0, interpolationMode)
{

}

void SequentialAnimation::addAnimation(std::unique_ptr<Animation> animation)
{
    cycleTime += animation->getCycleTime();
    animations.push_back(std::move(animation));
}

void SequentialAnimation::addAnimationNL(std::unique_ptr<Animation> animation)
{
    animation->shouldLoopBack = false;
    addAnimation(std::move(animation));
}

void SequentialAnimation::update(float pointInCycle, SceneObject *obj)
{
    double t = pointInCycle * cycleTime;
    for (auto& animation : animations) {
        if (t <= animation->getCycleTime()) {
            animation->doUpdate(t, obj);
            break;
        } else {
            t -= animation->getCycleTime();
        }
    }
}
