#include "animationcontroller.h"

AnimationController::AnimationController() : currentTick(0)
{

}

void AnimationController::addAnimation(SceneObject *obj, std::unique_ptr<Animation> animation)
{
    animations[obj].push_back(std::move(animation));
}

void AnimationController::tick()
{
    for (auto& pair : animations) {
        for (auto& anim : pair.second) {
            anim->doUpdate(currentTick, pair.first);
        }
    }

    currentTick++;
}
