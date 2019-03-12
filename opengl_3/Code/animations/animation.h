#ifndef ANIMATION_H
#define ANIMATION_H

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

    Animation(double cycleTime);
    Animation(double cycleTime, InterpolationMode interpolationMode);
    virtual ~Animation();

    void doUpdate(unsigned long currentTick, SceneObject* obj);

};

#endif // ANIMATION_H
