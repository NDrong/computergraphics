#include "scene.h"

#include "hit.h"
#include "image.h"
#include "material.h"
#include "ray.h"

#include <cmath>
#include <limits>
#include <iostream>

using namespace std;

void Scene::render(Image &img) {
    unsigned w = img.width();
    unsigned h = img.height();
    #pragma omp parallel for collapse(2)
    for (unsigned y = 0; y < h; ++y) {
        for (unsigned x = 0; x < w; ++x) {
            double step = 0.5 / superSamplingFactor;
            double start = 0.5 - superSamplingFactor / 2.0 * step;

            Color col;
            #pragma omp parallel for collapse(2)
            for (unsigned sy = 0; sy < (unsigned) superSamplingFactor; sy++) {
                for (unsigned sx = 0; sx < (unsigned) superSamplingFactor; sx++) {
                    Point pixel(x + start + sx * step, h - 1 - y + start + sy * step, 0);
                    Ray ray(eye, (pixel - eye).normalized());
                    Color col2 = trace(ray);
                    col += col2;
                }
            }
            col /= superSamplingFactor * superSamplingFactor;

            col.clamp();
            img(x, y) = col;
        }
    }
}

// --- Misc functions ----------------------------------------------------------

bool Scene::traceObjects(Ray const &ray, int remainingRecursions, Color &color, Point &hit) {
    // Find hit object and distance
    Hit min_hit(numeric_limits<double>::infinity(), Vector());
    ObjectPtr obj = nullptr;
    for (unsigned idx = 0; idx != objects.size(); ++idx) {
        Hit hit(objects[idx]->intersect(ray));
        if (hit.t < min_hit.t) {
            min_hit = hit;
            obj = objects[idx];
        }
    }
    // No hit? Return background color.
    if (!obj) {
        color = Color(0.0, 0.0, 0.0);
        hit = Point(0, 0, 0);
        return false;
    }

    const Material &material = obj->material;          //the hit objects material
    hit = ray.at(min_hit.t);                 //the hit point
    Vector N = min_hit.N;                          //the normal at hit point
    Vector V = -ray.D;                             //the view vector

    /****************************************************
    * This is where you should insert the color
    * calculation (Phong model).
    *
    * Given: material, hit, N, V, lights[]
    * Sought: color
    *
    * Hints: (see triple.h)
    *        Triple.dot(Vector) dot product
    *        Vector + Vector    vector sum
    *        Vector - Vector    vector difference
    *        Point - Point      yields vector
    *        Vector.normalize() normalizes vector, returns length
    *        double * Color     scales each color component (r,g,b)
    *        Color * Color      dito
    *        pow(a,b)           a to the power of b
    ****************************************************/
    Point displacedHit = hit + min_hit.N * 0.0001;

    if (material.hasTexture()) {
        Point uvw = obj->getTextureCoords(hit);
        color = material.texture->colorAt(static_cast<float>(uvw.x), static_cast<float>(uvw.y));
    } else {
        color = material.ka * material.color;
    }

    for (const auto &light : lights) {
        Vector L = (light->position - hit).normalized();
        Vector R = -L - 2 * (-L).dot(N) * N;

        bool inShadow = false;
        if (useShadows) {
            // Prevent shadow acne
            Ray lightRay(displacedHit, L);
            inShadow = !isnan(intersectsWithObject(lightRay).t);
        }

        if (!inShadow) {
            // Diffuse component
            color += material.kd * std::max(0.0, N.dot(L)) * material.color * light->color;
            // Specular component
            color += material.ks * pow(std::max(0.0, R.dot(V)), material.n) * light->color;
        }
    }

    if (remainingRecursions > 0) {
        Vector eyeR = (ray.D) - 2 * (ray.D).dot(N) * N;
        Point reflectHit;
        Color reflectColor;
        bool foundReflect = traceObjects(Ray(displacedHit, eyeR), remainingRecursions - 1, reflectColor, reflectHit);
        if (foundReflect) {
            Vector Rr = -eyeR - 2 * (-eyeR).dot(N) * N;
            color += material.ks * pow(std::max(0.0, Rr.dot(V)), material.n) * reflectColor;

        }
    }

    return true;
}

void Scene::addObject(ObjectPtr obj) {
    objects.push_back(obj);
}

void Scene::addLight(Light const &light) {
    lights.push_back(LightPtr(new Light(light)));
}

void Scene::setEye(Triple const &position) {
    eye = position;
}

unsigned Scene::getNumObject() {
    return objects.size();
}

unsigned Scene::getNumLights() {
    return lights.size();
}

void Scene::setUseShadows(bool useShadows) {
    this->useShadows = useShadows;
}

Hit Scene::intersectsWithObject(const Ray &ray) {
    for (unsigned idx = 0; idx != objects.size(); ++idx) {
        Hit hit(objects[idx]->intersect(ray));
        if (!isnan(hit.t)) {
            return hit;
        }
    }
    return Hit::NO_HIT();
}

void Scene::setMaxRecursionDepth(int maxRecursionDepth) {
    this->maxRecursionDepth = maxRecursionDepth;
}

Color Scene::trace(Ray const &ray) {
    Point hit;
    Color color;
    traceObjects(ray, maxRecursionDepth, color, hit);
    return color;
}

void Scene::setSuperSamplingFactor(int superSamplingFactor) {
    this->superSamplingFactor = superSamplingFactor;
}
