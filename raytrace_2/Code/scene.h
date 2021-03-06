#ifndef SCENE_H_
#define SCENE_H_

#include "light.h"
#include "object.h"
#include "triple.h"
#include "KdTree.h"

#include <vector>

// Forward declerations
class Ray;
class Image;

class Scene
{
    std::vector<ObjectPtr> objects;
    std::unique_ptr<KdTree> tree;
    std::vector<LightPtr> lights;   // no ptr needed, but kept for consistency
    Point eye;
    bool useShadows;
    int maxRecursionDepth;
    int superSamplingFactor;

    Hit intersectsWithObject(const Ray& ray);

    public:

        // trace a ray into the scene and return the color
        Color trace(Ray const &ray);
        bool traceObjects(Ray const &ray, int remainingRecursions, Color &color, Point &hit);

        // render the scene to the given image
        void render(Image &img);


        void addObject(ObjectPtr obj);
        void addLight(Light const &light);
        void setEye(Triple const &position);
        void setUseShadows(bool useShadows);
        void setMaxRecursionDepth(int maxRecursionDepth);

    void setSuperSamplingFactor(int superSamplingFactor);

    unsigned getNumObject();
        unsigned getNumLights();
};

#endif
