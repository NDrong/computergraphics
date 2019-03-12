#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include "animation.h"

class AnimationController
{
    std::map<SceneObject*, std::vector<std::unique_ptr<Animation>>> animations;
    unsigned long currentTick;

public:
    AnimationController();

    void addAnimation(SceneObject* obj, std::unique_ptr<Animation> animation);

    void tick();
};

#endif // ANIMATIONCONTROLLER_H
