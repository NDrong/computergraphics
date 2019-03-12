#ifndef TRANSLATIONANIMATION_H
#define TRANSLATIONANIMATION_H

#include "animation.h"

class TranslationAnimation : public Animation
{
    QVector3D from, to;
public:
    TranslationAnimation(double cycleTime, QVector3D from, QVector3D to, InterpolationMode interpolationMode = InterpolationMode::LINEAR);

    // Animation interface
protected:
    void update(float pointInCycle, SceneObject *obj) override;
};

#endif // TRANSLATIONANIMATION_H
