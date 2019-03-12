#include "translationanimation.h"

TranslationAnimation::TranslationAnimation(double cycleTime, QVector3D from, QVector3D to, InterpolationMode interpolationMode) : Animation(cycleTime, interpolationMode), from(from), to(to)
{

}

void TranslationAnimation::update(float pointInCycle, SceneObject *obj)
{
    QVector3D location = from + (to - from) * pointInCycle;
    obj->setTranslation(location);
}
