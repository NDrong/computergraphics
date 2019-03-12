#include "rotationanimation.h"

RotationAnimation::RotationAnimation(double cycleTime, QVector3D axis, InterpolationMode interpolationMode) : Animation (cycleTime, interpolationMode), axis(axis)
{

}

void RotationAnimation::update(float pointInCycle, SceneObject* obj) {
    float degrees = pointInCycle * 360.0f;
    QVector3D rotation = QVector3D(degrees, degrees, degrees) * axis;

    obj->setRotation(rotation);
}
