#ifndef SEQUENTIALANIMATION_H
#define SEQUENTIALANIMATION_H

#include "animation.h"

class SequentialAnimation : public Animation
{
    std::vector<std::unique_ptr<Animation>> animations;

public:
    SequentialAnimation(InterpolationMode interpolationMode = InterpolationMode::LINEAR);
    void addAnimation(std::unique_ptr<Animation> animation);
    void addAnimationNL(std::unique_ptr<Animation> animation);

    // Animation interface
protected:
    void update(float pointInCycle, SceneObject *obj) override;
};

#endif // SEQUENTIALANIMATION_H
