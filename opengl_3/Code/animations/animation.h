#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>
#include <sceneobject.h>

class Animation
{
protected:
    double cycleTime;
    virtual void update(float pointInCycle, SceneObject* obj) = 0;

public:
    enum InterpolationMode {
        LINEAR
    };
    InterpolationMode interpolationMode;
    bool shouldLoopBack;

    Animation(double cycleTime);
    Animation(double cycleTime, InterpolationMode interpolationMode);
    virtual ~Animation();

    void doUpdate(unsigned long currentTick, SceneObject* obj);
    double getCycleTime() const;

};

#endif // ANIMATION_H
