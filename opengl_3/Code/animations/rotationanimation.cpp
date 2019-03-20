#include "rotationanimation.h"

RotationAnimation::RotationAnimation(double cycleTime, Axis axis, float fromDegree, float toDegree, InterpolationMode interpolationMode) : Animation (cycleTime, interpolationMode), axis(axis), fromDegree(fromDegree), toDegree(toDegree)
{

}

void RotationAnimation::update(float pointInCycle, SceneObject* obj) {
    float degrees = fromDegree + pointInCycle * (toDegree - fromDegree);

    auto rotation = obj->getRotation();
    if (axis == Axis::X) {
        rotation.setX(degrees);
    } else if (axis == Axis::Y) {
        rotation.setY(degrees);
    } else if (axis == Axis::Z) {
        rotation.setZ(degrees);
    }

    obj->setRotation(rotation);
}
